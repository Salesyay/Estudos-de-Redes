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

int main(int argc, char *argv[]) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints *res;
    int sockfd;
    char ip[INET6_ADDRSTRLEN]; //armazenando o IP do cliente

    if(argv <= 2) {
        fprintf (stderr, "ocorreu um erro, e necessario digitar mais de um argumento
        \n digite ./server mais a port\n");
        //uso incorrteo do programa
        return 1; //ERR0

    }

    memset(&hints, 0, sizeof hints); //zerando a estrutura de rede

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    //estruturando o hints da rede

    getaddrinfo (NULL, argc, &hints, &res)

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    //estruturando o socket

    bind (sockfd, res-> ai_addr, res-> ai_addrlen);
    
    listen(sockfd, BACKLOG);



}