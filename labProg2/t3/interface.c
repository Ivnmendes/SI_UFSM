#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "arvore.h"
#include "interface.h"
#include "tela.h"


void imprimeArvoreTela(estado e) {
    tela_lincol(1, 1);
    imprimeArvore(e.arvore, 0, altura(e.arvore));
}

void imprimePalavraDigitada(estado e) {
    if (e.palavraAtual[0] != '\0') {
        tela_lincol(e.tamanhoTela.lin - 1 , 1);
        printf("%s", e.palavraAtual);
    }
}

void imprimePalavraDoComputador(estado e) {
    if (e.palavraDoComputador != NULL) {
        tela_lincol(e.tamanhoTela.lin - 1 , e.tamanhoTela.col - strlen(e.palavraDoComputador));
        printf("%s", e.palavraDoComputador);
    }
}

void imprimeTempoTranscorrido(estado e) {
    tela_lincol(e.tamanhoTela.lin - 3, e.tamanhoTela.col/2);
    printf("%.0fs", tela_relogio() - e.tempoInicial);
}

void imprimePontuacao(estado e) {
    tela_lincol(e.tamanhoTela.lin - 1, e.tamanhoTela.col/2);
    printf("%d", e.pontos);
}

void imprimeJogo(estado e) {
    tela_limpa();
    imprimeArvoreTela(e);
    imprimePalavraDoComputador(e);
    imprimePontuacao(e);
    imprimeTempoTranscorrido(e);
    imprimePalavraDigitada(e);
    tela_atualiza();
}