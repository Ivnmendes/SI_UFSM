#include "fila.h"
#include <stdlib.h>

#include <stdio.h>

// Comando para compilar egcc -c fila.c -o fila.out && gcc -c main.c -o main.out && gcc fila.out main.out -o program.out && ./program.out

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
    if (fila_cheia(self)) {
        self->vet = realloc(self->vet, sizeof(dado_t) * (self->max * 2));
        self->max *= 2;
    }
    self->ult = (self->ult + 1) % self->max; //revisar
    self->vet[self->ult] = d;
    self->tot++;
}

// Remove um elemento da fila e o retorna
dado_t fila_remove(Fila self)
{
    if (!fila_vazia(self)) {
        dado_t aux = self->vet[self->prim];
        self->prim = (self->prim+1) % self->max; //revisar
        self->tot--;
        if (self->tot < self->max/3) {
            self->vet = realloc(self->vet, sizeof(dado_t) * (self->max / 2));
            self->max /= 2;
        }
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