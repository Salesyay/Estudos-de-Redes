# Inspetor de IP (showip)

 Ferramenta desenvolvida em C para resolução e visualização de endereços IP utilizando a API de socket do linux.

## Sobre 

 O Inspetor de IP utiliza do `getaddrinfo()` para obter informações sobre endereços IP e exibi-los em formato legivel.

## Conceitos estudados

-getaddrinfo();
-IPv4;
-IPv6;
-struct addrinfo;
-struct sockaddr;
-Resolução de nomes e endereços;
-Estruturas de endereçamento da API de sockets;

## Compilação

 Compilie utilizando o `GCC`:
##### gcc showip.c -o showip

## Execução
 Execute o programa o programa conjuntamente com o endereço ou hostname que desejca consultar, ex:
##### showip reddit.com

 O programa faz a resolução do problema e retorna as informações obtidas.

## Objetivo
 Este projeto tem como objetivo compreender e praticar os fundamentos da programação de redes em C, e entender como o sistema operacional representa, resolve e manipula endereços  de rede.

 ## Tecnologias
 -C;
 -POSIX socket;
 -Linux;
 


