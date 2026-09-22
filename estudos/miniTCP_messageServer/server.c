#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BACKLOG 10

int main(void) {
    struct sockaddr_storage their_addr; //iformações do endereço conectado
    socklen_t addr_size; 
    struct addrinfo hints *res;
    int sockfd; //intenger que recrberá o socket
    char ip[INET6_ADDRSTRLEN]; //armazenando o IP do cliente
    int rv;
    int yes = 1;

  
    //estruturando o hints da rede
    memset(&hints, 0, sizeof hints); //zerando a estrutura de rede

    hints.ai_family = AF_UNSPEC; //IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; //TCP
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


      //reutilizando socket (caso não de, retorne erro)
      if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit (1);
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
  
  if(listen(sockfd, BACKLOG) == -1) {
    perror("server: info");
    exit(1);
  }

  //encerrando todos os dead process
  sa.sa_sandler = sigchld_handler; 
  sigemptyser(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  printf("servidor: esperando conexão... \n")
}