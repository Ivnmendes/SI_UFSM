#include "fila.h"
#include <stdlib.h>

#include <stdio.h>

// Comando para compilar gcc -c fila.c -o fila.out && gcc -c t2.c -o t2.out && gcc fila.out t2.out -o main && ./main

typedef struct _fila {
    int max;
    int tot;
    int prim;
    int ult;
    dado_t *vet;
} fila;

// Cria uma fila alocando "max" elementos
Fila fila_cria(int max)
{
    Fila self = malloc(sizeof(fila));
    if (self == NULL) {
        return NULL;
    }

    self->vet = malloc(max * sizeof(dado_t));
    if (self->vet == NULL) {
        free(self);
        return NULL;
    }

    self->max = max;
    self->tot = 0;
    self->prim = 0;
    self->ult = -1;

    return self;
}

// Libera a memória da alocada
void fila_destroi(Fila self)
{
    free(self->vet);
    free(self);
}

// Insere um elemento na fila
void fila_insere(Fila self, dado_t d)
{
    if (!fila_cheia(self)) {
        self->ult = (self->ult + 1) % self->max; //revisar
        self->vet[self->ult] = d;
        self->tot++;
    }
}

// Remove um elemento da fila e o retorna
dado_t fila_remove(Fila self)
{
    if (!fila_vazia(self)) {
        dado_t aux = self->vet[self->prim];
        self->prim = (self->prim+1) & self->max; //revisar
        self->tot--;
        return aux;
    }
}

// Verifica se a fila esta vazia
bool fila_vazia(Fila self)
{
    return self->tot <= 0;
}

// Verifica se a fila esta cheia
bool fila_cheia(Fila self)
{
    return self->tot >= self->max;
}

void mostrarFila(Fila self){

	int cont, i;

	for ( cont = 0, i = self->prim; cont < self->tot; cont++){

		printf("%d\t", self->vet[i++]);

		if (i == self->max)
			i=0;

	}
	printf("\n\n");

} //