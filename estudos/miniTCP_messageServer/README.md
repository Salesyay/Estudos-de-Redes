# MiniTCP_messageServer

Servidor TCP desenvolvido em C como estudo de programação de redes e
comunicação cliente-servidor.

## Sobre

Este programa implementa um servidor TCP capaz de aceitar conexões
de clientes utilizando sockets POSIX.

O servidor utiliza `getaddrinfo()` para obter endereços compatíveis
com IPv4 e IPv6 e cria um processo filho para atender cada conexão.

## Conceitos estudados

- TCP
- Socket programming
- `getaddrinfo()`
- `socket()`
- `setsockopt()`
- `bind()`
- `listen()`
- `accept()`
- `fork()`
- `send()`
- `SIGCHLD`
- `waitpid()`
- IPv4 e IPv6

## Estrutura

- `server.c` — implementação do servidor
- `client.c` — cliente utilizado para testar a comunicação

## Compilação

```bash
gcc server.c -o server
gcc client.c -o client