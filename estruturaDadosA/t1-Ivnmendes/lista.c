/*
 * lista.c
 * Implementação da TAD lista_t.
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2024 João Vicente, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

/* define a struct TAD lista duplamente encadeada */
struct _lista {
  void* dado;	      /* ponteiro para o dado (tipo void*) */
  struct _lista *ant; /* ponteiro para o elemento anterior */
  struct _lista *prox; /* ponteiro para o proximo elemento */
};

/* insere no comeco da lista, retorna a lista atualizada */
lista_t* lista_insere( lista_t* l, void* dado )
{
	/* TODO fazer inserção nessa aula */
	lista_t* aux = (lista_t*) malloc(sizeof(lista_t));
	aux->dado = dado;
	aux->prox = l;
	aux->ant = NULL;

	if (l != NULL) {
		l->ant = aux;
	}

	return aux;
}

/* remove da lista o elemento que contem 'dado'.
   Se lista ficar vazia, retorna NULL.
   Se encontrou, o elemento da lista deve ser liberado com free(). ATENCAO: nao liberar o dado.
   Se nao encontrou, retorna a lista 'l'.
*/
lista_t* lista_remove( lista_t* l, void* dado, int (*f)(void*, void*)  )
{
	lista_t* aux = l;

	while( lista_vazia(aux) == 0 ){
		if( f(aux->dado, dado) == 1 ) {
			break;
		}
		aux = aux->prox;
	}

	if (aux == NULL) {
		return l;
	}

	if (l == aux) {
		l = aux->prox;
	} else {
		aux->ant->prox = aux->prox;
	}

	if (aux->prox != NULL) {
		aux->prox->ant = aux->ant;
	}

	free(aux);

	if(lista_vazia(l)) {
		return NULL;
	}

	return l;
}

/* libera a memória de cada nó da lista.
 * ATENÇÃO: não libera memória dos dados.
 */
void lista_destroi( lista_t* l )
{
	/* TODO libera toda a lista */
	lista_t* aux = l;
	while (aux != NULL) {
		lista_t* aux2 = aux->prox;
		free(aux);
		aux = aux2;
	}
}


/* cria lista vazia */
lista_t* lista_cria(void)
{
	return NULL;
}

/* retorna se a lista esta vazia (true), ou false caso contrario */
int lista_vazia( lista_t* l )
{
	return (l == NULL);
}

/* busca um elemento na lista por meio da funcao f():
  bool f(void* a, void* b) {}
  que retonar 'true' caso a e b sejam iguais.
*/
int lista_busca( lista_t* l, void* dado, int (*f)(void*, void*)  )
{
	lista_t* primeiro = l;

	while( lista_vazia(primeiro) == 0 ){
		if( f(primeiro->dado, dado) == 1 )
			return 1;

		primeiro = primeiro->prox;
	}
	return 0;
}

