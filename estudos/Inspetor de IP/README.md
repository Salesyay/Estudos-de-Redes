# Inspetor de IP (showip)

 Ferramenta desenvolvida em C para resolução e visualização de endereços IP utilizando a API de socket do linux.<br>

## Sobre 

 O Inspetor de IP utiliza do `getaddrinfo()` para obter informações sobre endereços IP e exibi-los em formato legivel.<br>

## Conceitos estudados

-getaddrinfo();<br>
-IPv4;<br>
-IPv6;<br>
-struct addrinfo;<br>
-struct sockaddr;<br>
-Resolução de nomes e endereços;<br>
-Estruturas de endereçamento da API de sockets;<br>

## Compilação

 Compilie utilizando o `GCC`:<br>
 Exemplo:
##### gcc showip.c -o showip <br>

## Execução
 Execute o programa o programa conjuntamente com o endereço ou hostname que desejca consultar <br>
 Exemplo:
##### showip reddit.com

 O programa faz a resolução do problema e retorna as informações obtidas. <br>

## Objetivo
 Este projeto tem como objetivo compreender e praticar os fundamentos da programação de redes em C, e entender como o sistema operacional representa, resolve e manipula endereços  de rede.

 ## Tecnologias
 -C;<br>
 -POSIX socket;<br>
 -Linux;<br>
 


