/*
 * pilha.h
 * Definição da TAD pilha_t com vetor.
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


#pragma once 


/* define o tipo pilha_t, derivado da 'struct _pilha' */
typedef struct _pilha pilha_t;

/* cria uma pilha vazia, sendo:
 * - alocar memória para a pilha (chamar malloc)
 * - atribuir o valor incial de elmentos da pilha (n = 0)
 * - retorna a pilha criada
 */
pilha_t* pilha_cria (void);

/* testa se a pilha esta vazia */
int pilha_vazia( pilha_t* p );

/* insere um elemento na pilha, sendo:
 * - verificar se a quantidade de elementos da pilha (p->n) é menor que o número máximo de elementos (N)
 * - próxima posição livre = p->n
 * - após atribuir o dado ao vetor, incrementa p->n 
 * 
 * Retorna 0 se não empilhou, 1 caso contrario.
 */
int pilha_empilha( pilha_t* p, void* dado );

/* Retorna o elemento no topo da pilha, sem desempilhar.
 * NULL caso a pilha seja vazia.
 */
void* pilha_topo( pilha_t* p ); 

/* retira o elemento do topo da pilha, sendo:
 * - verificar se a pilha está vazia (chamar função pilha vazia)
 * - topo da pilha = p->n-1
 * - após armazenar o dado, é preciso decrementar p->n antes de retorná-lo
 */
void pilha_desempilha( pilha_t* p ); 

/* destroi a pilha */
void pilha_destroi( pilha_t* p );
