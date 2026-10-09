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
#include "funcoes.h"

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
    int listener;//descritor do codigo
    int yes=1;//valor q sera passado para setsockopt() para ativar SO_REUSEADDR()
    int rv;

    struct addrinfo hints, *ai, *p;
  //lista de addeinfo e seus ponteiros

    //estrutura do hints
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; //IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; //tcp
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
      //checagem de erro em getaddrinfo()
        fprintf(stderr, "pollserver: %s\n", gai_strerror(rv));
        exit(1);
    }

  //percorendo a lista de getaddrinfo()
    for(p = ai; p != NULL; p = p->ai_next) {
      //criando socket
        listener = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol);
        if (listener < 0) {
            continue;
        }

        // reutilizando o socket
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int));

      //bind()ando o socket
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // não conseguimos conexão, retorne errro
    if (p == NULL) {
        return -1;
    }

    freeaddrinfo(ai); // liberando o addrinfo

    // Listen erro
    if (listen(listener, 10) == -1) {
        return -1;
    }

    return listener;
}

void add_to_pfds(struct pollfd **pfds, int newfd, int *fd_count, int *fd_size) {
  //checando se tem memoria suficiente
  if(*fd_count == fd_size){
    //se nao tiver, dobra e realoca com reqlloc()
    fd_size *= 2;
    *pfds = realloc(*pfds,sizeof(**pfds) * (fd_size));
    
  }
}
//remoção de um elemento do array pfds
void del_from_pfds (struct pollfd pfds[], int i, int *fd_count) {
  pfds[i] = pfds[fd_count - 1];

  (*fd_count)--;
}

