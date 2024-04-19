/*
 * testes.cpp
 * Exercício sobre TAD lista.
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

/* NÃO MUDAR ESSSE ARQUIVO!!!*/

#include "catch_amalgamated.hpp"

#include <cstring>
#include <cstdlib>

extern "C" {
    #include "pilha.h"

typedef struct {
	int		x;
	int		y;
} ponto_t;

}


int compara(void *a, void *b)
{
	/* primeiro faz typecast dos ponteiros para ponto_t */
	ponto_t        *p1 = (ponto_t *) a;
	ponto_t        *p2 = (ponto_t *) b;

	/* compara os pontos aqui */
	if ((p1->x == p2->x) && (p1->y == p2->y))
		return 1;

	return 0;
}

TEST_CASE("teste inicial 1") {
    pilha_t *p;
    p = pilha_cria();
    REQUIRE( pilha_vazia(p) != 0 );
    pilha_destroi(p);
}

TEST_CASE("teste inicial 2") {
    pilha_t *p;
    ponto_t        *p1;
    p = pilha_cria();
    REQUIRE( pilha_vazia(p) != 0 );
    p1 = (ponto_t *) malloc(sizeof(ponto_t));
	p1->x = p1->y = 1.0;
    pilha_empilha(p, p1);
    REQUIRE( pilha_vazia(p) == 0 );
    pilha_destroi(p);
    free(p1);
}

TEST_CASE("teste inicial 3") {
    pilha_t *p;
    ponto_t        *p1;
    p = pilha_cria();
    REQUIRE( pilha_vazia(p) != 0 );
    p1 = (ponto_t *) malloc(sizeof(ponto_t));
	p1->x = p1->y = 1.0;
    pilha_empilha(p, p1);
    REQUIRE( pilha_vazia(p) == 0 );
    pilha_desempilha(p);
    REQUIRE( pilha_vazia(p) != 0 );
    pilha_destroi(p);
    free(p1);
}

TEST_CASE("teste empilha 1") {
    pilha_t *p;
    p = pilha_cria();
    ponto_t        *p1, *p2, *px;
    REQUIRE( pilha_vazia(p) != 0 );
    p1 = (ponto_t *) malloc(sizeof(ponto_t));
	p1->x = p1->y = 1.0;
	p2 = (ponto_t *) malloc(sizeof(ponto_t));
	p2->x = p2->y = 2.0;
    pilha_empilha(p, p1);
    pilha_empilha(p, p2);
    REQUIRE( pilha_vazia(p) == 0 );
    px = (ponto_t*)pilha_topo(p);
    pilha_desempilha(p);
    REQUIRE( compara(px, p2) == 1 );
    REQUIRE( pilha_vazia(p) == 0 );
    px = (ponto_t*)pilha_topo(p);
    pilha_desempilha(p);
    REQUIRE( compara(px, p1) == 1 );
    REQUIRE( pilha_vazia(p) != 0 );
    pilha_destroi(p);
    free(p1);
    free(p2);
}

TEST_CASE("teste erro") {
    pilha_t *p;
    ponto_t        *p1;
    p = pilha_cria();
    REQUIRE( pilha_vazia(p) != 0 );
    p1 = (ponto_t *) malloc(sizeof(ponto_t));
	p1->x = p1->y = 1.0;
    pilha_empilha(p, p1);
    REQUIRE( pilha_vazia(p) == 0 );
    pilha_desempilha(p);
    REQUIRE( pilha_vazia(p) != 0 );
    pilha_desempilha(p);
    REQUIRE( pilha_vazia(p) != 0 );
    REQUIRE( pilha_topo(p) == NULL );
    pilha_destroi(p);
    free(p1);
}

