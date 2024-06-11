#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> //

#include "arvore.h"
#include "interface.h"
#include "telag.h"


void imprimeArvoreTela(estado e) {
    imprimeArvore(e.arvore, 0, altura(e.arvore));
}

void imprimePalavraDigitada(estado e) {
    char aux[] = "Palavra digitada:";
    tela_texto(e.tamanhoTela.larg - (e.tamanhoTela.larg * 0.90), e.tamanhoTela.alt - (e.tamanhoTela.alt / 25), 20, preto, aux);

    if (e.palavraAtual[0] != '\0') {
        tela_texto_dir(e.tamanhoTela.larg - (e.tamanhoTela.larg * 0.90) + strlen(aux) + 75, e.tamanhoTela.alt - (e.tamanhoTela.alt / 19), 20, vermelho, e.palavraAtual);
    }
}

void imprimePalavraDoComputador(estado e) {
    char aux[] = "Palavra futura:";
    tela_texto(e.tamanhoTela.larg * 0.85, e.tamanhoTela.alt - (e.tamanhoTela.alt / 25), 20, preto, aux);
    if (e.palavraDoComputador != NULL) {
        tela_texto(e.tamanhoTela.larg * 0.85 + strlen(aux) + 100, e.tamanhoTela.alt - (e.tamanhoTela.alt / 25), 20, vermelho, e.palavraDoComputador);
    }
}

void imprimeTempoTranscorrido(estado e) {
    char aux[100];
    sprintf(aux, "%.0fs", tela_relogio() - e.tempoInicial);
    tela_texto(e.tamanhoTela.larg/2, e.tamanhoTela.alt - (e.tamanhoTela.alt / 20), 20, preto, aux);
}

void imprimePontuacao(estado e) {
    char aux[100];
    sprintf(aux, "%d", e.pontos);
    tela_texto(e.tamanhoTela.larg/2, e.tamanhoTela.alt - 15, 20, azul, aux);
}

void imprimeJogo(estado e) {
    al_clear_to_color(al_map_rgb(255, 255, 255));
    imprimeArvore(e.arvore, 15, e.tamanhoTela.larg/2);
    imprimePalavraDoComputador(e);
    imprimePontuacao(e);
    imprimeTempoTranscorrido(e);
    imprimePalavraDigitada(e);
    tela_atualiza();
}