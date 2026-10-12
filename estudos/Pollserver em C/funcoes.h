#ifndef FUNCOES_H
#define FUNCOES_H

const char *inet_ntop2(void *addr, char *buf, size_t size);
int get_listener_socket(void);
void del_from_pfds (struct pollfd pfds[], int i, int *fd_count);
void add_to_pfds(struct pollfd **pfds, int newfd, int *fd_count, int *fd_size);
void handle_client_data(int listener, int *fd_count,
        struct pollfd *pfds, int *pfd_i);
void handle_new_connection(int listener, int *fd_count, int *fd_size,
        struct pollfd **pfds);

#endif // FUNCOES_H