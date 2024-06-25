#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "manipulaHistorico.h"

#include "estado.h"

void imprimeJogo(estado e); //Imprime a arvore, a palavra do usuario, a palavra do computador e o relogio

void imprimeMenu(float alturaTela, float larguraTela);

int testaBotaoMenu(int px, int py, float larguraTela, float alturaTela);

void imprimeHistorico(float larguraTela, float alturaTela, int pontosHistorico[10]);

bool testaBotaoHistorico(int px, int py, float alturaTela);

void imprimeFimDeJogo(estado e);

int testaBotaoFimDeJogo(float px, float py, float alturaTela, float larguraTela);

void imprimeTelaPause(estado e);

int testaBotaoPause(float px, float py, float alturaTela, float larguraTela);