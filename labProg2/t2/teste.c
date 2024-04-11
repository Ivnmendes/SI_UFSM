#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

int main(int argc, char const *argv[])
{
    Fila f = fila_cria(sizeof(int));

    int *x = (int*) malloc(sizeof(int));
    int *y = (int*) malloc(sizeof(int));
    do {
        scanf("%d", x);
        if (*x == -2) {
            fila_remove(f, y);
            printf("dado removido: %d\n", (int) *y);
        } else {
            fila_insere(f, x);
        }
        imprime_fila(f);
    } while (*x != -1);

    // int *x = (int*) malloc(sizeof(int));
    // int *y = (int*) malloc(sizeof(int));
    // int *z = (int*) malloc(sizeof(int));

    // *x = 10;
    // *y = 20;
    // *z = 30;

    // fila_insere(f, x);
    // imprime_fila(f);
    // fila_insere(f, y);
    // imprime_fila(f);
    // fila_insere(f, z);
    // imprime_fila(f);

    fila_destroi(f);
    return 0;
}
