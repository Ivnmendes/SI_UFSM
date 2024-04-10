[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/wf5iTTlN)

# TDD - Multiplicação de matrizes

Este é o código exemplo do trabalho usando TDD (*Test Driven Development*) com o framework C++ [Catch2](https://github.com/catchorg/Catch2).

## Tarefa

Modifique o arquivo [matriz.c](matriz.c) para completar as funções:
- `matriz_aloca`: aloca memória para uma matriz `A[N][N]` e retorna um `**int`
- `matriz_libera`: libera memória alocada previamente por `**A`
- `matriz_multiplica`: multiplica as matrizes `A` e  `B` no formato `C = AB + C`

O resultado estará disponível na aba **Actions** do Github a cada alteração.


## Test Drive Development

O framework Catch2 consegue ser utilizado localmente com os arquivos [catch_amalgamated.hpp](catch_amalgamated.hpp)  e [catch_amalgamated.cpp](catch_amalgamated.cpp) sem necessidade de instalação.

**NÃO MODIFIQUE OS TESTES** 

O teste pode ser feito localmente com os comandos abaixo:
```
g++ -Wall -g -c catch_amalgamated.cpp
g++ -Wall -g -c testes.cpp
gcc -Wall -g -c matriz.c
g++ -Wall -g matriz.o testes.o  catch_amalgamated.o
valgrind --leak-check=full ./a.out --reporter compact --success
```