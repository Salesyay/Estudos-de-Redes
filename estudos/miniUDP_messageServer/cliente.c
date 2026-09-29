#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT "8000"
#define MAXDATASIZE 100 //número máximo de bytes que podem ser armazenados no buffer

void *get_in_addr(struct sockaddr *sa) {
    //adaptando a estrutura para IPv4 ou IPv6
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    else {
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[MAXDATASIZE]; //buffer de dados que armazena MAXDATASIZE
    struct addrinfo hints, *serverinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2)
      //programa executado de maneira errada
    {
        fprintf(stderr, "uso: client hostname\n");
        exit(1);
    }

    //armazenando as características da conexão
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    //setting getaddrinfo() já checando erro na formatação do mesmo
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &serverinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    //percorrendo todos os resultados de getaddrinfo()
    for (p = serverinfo; p != NULL; p = p->ai_next) {

        //criando o socket e verificando erro no mesmo
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }


        //transformando binário em IP para informar ao s
        inet_ntop(p->ai_family,
                  get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);

        printf("client: tentando conectar em %s\n", s);

        break;
    }

    printf("Conectado ao servidor!\n");//gg

    close(sockfd); //fechando o socket

    freeaddrinfo(serverinfo); //encerrando a lista criada por getaddrinfo()

    return 0;
}