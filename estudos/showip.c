#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    // argc = quantidade de argumentos
    // argv = argumentos recebidos pelo terminal

    struct addrinfo hints, *res, *p;
    // hints configura a busca; res recebe os resultados; p percorre a lista

    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr, "uso: showip hostname\n");
        return 1; // uso incorreto do programa
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2; // erro ao resolver o hostname
    }

    printf("Endereço IP para %s:\n\n", argv[1]);

    for (p = res; p != NULL; p = p->ai_next) {
        // Percorre cada endereço encontrado

        void *addr;
        char *ipver;

        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 =
                (struct sockaddr_in *)p->ai_addr;

            addr = &(ipv4->sin_addr);
            ipver = "IPv4";

        } else { // IPv6
            // tratar endereço IPv6 aqui
        }
    }
}