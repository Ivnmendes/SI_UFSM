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
      self->max = 5;
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
  if (pos < 0 || pos >= self->max) return NULL;
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
  void *ptr = calcula_ponteiro(self, self->prim);
  assert(ptr != NULL);
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  self->prim = (self->prim + 1) % self->max;
  self->n_elem--;
  if (self->n_elem < self->max / 3) {
    self->espaco = realloc(self->espaco, self->tam_dado * (self->max / 2));
    self->max /= 2;
  }
}

void fila_insere(Fila self, void *pdado) {
  if (fila_cheia(self)) {
    int novoMax = self->max * 2;
    void *listaAux = malloc(novoMax * self->tam_dado);
    assert(listaAux != NULL);
    if (self->ult > self->prim) {
      memmove(listaAux, self->espaco + self->prim, self->n_elem * self->tam_dado);
    } else {
      memmove(listaAux, self->espaco + self->prim, self->tam_dado * (self->max - self->prim));
      memmove(listaAux + (self->tam_dado * (self->max - self->prim)), self->espaco, self->tam_dado * (self->ult + 1));
    }

    free(self->espaco);
    self->espaco = listaAux;
    self->prim = 0;
    self->ult = self->max - 1;
    self->max *= 2;
  }
  self->ult = (self->ult + 1) % self->max;
  void *ptr = calcula_ponteiro(self, self->ult);
  self->n_elem++;
  assert(ptr != NULL);
  memmove(ptr, pdado, self->tam_dado);
}

//remover depois
void imprime_fila(Fila self) {
  int cont, i;

  printf("[ ");
  for(cont = 0, i = self->prim; cont < self->n_elem; cont++) {
    printf("%d ", * ((int*) (self->espaco + i * self->tam_dado)));

    i = (i + 1) % self->max;
  }
  printf("]\n");
  printf("max: %d prim:%d ult:%d n_elem:%d\n", self->max,self->prim,self->ult,self->n_elem);
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
