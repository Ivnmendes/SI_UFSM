#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 1000

struct _fila {
  int max;
  int n_elem;
  int tam_dado;
  int prim;
  int ult;
  int pos_percurso;
  void *espaco;
};

// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado) {
  Fila self = malloc(sizeof(struct _fila));
  if (self != NULL) {
    self->espaco = malloc(10 * tam_do_dado);
    if (self->espaco != NULL) {
      self->max = 10;
      self->n_elem = 0;
      self->prim = 0;
      self->ult = -1;
      self->tam_dado = tam_do_dado;
    } else {
      free(self);
      self = NULL;
    }
  }
  return self;
}

void fila_destroi(Fila self) {
  free(self->espaco);
  free(self);
}

// calcula o valor do ponteiro para o elemento na posição pos da fila
static void *calcula_ponteiro(Fila self, int pos)
{
  // TODO: suporte a pos negativa
  if (pos < 0) {
    pos += self->max;
  }
  //
  if (pos < 0 || pos >= self->n_elem) return NULL;
  // calcula a posição convertendo para char *, porque dá para somar em
  //   bytes. tem que fazer essa conversão porque não conhecemos o tipo
  //   do dado do usuário, só o tamanho.
  void *ptr = (char *)self->espaco + pos * self->tam_dado;
  return ptr;
}

bool fila_vazia(Fila self) { return self->n_elem == 0; }

bool fila_cheia(Fila self) { return self->n_elem == self->max; }

void fila_remove(Fila self, void *pdado) {
  assert(!fila_vazia(self));
  void *ptr = calcula_ponteiro(self, self->prim)/*(self->prim - self->prim) % self->max)*/;
  assert(ptr != NULL);
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  self->n_elem--;
  if (self->prim == self->n_elem) {
    self->prim = 0;
  }
  self->prim++;
  if (self->n_elem < self->max / 3) {
    self->espaco = realloc(self->espaco, self->tam_dado * (self->max / 2));
    self->max /= 2;
  }
}

void fila_insere(Fila self, void *pdado) {
  if (fila_cheia(self)) {
    self->espaco = realloc(self->espaco, self->tam_dado * (self->max * 2));
    assert(self->espaco != NULL);
    self->max *= 2;
  }
  if (self->ult == self->n_elem-1) {
    self->ult = -1;
  }
  self->ult++;
  self->n_elem++;
  void *ptr = calcula_ponteiro(self, self->ult)/*(self->ult - (self->n_elem - 1)) % self->max)*/;
  assert(ptr != NULL);
  memmove(ptr, pdado, self->tam_dado);
}


void fila_inicia_percurso(Fila self, int pos_inicial)
{
  self->pos_percurso = pos_inicial;
}

bool fila_proximo(Fila self, void *pdado)
{
  void *ptr = calcula_ponteiro(self, self->pos_percurso);
  if (ptr == NULL) return false;
  memmove(pdado, ptr, self->tam_dado);
  if (self->pos_percurso < 0) {
    self->pos_percurso--;
  } else {
    self->pos_percurso++;
  }
  return true;
}
