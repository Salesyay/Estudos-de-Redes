# MiniTCP_messageServer

  Projeto desenvolvido a partir de [miniTCP_messageServer](https://github.com/Salesyay/Estudos-de-Redes/tree/main/estudos/miniTCP_messageServer), adaptando-o para usar <b>UDP</b> invés de TCP.

``` bash 
  Projeto base:
  [miniTCP_messageServer](https://github.com/Salesyay/Estudos-de-Redes/tree/main/estudos/miniTCP_messageServer)
```

  
## Sobre

Este projeto tem como objetivo 
estabelecer uma comunicação cliente-servidor utiluzando o protocolo <b>UDP</b>.

A ideia é usar o [servidor TCP](https://github.com/Salesyay/Estudos-de-Redes/tree/main/estudos/miniTCP_messageServer) como base e realizar alterações necessarias adapta-lo. Tudo isso com intuito estudantil, com foco em entender, na prática as diferenças diferenças entre uma comunicação orientada a conexão (TCP) e uma comunicação sem conexão (TCP).

## Principaos alterações

Em relação ao sercidor TCP foram feitas alterações em relação a como os dados são enciados e recebidos.

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

### Cliente:
Em outro terminal:
```bash
gcc client.c -o client
```

### Exemplo
#### Servidor
```bash
servidor: esperando conexão...
```

### Client
```bash
client: tentando conectar
Conectado ao servidor!
Mensagem do servidor: Olá, mundo!
```

### Observação
 Este projeto tem finalidade didática, e varia da versão [TCP](https://github.com/Salesyay/Estudos-de-Redes/tree/main/estudos/miniTCP_messageServer) para a comparação prática entre estes tipos de comunicação.
