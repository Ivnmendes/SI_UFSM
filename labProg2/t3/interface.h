#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "estado.h"

void imprimeJogo(estado e); //Imprime a arvore, a palavra do usuario, a palavra do computador e o relogio

void imprimeMenu(float alturaTela, float larguraTela);

int testaBotaoMenu(int px, int py, float larguraTela, float alturaTela);

void imprimeHistorico();