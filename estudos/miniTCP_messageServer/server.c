/*Seu primeiro objetivo

Faça o servidor:

criar um socket TCP;
escolher uma porta, por exemplo 3490;
fazer bind;
chamar listen;
ficar parado esperando um cliente em accept.*/

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

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    //estruturando o socket

    bind (sockfd, res-> ai_addr, res-> ai_addrlen);
    
    listen(sockfd, BACKLOG);



}