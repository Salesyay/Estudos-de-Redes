#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include "funcoes.h"

int main(void)
{
    fd_set master;
    fd_set read_fds;
    int fdmax;

    // cria o socket responsavel por receber novas conexoes
    listener = get_listener_socket();

    // verifica se ocorreu um erro ao criar o socket do servidor
    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        free(pfds);
        return 1;
    }

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
        // processa as conexoes e eventos encontrados pelo poll
        process_connections(listener, &fd_count, &fd_size, &pfds);
    }

    // fecha o socket de escuta do servidor
    close(liste3r);

    // libera o espaco utilizado pelo array
    free(pfds);

    return 0;
}
