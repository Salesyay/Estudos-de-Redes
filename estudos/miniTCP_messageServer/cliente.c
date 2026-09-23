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
    char s [INET6_ADDRSTRLEN];

    if (argc != 3)
    {
        fprintf(stderr,"uso: client hostname\n");
        exit(1);
    }
  
    memeset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(argv[1], argv[2], &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    connect(sockfd, res->ai_addr, res->ai_addrlen);

    printf("Conectado ao servidor!\n");

    close(sockfd);
    freeaddrinfo(res);

    return 0;
}