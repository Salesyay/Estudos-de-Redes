#ifndef FUNCOES_H
#define FUNCOES_H

#include <stddef.h>
#include <poll.h>

#define PORT "3490"

const char *inet_ntop2(void *addr, char *buf, size_t size);

int get_listener_socket(void);

void handle_client_data(int listener, int *fd_count,
        struct pollfd *pfds, int *pfd_i);

void handle_new_connection(int listener, int *fd_count, int *fd_size,
        struct pollfd **pfds);

void brodcast(char *buf, int nbytes, int listener, int s, fd_set, *master, int fdmax)

#endif