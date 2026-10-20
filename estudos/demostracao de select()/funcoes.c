#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <errno.h>
#include <signal.h>
#include "funcoes.h"

//funcao inetntop
const char *inet_ntop2(void *addr, char *buf, size_t size)
{
    struct sockaddr_storage *sas = addr; //sas aponta para 'sockaddr_storage' e addr aponta para 'void'
    struct sockaddr_in *sa4; //sa4 aponta para o endereco de IPv4
    struct sockaddr_in6 *sa6; //sa6 aponta para o endereco de IPv6
    void *src; //aponta para o endereco IP independente da versao de protocolo

    //verifica a familia do endereco recebido
    switch (sas->ss_family) {
        case AF_INET: //caso IPv4
            sa4 = addr; //addr recebe sa4 que eh um ponteiro para IPv4
            src = &(sa4->sin_addr); //faz src apontar para o endereco IPv4 dentro da estrutura
            //em C '&' representa 'endereco de', por isso usamos ele ali em cima
            break;

        case AF_INET6: //caso IPv6
            sa6 = addr; //addr recebe sa6 que eh um ponteiro para IPv6
            src = &(sa6->sin6_addr); //faz src apontar para o endereco IPv6 dentro da estrutura
            break;

        default:
            return NULL; //caso nao seja nenhum dos dois, retorna NULL
    }

    //a funcao inet_ntop() recebe: inet_ntop(family, endereco, buffer, tamanho)
    return inet_ntop(sas->ss_family, src, buf, size);
}


int get_listener_socket(void)
{
    int listener; //descritor do socket do servidor
    int yes = 1; //valor passado para setsockopt() para ativar SO_REUSEADDR
    int rv;

    struct addrinfo hints, *ai, *p;
    //estrutura de configuracao e ponteiros para a lista de enderecos

    //estrutura do hints
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; //IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = AI_PASSIVE;

    //obtendo os enderecos locais para criar o socket do servidor
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        //checagem de erro em getaddrinfo()
        fprintf(stderr, "pollserver: %s\n", gai_strerror(rv));
        return -1;
    }

    //percorrendo a lista de getaddrinfo()
    for (p = ai; p != NULL; p = p->ai_next) {

        //criando socket
        listener = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol);

        if (listener < 0) {
            continue;
        }

        //reutilizando o socket
        if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof yes) < 0) {
            close(listener);
            continue;
        }

        //bind()ando o socket
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    //nao conseguimos criar e associar o socket a um endereco
    if (p == NULL) {
        freeaddrinfo(ai);
        return -1;
    }

    freeaddrinfo(ai); //liberando o addrinfo

    //colocando o socket para escutar novas conexoes
    if (listen(listener, 10) == -1) {
        close(listener);
        return -1;
    }

    return listener;
}

void handle_client_data(int listener, int *fd_count,
        struct pollfd *pfds, int *pfd_i)
{
    char buf[256]; //buffer que armazena os dados recebidos do cliente

    //armazena o descritor do cliente que enviou os dados
    int sender_fd = pfds[*pfd_i].fd;

    //recebe os dados enviados pelo cliente conectado
    int nbytes = recv(sender_fd, buf, sizeof buf, 0);

    //verifica se ocorreu um erro ou se o cliente encerrou a conexao
    if (nbytes <= 0) {

        if (nbytes == 0) {
            printf("pollserver: socket %d hung up\n", sender_fd);
        } else {
            perror("recv");
        }

        //fecha o socket do cliente desconectado
        close(sender_fd);

        //remove o descritor do cliente do array pfds
        del_from_pfds(pfds, *pfd_i, fd_count);

        //volta uma posicao no indice porque um elemento foi removido
        (*pfd_i)--;

    } else {

        //mostra os dados recebidos do cliente
        printf("pollserver: recv from fd %d: %.*s",
                sender_fd, nbytes, buf);

        //percorre os descritores para enviar os dados aos outros clientes
        for (int j = 0; j < *fd_count; j++) {

            //armazena o descritor do cliente que vai receber os dados
            int dest_fd = pfds[j].fd;

            //verifica se o destino nao eh o socket do servidor nem o remetente
            if (dest_fd != listener && dest_fd != sender_fd) {

                //envia os dados recebidos para o outro cliente
                int total_sent = 0;

                //continua enviando enquanto houver dados pendentes
                while (total_sent < nbytes) {
                    int sent = send(dest_fd, buf + total_sent,
                            nbytes - total_sent, MSG_NOSIGNAL);

                    //verifica se ocorreu um erro durante o envio
                    if (sent <= 0) {
                        perror("send");
                        break;
                    }

                    //atualiza a quantidade de bytes enviados
                    total_sent += sent;
                }
            }
        }
    }
}


void handle_new_connection(int listener, int *fd_count, int *fd_size,
        struct pollfd **pfds)
{
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen = sizeof remoteaddr;
    int newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

    if (newfd == -1) {
        perror("accept");
        return;
    }

    char remoteIP[INET6_ADDRSTRLEN];
    const char *ip = inet_ntop2(&remoteaddr, remoteIP, sizeof remoteIP);

    if (ip == NULL) {
        fprintf(stderr, "pollserver: inet_ntop failed\n");
        ip = "unknown";
    }

    printf("pollserver: new connection from %s on socket %d\n",
            ip, newfd);

    add_to_pfds(pfds, newfd, fd_count, fd_size);
}


void process_connections(int listener, int *fd_count, int *fd_size,
        struct pollfd **pfds)
{
    //percorre os descritores registrados no array pfds
    for (int i = 0; i < *fd_count; i++) {

        //armazena os eventos identificados pelo poll()
        short revents = (*pfds)[i].revents;

        //verifica se ocorreu algum evento no socket
        if (revents == 0) {
            continue;
        }   

        //verifica se o socket apresentou erro ou descritor invalido
        if (revents & (POLLERR | POLLNVAL)) {

            //verifica se o descritor pertence a um cliente
            if ((*pfds)[i].fd != listener) {
                //fecha o socket do cliente
                close((*pfds)[i].fd);

                //remove o descritor do array pfds
                del_from_pfds(*pfds, i, fd_count);

                //volta uma posicao para verificar o elemento que foi movido
                i--;
            }

            continue;
        }

        //verifica se o descritor recebeu dados ou se a conexao foi encerrada
        if (revents & (POLLIN | POLLHUP)) {

            //verifica se o descritor pertence ao socket de escuta do servidor
            if ((*pfds)[i].fd == listener) {

                //trata uma nova conexao recebida pelo servidor
                handle_new_connection(listener, fd_count, fd_size,
                        pfds);

            } else {

                //trata os dados recebidos de um cliente conectado
                handle_client_data(listener, fd_count, *pfds, &i);
            }
        }
    }
}