#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>

#define PORT "8000"
#define MAXDATASIZE "100" //numero de bytes que nós receberemos de uma vez

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[MAXDATASIZE]; //buffer de dados que armazena MAXDATASIZE
    struct addrinfo hints, *serverinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 3)
      //programa executado de maneira errada
    {
        fprintf(stderr, "uso: client hostname\n");
        exit(1);
    }

    //armazenando as caracteristicas da conexão
    memeset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    //setting getaddrinfo() ja checando erro na formatação do mesmo
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &serverinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    //percorrendo todos os resultados de getaddrinfo()
    for (p = serverinfo; p != NULL; p = p->ai_next) {
        //criando o socket e verificando erro no mesmo
        if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        //transformando binario em ip para informa-lo a "s"
        inet_ntop(p->ai_familly,
                  get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);

        //conectando ao servidor
        if (connect(sockfd, res->ai_addr, res->ai_addrlen)) {
            perror("client: connect");
            close(sockfd);
        }

        break;
    }

    printf("Conectado ao servidor!\n");//gg

    close(sockfd); //fechando o socket
    freeaddrinfo(res); // liberando  a lista de endereços de getaddrinfo()
    return 0;
}