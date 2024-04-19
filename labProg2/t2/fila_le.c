#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 1000

// comando para compilar e rodar: $gcc -Wall -o cobra cobra.c fila_le.c tela.c tecla.c && ./cobra

typedef struct _nodo nodo;
struct _nodo {
  void *dado;
  nodo *prox;
};

struct _fila {
  int n_elem;
  nodo *prim;
  nodo *ult;
  int tam_dado;
  int pos_percurso;
};

// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado) {
  Fila self = malloc(sizeof(struct _fila));
  assert(self != NULL);

  self->prim = NULL;
  self->ult = NULL;
  self->tam_dado = tam_do_dado;

  return self;
}

void fila_destroi(Fila self) {
  nodo *no = self->prim;

  while (no != NULL) {
    nodo *prox = no->prox;
    free(no->dado);
    free(no);
    no = prox;
  }
  free(self);
}

static nodo *fila_nodo_pos(Fila self, int pos) {
  nodo *no = self->prim;
  int p = 0;
  while(no != NULL && p < pos) {
    no = no->prox;
    p++;
  }
  return no;
}

// calcula o valor do ponteiro para o elemento na posição pos da fila
static void *calcula_ponteiro(Fila self, int pos)
{
  // TODO: suporte a pos negativa
  if (pos < 0) {
    pos += self->n_elem;
  }

  if (pos < 0 || pos >= self->n_elem) return NULL;
  // calcula a posição convertendo para char *, porque dá para somar em
  //   bytes. tem que fazer essa conversão porque não conhecemos o tipo
  //   do dado do usuário, só o tamanho.
  
  nodo *noNaPos = fila_nodo_pos(self, pos);
  return noNaPos->dado;
}

bool fila_vazia(Fila self) { return self->prim == NULL; }

static nodo *cria_nodo(Fila self, void *pdado, nodo *prox) {
  nodo *no = malloc(sizeof *no);
  assert(no != NULL);
  //no->dado = pdado;
  no->dado = malloc(self->tam_dado);
  assert(no->dado != NULL);
  memmove(no->dado, pdado, self->tam_dado);
  no->prox = prox;
  return no;
}

void fila_remove(Fila self, void *pdado) {
  assert(!fila_vazia(self));
  memmove(pdado, self->prim->dado, self->tam_dado);
  self->n_elem--;
  free(self->prim->dado);
  free(self->prim);
  if (self->n_elem == 0) {
    self->prim = NULL;
    self->ult = NULL;
  } else {
    self->ult->prox = self->prim->prox;
    self->prim = self->ult->prox;
  }
}

void fila_insere(Fila self, void *pdado) {
  if (fila_vazia(self)) {
    nodo *novo = cria_nodo(self, pdado, self->prim);
    self->prim = novo;
    self->ult = novo;
  } else {
    nodo *novo = cria_nodo(self, pdado, self->prim);

    self->ult->prox = novo;
    self->ult = novo;
    self->ult->prox = self->prim;
  }

  self->n_elem++;
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

//remover depois
void imprime_fila(Fila self) {
  printf("[ ");
  int cont = 0;
  for(nodo *no = self->prim; cont < self->n_elem; cont++, no = no->prox) {
    printf("%d ", * ((int*) ((char*) no->dado)));
  }
  printf("]\n");
}