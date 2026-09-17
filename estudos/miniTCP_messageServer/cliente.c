```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *res;

    if (argc != 3)
    {
        printf("Uso: %s <host> <porta>\n", argv[0]);
        return 1;
    }

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(argv[1], argv[2], &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    connect(sockfd, res->ai_addr, res->ai_addrlen);

    printf("Conectado ao servidor!\n");

    close(sockfd);
    freeaddrinfo(res);

    return 0;
}
```
