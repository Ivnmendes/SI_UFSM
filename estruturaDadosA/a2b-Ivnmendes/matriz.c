/*
 * matriz.c
 * Exercício sobre TAD matriz.
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
#include <string.h>
#include <time.h>

#include "matriz.h"


/* Aloca uma matriz NxM e retorna um vetor de ponteiros (int**) */
int** matriz_aloca(const int N)
{
	if (N < 1) {
		return NULL;
	}
	
	int **mat = (int **) malloc(N * sizeof(int*));
	if (mat == NULL) {
		return NULL;
	}

	for (int i = 0; i < N; i++) {
		mat[i] = (int*) malloc(N * sizeof(int));
		if(mat[i] == NULL) {
			return NULL;
		}
	}

	return mat;
}


void matriz_multiplica(int** const A, int** const B, int** const C, 
		const int N)
{
	/* Algoritmo da multiplicação:
	para i menor que N
		para j menor que N
			para k menor que N
				C[i][j] = A[i][k] * B[k][j] + C[i][j]
	*/
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				C[i][j] = A[i][k] * B[k][j] + C[i][j];
			}
		}
	}
}


void matriz_libera(int** A, const int N)
{
	/* libera toda a memória */
	for (int i = 0; i < N; i++) {
		if(A[i] != NULL) {
			free(A[i]);
		}
	}

	if (A != NULL) {
		free(A);
	}
}


/* função PRONTA */
void matriz_imprime(int** const A, const int N)
{
	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%4d ", A[i][j]);
		}
		printf("\n");
	}	
}

/* função PRONTA */
void matriz_inicia(int** const A, const int N)
{
	int i, j;

	/* inicia a sequencia de números pseudo-aleatórios rand() baseado no tempo */
	srand(time(NULL));
	/* inicializa a matriz */
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			A[i][j] = (rand() % N)+1; /* garante um número sempre não-zero */
		}
	}	
}

/* função PRONTA */
void matriz_copia(int** const dest, int** const orig, const int N)
{
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			dest[i][j] = orig[i][j];
		}
	}	

}

/* função PRONTA */
int matriz_compara(int** const A, int** const B, const int N)
{
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if( A[i][j] != B[i][j] ) 
				return 0; /* não são iguais */
		}
	}	

	return 1; /* tudo igual */
}
