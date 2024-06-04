#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include <allegro5/allegro.h>

#include "arvore.h"
#include "interface.h"
#include "telag.h"


void imprimeArvoreTela(estado e) {
//    tela_lincol(1, 1);
    imprimeArvore(e.arvore, 0, altura(e.arvore));
}

void imprimePalavraDigitada(estado e) {
    tela_texto(100, e.tamanhoTela.alt, 80, preto, "Palavra digitada:");
    if (e.palavraAtual[0] != '\0') {
        tela_texto_dir(strlen(e.palavraAtual) ,e.tamanhoTela.alt, 80, preto, e.palavraAtual); //nao ta funcionando ainda
    }
}

void imprimePalavraDoComputador(estado e) {
    tela_texto(e.tamanhoTela.larg - 150, e.tamanhoTela.alt, 80, preto, "Palavra futura:");
    if (e.palavraDoComputador != NULL) {
        tela_texto(e.tamanhoTela.larg - strlen(e.palavraDoComputador) - 50, e.tamanhoTela.alt, 80, preto, e.palavraDoComputador);
    }
}

void imprimeTempoTranscorrido(estado e) {
    char aux[100];
    sprintf(aux, "%.0fs", tela_relogio() - e.tempoInicial);
    tela_texto(e.tamanhoTela.larg/2, e.tamanhoTela.alt - 30, 80, preto, aux);
}

void imprimePontuacao(estado e) {
    char aux[100];
    sprintf(aux, "%d", e.pontos);
    tela_texto(e.tamanhoTela.larg/2, e.tamanhoTela.alt, 80, azul, aux);
}

void imprimeJogo(estado e) {
    //imprimeArvoreTela(e);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    imprimePalavraDoComputador(e);
    imprimePontuacao(e);
    imprimeTempoTranscorrido(e);
    imprimePalavraDigitada(e);
    tela_atualiza();
}