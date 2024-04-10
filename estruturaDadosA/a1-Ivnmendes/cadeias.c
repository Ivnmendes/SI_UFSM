/*
 * cadeias.c
 * Exercício sobre cadeias de caracteres.
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

	#include "cadeias.h"


	/* junta as strings de 'dest' e 'orig' 
		Retorna um novo ponteiro com as duas juntas
	*/
	char* concatena(const char* dest, const char* orig)
	{
		/* TODO faça a função aqui! */
		char *aux;

		aux = (char *) malloc(sizeof(dest) + sizeof(orig) + 1);
		if (aux == NULL) {
			return  NULL;
		}

		strcpy(aux, dest);
		strcat(aux, orig);

		return aux;
	}

/* Recebe um texto 'texto' como entrada e um caractere 'c'
	Retorna um vetor de char* com a quebra das palavras.
*/
char** quebra_palavras(const char* texto, char c) 
{	//essa eu fiz acompanhando a explicação
	char **aux;
	char *token;
	char *textoAux = strdup(texto);
	int contPalavras = 0;
	char anterior = 0;
	char delim[2] = {c, '\0'};

	for (int i = 0; i < strlen(texto); i++) {
		if (texto[i] == c && anterior != c) {
			contPalavras++;
		}
		anterior = texto[i];
	}

	aux = (char **) calloc(contPalavras + 1, sizeof(char*));
	if (aux == NULL) {
		return NULL;
	}

	int i = 0;
	token = strtok(textoAux, delim);

	while(token != NULL) {
		int tam = strlen(token);
		char* palavra = (char*) malloc((tam + 1) * sizeof(char));
		strcpy(palavra, token);
		aux[i] = palavra;
		token = strtok(NULL, delim);
		i++;
	}

	free(textoAux);
	return aux;
}
