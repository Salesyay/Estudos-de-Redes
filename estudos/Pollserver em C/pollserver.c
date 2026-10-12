#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include "funcoes.h"

int main(void)
{
    int listener; // socket responsavel por receber novas conexoes

    int fd_size = 5; // capacidade inicial do array de descritores
    int fd_count = 0; // quantidade de descritores utilizados

    // espaco para armazenar os descritores monitorados pelo poll
    struct pollfd *pfds = malloc(sizeof *pfds * fd_size);

    // verifica se a alocacao de memoria foi realizada corretamente
    if (pfds == NULL) {
        perror("malloc");
        return 1;
    }

    // cria o socket responsavel por receber novas conexoes
    listener = get_listener_socket();

    // verifica se ocorreu um erro ao criar o socket do servidor
    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        free(pfds);
        return 1;
    }

    // adiciona o socket listener ao primeiro espaco do array
    pfds[0].fd = listener;

    // monitora o socket para verificar novas conexoes
    pfds[0].events = POLLIN;
    pfds[0].revents = 0;

    // atualiza a quantidade de descritores utilizados
    fd_count = 1;

    puts("pollserver: waiting for connections...");

    // mantem o servidor executando continuamente
    for (;;) {

        // espera algum dos sockets ficar pronto para comunicacao
        int poll_count = poll(pfds, fd_count, -1);

        // verifica se ocorreu um erro durante o monitoramento
        if (poll_count == -1) {
            perror("poll");
            break;
        }

        // processa as conexoes e eventos encontrados pelo poll
        process_connections(listener, &fd_count, &fd_size, &pfds);
    }

    // fecha o socket de escuta do servidor
    close(liste3r);

    // libera o espaco utilizado pelo array
    free(pfds);

    return 0;
}