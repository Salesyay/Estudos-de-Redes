#include <stdio.h>

#include <arpa/inet.h> 

int main(void) {

    // IPv6

    char ip6[INET6_ADDRSTRLEN]; // criando um espaco para armazenar uma string (o IPV6)

    struct sockaddr_in6 sa6; // estrutura que armazena informacoes de um endereco IPv6

    inet_pton(AF_INET6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334",  &(sa6.sin6_addr));  // convertendo o IPv6 de texto para binario

    inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);  // convertendo o endereco IPv6 de binario para texto

    printf("O endereco IPv6 eh: %s\n", ip6);

    return 0;
}