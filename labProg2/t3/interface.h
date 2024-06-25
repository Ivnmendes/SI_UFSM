#ifndef _interface_h_
#define _interface_h_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "manipulaHistorico.h"

#include "estado.h"

void imprimeJogo(estado e); //Imprime a arvore, a palavra do usuario, a palavra do computador e o relogio

void imprimeMenu(float alturaTela, float larguraTela); //Imprime o menu de selecao

int testaBotaoMenu(int px, int py, float larguraTela, float alturaTela); //Testa se algum botao foi apertado, retorna um inteiro correspondente ao botao
// 2 = jogar
// 3 = historico
// 4 = sair
// qualquer outro numero = nenhum botao

void imprimeHistorico(float larguraTela, float alturaTela, int pontosHistorico[10]); //Imprime a tela de historico de partidas

bool testaBotaoHistorico(int px, int py, float alturaTela); //Testa se o botao de voltar foi apertado, retorna true se sim

void imprimeFimDeJogo(estado e); //Imprime a tela de fim de jogo

int testaBotaoFimDeJogo(float px, float py, float alturaTela, float larguraTela); //Testa se algum botao foi apertado, retorna 1 para recomecar a partida e 2 para voltar ao menu

void imprimeTelaPause(estado e); //Imprime a tela de pause

int testaBotaoPause(float px, float py, float alturaTela, float larguraTela); //Testa se algum botao foi apertado, retorna 1 para voltar a partida e 2 para voltar ao menu

#endif