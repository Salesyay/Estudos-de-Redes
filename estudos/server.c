/*O exercício

Faça um programa server.c que:

Crie um socket TCP.
Faça bind() dele em uma porta que você escolher, por exemplo 3490.
Coloque o socket em modo de escuta com listen().
Fique esperando um cliente com accept().

Quando alguém conectar, mostre algo como:

Cliente conectado!
Feche a conexão aceita e termine o programa.

Por enquanto não precisa mandar nem receber dados. Só queremos provar que você entendeu o estabelecimento da conexão.*/
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

#define MYPORT "8000"
//porta que sera usada no servidor
#define BACKLOG 10
//definindo o backlog

int main(void) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd, new_fd;

    memset(&hints, 0, sizeof hints);
    //zerando a estrutura de rede

    hints.ai_family = AF_UNSPEC; //IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = AI_PASSIVE; //preencha com o meu IP

    getaddrinfo(NULL, MYPORT, &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    //estruturando o socket

    bind(sockfd, res->ai_addr, res->ai_addrlen);
    //resstruturando o bind

    listen(sockfd, BACKLOG);

    //aceitando uma requisicao a caminho
    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);

    //pronto para comunicar...
    printf("Cliente conectado!\n")
}