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
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(listener, &master);
    fdmax = listener;

    for(;;) {
      read_fds = master;
      if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
        perror("select")
        exit(4);
      }
    }
    return 0;
}
