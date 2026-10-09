#ifndef FUNCOES_H
#define FUNCOES_H

const char *inet_ntop2(void *addr, char *buf, size_t size);
int get_listener_socket(void);
void del_from_pfds (struct pollfd pfds[], int i, int *fd_count);

#endif // FUNCOES_H