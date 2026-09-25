# MiniTCP_messageServer

 Este projeto é uma copia de com alterações para adapta-lo a Datagram Sockets de: https://github.com/Salesyay/Estudos-de-Redes/tree/main/estudos/miniTCP_messageServer

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
- `recv()`
- `SIGCHLD`
- `waitpid()`
- IPv4 e IPv6

## Estrutura

- `server.c` — implementação do servidor
- `client.c` — cliente utilizado para testar a comunicação

## Compilação

### servidor:

Compile o servidor:
```bash
gcc server.c -o server
```
Execute:
``` bash
./server
```

O servidor ficará aguardando conexões na porta "8000".
gcc client.c -o client

### Cliente:
Em outro terminal:
```bash
gcc client.c -o client
```
Execute utilizando o hostname ou endereço IP do servidor:
```bash
./client localhost
```
Em uma máquina diferente da mesma rede, pode ser utilizado o endereço IP do computador que está executando o servidor:
```bash
./client 192.168.1.10
```

### Exemplo
#### Servidor
```bash
servidor: esperando conexão...
servidor foi conectado a 127.0.0.1
```

### Client
```bash
client: tentando conectar em 127.0.0.1
Conectado ao servidor!
Mensagem do servidor: Olá, mundo!
```