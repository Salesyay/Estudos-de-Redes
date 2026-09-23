#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MYPORT "8000"
// porta que sera usada no servidor

#define BACKLOG 10
// definindo o backlog

int main(void) {

    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd, new_fd;
    char ip[INET6_ADDRSTRLEN]; //armazenando o IP do cliente


    memset(&hints, 0, sizeof hints);
    // zerando a estrutura de rede

    hints.ai_family = AF_UNSPEC; // IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM;//TCP
    hints.ai_flags = AI_PASSIVE; //preencha com o meu IP


    getaddrinfo(NULL, MYPORT, &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    // estruturando o socket2

    bind(sockfd, res->ai_addr, res->ai_addrlen);
    // associando o socket na port


    listen(sockfd, BACKLOG);

    //aceitando uma requisicao a caminho
    addr_size = sizeof their_addr;
    new_fd = accept(sockfd,(struct sockaddr *)&their_addr,&addr_size);

    //pronto para comunicar...
    printf("Cliente conectado!\n");

    // mostrando o IP do cliente na tela
    if (their_addr.ss_family == AF_INET) {
        // se o endereco do cliente for IPv4

        struct sockaddr_in *ipv4 =
            (struct sockaddr_in *)&their_addr;
        // interpreta their_addr como uma estrutura IPv4


        inet_ntop(
            AF_INET,
            &ipv4->sin_addr,
            ip,
            sizeof ip
        );
        // converte o endereco IPv4 de binario
        // para uma string legivel
    }

    else {
        // caso contrario, o endereco sera IPv6

        struct sockaddr_in6 *ipv6 =
            (struct sockaddr_in6 *)&their_addr;
        // interpreta their_addr como uma estrutura IPv6


        inet_ntop(
            AF_INET6,
            &ipv6->sin6_addr,
            ip,
            sizeof ip
        );
        // converte o endereco IPv6 de binario
        // para uma string legivel
    }


    printf("IP do cliente: %s\n", ip);
    // mostra o IP convertido para texto

    close(new_fd);
    // fecha a conexao com o cliente

    close(sockfd);
    // fecha o socket do servidor

    freeaddrinfo(res);
    // libera a memoria usada pelo getaddrinfo

    return 0;
}