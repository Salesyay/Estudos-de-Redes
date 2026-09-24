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

  //setting getaddrinfo() ja checando erro na formatação do mesmo
  if((rv = getaddrinfo(argv[1], PORT,&hints, &serverinfo)) != 0) {
    fprintf(stderr"getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  for(p = serverinfo; p != NULL, p -> ai_next) {
    if(((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
      perror(stderr"server: socket")
      continue;
    }

    inet_ntop(p->ai_familly,
             get_in_addr((struct sockaddr *)p -> ai_addr), s, sizeof s);

    if(connect(sockfd, res->ai_addr, res->ai_addrlen)) {
      perror("client: connect");
      close(sockfd);
    }
    
    break; 
  }
    
    printf("Conectado ao servidor!\n");

    close(sockfd);
    freeaddrinfo(res);
*/
    return 0;
}