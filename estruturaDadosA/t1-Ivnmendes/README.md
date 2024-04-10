
# TDD - Lista duplamente encadeada

Este é o código exemplo do trabalho usando TDD (*Test Driven Development*) com o framework C++ [Catch2](https://github.com/catchorg/Catch2).

## Tarefa

Modifique o arquivo [lista.c](lista.c) para completar as funções:
- `lista_insere`: insere um novo elemento na lista, retorna a lista atualizada, ou seja, o novo 1o elemento.
- `lista_destroi`: libera a memória de cada elemento da lista, não deve liberar a memória dos dados.

O resultado estará disponível na aba **Actions** do Github a cada alteração.

## Test Drive Development

O framework Catch2 consegue ser utilizado localmente com os arquivos [catch_amalgamated.hpp](catch_amalgamated.hpp)  e [catch_amalgamated.cpp](catch_amalgamated.cpp) sem necessidade de instalação.

**NÃO MODIFIQUE OS TESTES** 

O teste pode ser feito localmente com os comandos abaixo:
```
g++ -Wall -g -c catch_amalgamated.cpp
g++ -Wall -g -c testes.cpp
gcc -Wall -g -c lista.c
g++ -Wall -g lista.o testes.o  catch_amalgamated.o
valgrind --leak-check=full ./a.out --reporter compact --success
```