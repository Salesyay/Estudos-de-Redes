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

//funcao inetntop
const char *inet_ntop2(void *addr, char *buf, size_t size)
{
    struct sockaddr_storage *sas = addr;//sas aponta para 'sockaddr_sotrage' e addr aponta para 'void'
    struct sockaddr_in *sa4; //sa4 aponta para o endereco de IPv4
    struct sockaddr_in6 *sa6; //sa6 aponta para o endereco de IPv6
    void *src; //aponta pra o endereco IP independente da versao de protocolo

    switch (sas->ss_family) {
        case AF_INET: //caso IPv4
            sa4 = addr; //addr recebe sa4 que eh um ponteiro para ipv4
            src = &(sa4->sin_addr); //faca com que src aponte para o endereco IPv4 dentro da estrutura
            // em C '&' representa 'endereco de', por isso usamos ele ali em cima
            break;
        case AF_INET6: //caso IPv6
            sa6 = addr;// addr recebe sa6 que eh um ponteiroi para IPv6
            src = &(sa6->sin6_addr); //faz com que src aponte para o enderco de IPv6 dentro da estrutura
            break;
        default:
            return NULL; //caso nao for nenhum dos dois renorne NULL
    }

    return inet_ntop(sas->ss_family, src, buf, size); // se tudo occoreu certo, 
    // a funcao inet_ntop() recebe: inet_ntop(family, endereço, buffer, tamanho);
}


int get_listener_socket(void)
{
    int listener;     // Listening socket descriptor
    int yes=1;        // For setsockopt() SO_REUSEADDR, below
    int rv;

    struct addrinfo hints, *ai, *p;

    // Get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "pollserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol);
        if (listener < 0) {
            continue;
        }

        // Lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // If we got here, it means we didn't get bound
    if (p == NULL) {
        return -1;
    }

    freeaddrinfo(ai); // All done with this

    // Listen
    if (listen(listener, 10) == -1) {
        return -1;
    }

    return listener;
}

int main(void)
{
    int listener;   // socket responsavel por receber novas conexoes

    int fd_size = 5;    // capacidade inicial do array de descritores
    int fd_count = 0;   // quantidade de descritores sendo utilizados no momento

    // espaco para armazenar os descritores que serao monitorados pelo poll
    struct pollfd *pfds = malloc(sizeof *pfds * fd_size);

    listener = get_listener_socket();

    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    // adiciona o socket listener ao primeiro espaco do array
    pfds[0].fd = listener;

    // monitora o socket para verificar novas conexoes
    pfds[0].events = POLLIN;

    fd_count = 1;

    puts("pollserver: waiting for connections...");

    // mantem o servidor executando continuamente
    for (;;) {

        // espera algum dos sockets ficar pronto para comunicacao
        int poll_count = poll(pfds, fd_count, -1);

        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        // processa as conexoes e eventos encontrados pelo poll
        process_connections(listener, &fd_count, &fd_size, &pfds);
    }

    // libera o espaco utilizado pelo array
    free(pfds);
}