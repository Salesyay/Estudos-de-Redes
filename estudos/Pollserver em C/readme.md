# Pollserver em C

Servidor TCP desenvolvido em C para estudar redes e o gerenciamento de múltiplas conexões utilizando `poll()`.

## Funcionalidades

- Gerenciamento de múltiplas conexões TCP.
- Monitoramento de sockets com `poll()`.
- Aceitação de novas conexões.
- Recebimento e envio de mensagens entre clientes.

## Compilação

```bash
gcc -Wall -Wextra -Wpedantic pollserver.c funcoes.c -o pollserver
```

## Execução

```bash
./pollserver
```

## Objetivo

Projeto desenvolvido para praticar programação de redes em C e compreender o funcionamento de servidores TCP com múltiplas conexões.
