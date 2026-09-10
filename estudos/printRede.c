#include <stdio.h>

#include <arpa/inet.h> // biblioteca que permite a conversao e manipulacao de redes

int main(void) {

    // IPv4

    char ip4[INET_ADDRSTRLEN]; // criando um espaco para armazenar uma string (o IP)

    struct sockaddr_in sa; // estrutura que armazena informacoes de um endereco IPv4

    inet_pton(AF_INET, "192.168.1.100", &(sa.sin_addr)); // convertendo o IP de texto para binario

    inet_ntop(AF_INET, &(sa.sin_addr), ip4,
              INET_ADDRSTRLEN); // convertendo o endereco IPv4 de binario para texto

    printf("O endereco IPv4 eh %s\n", ip4); // mostrando o endereco IPv4 na tela

    return 0;