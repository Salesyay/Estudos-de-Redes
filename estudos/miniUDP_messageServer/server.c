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

void sigchld_handler(int s) {
  //evita que os processos filhos virem zombie process.
  (void)s;
  int saved_errno = errno;
  while(waitpid(-1, NULL, WNOHANG) > 0);
  errno = saved_errno;
}

void *get_in_addr(struct sockaddr *sa) {
  //adaptando a estrutura para IPv4 ou IPv6
  if(sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)-> sin_addr);
  }
  else {
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
  }
}


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
  
  if(listen(sockfd, BACKLOG) == -1) {
    perror("server: info");
    exit(1);
  }

  //encerrando todos os dead process
  sa.sa_handler = sigchld_handler; 
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  printf("servidor: esperando conexão... \n");

  addr_len = sizeof their_addr;
  if((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0,
     (struct sockaddr *)&their_addr, addr_len)) ==-1) {
    perror("recvfrom");
    exit(1);
     }
  printf()

  while(1) {
    //loop que aceita conexões
    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);
    if (new_fd == -1){
      //checagem de erro
      perror("accept");
      continue;
    }

    //descobrindo o IP dk client 
    inet_ntop(their_addr.ss_family, 
      get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
    printf("servidor foi conectado a %s\n", s);

    //criando processo filho para atender o cliente
    if (!fork()) {
      close(sockfd);
      //imprimindo "Olá, mundo!" :3
      if(send(new_fd, "Olá, mundo!", 13, 0) == -1)
        perror("send");
      //encerrando processo filho
      close(new_fd);
      exit(0);
    }
    //encerrando processo pai
    close(new_fd);
  }
  return 0; //gg
}