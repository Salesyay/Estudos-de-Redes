#include <stdio.h>

int main(void)
{
    int listener;   // socket responsavel por receber novas conexoes

    int fd_size = 5;    // capacidade inicial do array de descritores
    int fd_count = 0;   // quantidade de descritores sendo utilizados no momento

    // espaco para armazenar os descritores que serao monitorados pelo poll
    struct pollfd *pfds = malloc(sizeof *pfds * fd_size);

    listener = get_listener_socket();

    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    // adiciona o socket listener ao primeiro espaco do array
    pfds[0].fd = listener;

    // monitora o socket para verificar novas conexoes
    pfds[0].events = POLLIN;

    fd_count = 1;

    puts("pollserver: waiting for connections...");

    // mantem o servidor executando continuamente
    for (;;) {

        // espera algum dos sockets ficar pronto para comunicacao
        int poll_count = poll(pfds, fd_count, -1);

        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        // processa as conexoes e eventos encontrados pelo poll
        process_connections(listener, &fd_count, &fd_size, &pfds);
    }

    // libera o espaco utilizado pelo array
    free(pfds);
}