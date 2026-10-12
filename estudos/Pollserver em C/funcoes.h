#ifndef FUNCOES_H
#define FUNCOES_H

#include <stddef.h>
#include <poll.h>

#define PORT "3490"

const char *inet_ntop2(void *addr, char *buf, size_t size);

int get_listener_socket(void);

void add_to_pfds(struct pollfd **pfds, int newfd,
        int *fd_count, int *fd_size);

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count);

void handle_client_data(int listener, int *fd_count,
        struct pollfd *pfds, int *pfd_i);

void handle_new_connection(int listener, int *fd_count, int *fd_size,
        struct pollfd **pfds);

void process_connections(int listener, int *fd_count, int *fd_size,
        struct pollfd **pfds);

#endif