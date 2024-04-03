#ifndef _FILA_H_
#define _FILA_H_

#include <stdbool.h>

typedef struct _fila *Fila;
typedef int dado_t;

Fila fila_cria(int max);

void fila_destroi(Fila self);

void fila_insere(Fila self, dado_t d);

dado_t fila_remove(Fila self);

bool fila_vazia(Fila self);

bool fila_cheia(Fila self);

void mostrarFila(Fila self); //

#endif