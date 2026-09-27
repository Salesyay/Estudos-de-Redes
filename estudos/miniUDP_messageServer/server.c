#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

#define PORT "8000"
#define MAXBUFLEN 100

int main(void) {
  struct sockaddr_storage their_addr; //iformações do endereço conectado
  socklen_t addr_size; 
  struct addrinfo hints, *serverinfo, *p;
  int sockfd; //intenger que recrberá o socket
  char s[INET6_ADDRSTRLEN]; //armazenando o IP do cliente
  int rv;
  struct sigaction sa;
  int numbytes;
  char buf[MAXBUFLEN];
  

  
  //estruturando o hints da rede
  memset(&hints, 0, sizeof hints); //zerando a estrutura de rede

  hints.ai_family = AF_UNSPEC; //IPv4 ou IPv6
  hints.ai_socktype = SOCK_DRAM; //UDP
  hints.ai_flags = AI_PASSIVE; //endereço local para servidor

  //checagem de erro na execução do getaddrinfo()
  if ((rv = getaddrinfo(NULL, PORT, &hints, &serverinfo)) != 0) {
  fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
  return 1;
  }

  //percorrendo as opções de endereço retornadas por getaddrinfo()
  for(p = serverinfo; p != NULL; p = p-> ai_next) {
    //estruturando socket e verificando erro
    if ((sockfd = socket(p-> ai_family, p-> ai_socktype, p->ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }

    //associando o socket a um endereço e porta (caso der erro, feche socket)
    if(bind(sockfd, p-> ai_addr, p-> ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      continue;
    }
    break;
    }

  freeaddrinfo(serverinfo); //liberando a lista alocada por getaddrinfo()

  if(p == NULL) {
    //nenhum dos endereços disponiveis pode ser associado ao socket
    fprintf(stderr,"server: filled to bind\n"); 
    exit(1);
   }

  printf("Listrner: esperando recvfrom\n");

  addr_len = sizeof their_addr; //tamanho do addr do cliente

  //estruturando o recvfrom e checando erro no mesmo
  if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0,(struct sockaddr *) &their_addr, &addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }
  
  printf("listener: pacote recebido de: %s\n", inet_ntop(their_addr.ss_family,
                                                        get_in_addr((steuct sockaddr*)&their_addr), s. sizeof s));
  printf("o tamanho do pacote é: %d em bytes\n", numbytes);

  buf[numbytes] = '/0';

  printf("O pacote contém: %s\n", buf); /

  close(sockfd); //fechando o socket

  return 0; //gg
  }
