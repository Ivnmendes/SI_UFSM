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
#include "manipulaHistorico.h"

static void imprimePalavraDigitada(estado e) {
    char aux[] = "Palavra digitada:";
    tela_texto(e.tamanhoTela.larg - (e.tamanhoTela.larg * 0.90), e.tamanhoTela.alt - (e.tamanhoTela.alt / 25), 20, preto, aux);

    if (e.palavraAtual[0] != '\0') {
        tela_texto_dir(e.tamanhoTela.larg - (e.tamanhoTela.larg * 0.90) + strlen(aux) + 75, e.tamanhoTela.alt - (e.tamanhoTela.alt / 19), 20, vermelho, e.palavraAtual);
    }
}

static void imprimePalavraDoComputador(estado e) {
    char aux[] = "Palavra futura:";
    tela_texto(e.tamanhoTela.larg * 0.83, e.tamanhoTela.alt - (e.tamanhoTela.alt / 25), 20, preto, aux);
    if (e.palavraDoComputador != NULL) {
        tela_texto(e.tamanhoTela.larg * 0.85 + strlen(aux) + 100, e.tamanhoTela.alt - (e.tamanhoTela.alt / 25), 20, vermelho, e.palavraDoComputador);
    }
}

static void imprimeTempoTranscorrido(estado e) {
    char aux[100];
    sprintf(aux, "%.0fs", tela_relogio() - e.tempoInicial);
    tela_texto(e.tamanhoTela.larg/2, e.tamanhoTela.alt - (e.tamanhoTela.alt / 20), 20, preto, aux);
}

static void imprimePontuacao(estado e) {
    char aux[100];
    sprintf(aux, "%d", e.pontos);
    tela_texto(e.tamanhoTela.larg/2, e.tamanhoTela.alt - 15, 20, azul, aux);
}

static void imprimeBotao(float larg1, float alt1, float larg2, float alt2, float largTexto, float altTexto, float largRet, char* texto, int tLetra, int corLetra, int corFundo) {
    tela_retangulo(larg1, alt1, larg2, alt2, largRet, preto, corFundo);
    tela_texto(largTexto, altTexto, tLetra, corLetra, texto);
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

void imprimeMenu(float alturaTela, float larguraTela) {
    float altura1 = alturaTela / 2;
    float altura2 = alturaTela / 2 - 60;
    float largura1 = larguraTela / 2 + 100;
    float largura2 = larguraTela / 2 - 100;

    al_clear_to_color(al_map_rgb(255, 255, 255));

    tela_texto(larguraTela / 2, alturaTela / 4, 40, preto, "Jogo da Arvore");

    char* texto[] = {"Jogar", "Historico", "Sair"};

    for (int i = 0; i < 3; i++, altura1 += 70, altura2 += 70) {
        imprimeBotao(largura1, altura1, largura2, altura2, larguraTela / 2, altura1 - 30, 3, texto[i], 25, preto, branco);
    }
    
    tela_atualiza();
}

int testaBotaoMenu(int px, int py, float larguraTela, float alturaTela) {
    float altura1 = alturaTela / 2;
    float altura2 = alturaTela / 2 - 60;
    float largura1 = larguraTela / 2 + 100;
    float largura2 = larguraTela / 2 - 100;
    int retorno = 1;
    bool achou;
    
    while (!achou && retorno < 4) {
        if (px <= largura1 && px >= largura2) {
            if (py <= altura1 && py >= altura2) {
                achou = true;
            }
        }
        altura1 += 70;
        altura2 += 70;
        retorno++;
    }
    if (!achou) { retorno = 0; }
    return retorno;
}

void imprimeHistorico(float larguraTela, float alturaTela, int pontosHistorico[10]) {
    al_clear_to_color(al_map_rgb(255, 255, 255));
    tela_texto(larguraTela / 2, alturaTela / 10, 40, preto, "Historico");

    int i = 0;
    while(i < 10 && pontosHistorico[i] != 0) {
        char aux[100];
        sprintf(aux, "%d. %d", i + 1, pontosHistorico[i]);
        tela_texto(larguraTela / 2, alturaTela / 6 + i*30, 20, preto, aux);
        i++;
    }

    imprimeBotao(50, alturaTela - 100, 250, alturaTela - 30, 150, alturaTela - 70, 2, "Voltar", 40, preto, transparente);
    tela_atualiza();
}

bool testaBotaoHistorico(int px, int py, float alturaTela) {
    if (px <= 250 && px >= 50) {
        if (py <= alturaTela - 30 && py >= alturaTela - 100) {
            return true;
        }
    }

    return false;
}

void imprimeFimDeJogo(estado e) {
    tela_retangulo(e.tamanhoTela.larg / 2 - 300, e.tamanhoTela.alt / 2 - 300, e.tamanhoTela.larg / 2 + 300, e.tamanhoTela.alt / 2 - 100, 3, preto, branco);
    tela_texto(e.tamanhoTela.larg / 2, e.tamanhoTela.alt / 2 - 250, 20, preto, "Partida finalizada!");

    imprimeBotao(e.tamanhoTela.larg / 2 - 280, e.tamanhoTela.alt / 2 - 150, e.tamanhoTela.larg / 2 - 30, e.tamanhoTela.alt / 2 - 110,
    e.tamanhoTela.larg / 2 - 155, e.tamanhoTela.alt / 2 - 130,
    1, "Jogar novamente", 25, preto, branco);
    
    imprimeBotao(e.tamanhoTela.larg / 2 + 50, e.tamanhoTela.alt / 2 - 150, e.tamanhoTela.larg / 2 + 280, e.tamanhoTela.alt / 2 - 110,
    e.tamanhoTela.larg / 2 + 170, e.tamanhoTela.alt / 2 - 130,
    1, "Menu", 25, preto, branco);
    tela_atualiza();
}

int testaBotaoFimDeJogo(float px, float py, float alturaTela, float larguraTela) {
    if (py >= alturaTela / 2 - 150 && py <= alturaTela / 2 - 110) {
        if (px >= larguraTela / 2 - 280 && px <= larguraTela / 2 - 30) {
            return 1;
        }
        else if (px >= larguraTela / 2 + 50 && px <= larguraTela / 2 + 280) {
            return 2;
        }
    }

    return 0;
}

void imprimeTelaPause(estado e) {
    tela_retangulo(e.tamanhoTela.larg / 2 - 300, e.tamanhoTela.alt / 2 - 300, e.tamanhoTela.larg / 2 + 300, e.tamanhoTela.alt / 2 - 100, 3, preto, branco);
    tela_texto(e.tamanhoTela.larg / 2, e.tamanhoTela.alt / 2 - 250, 20, preto, "Jogo Parado");

    imprimeBotao(e.tamanhoTela.larg / 2 - 280, e.tamanhoTela.alt / 2 - 150, e.tamanhoTela.larg / 2 - 30, e.tamanhoTela.alt / 2 - 110,
    e.tamanhoTela.larg / 2 - 155, e.tamanhoTela.alt / 2 - 130,
    1, "Voltar ao jogo", 25, preto, branco);
    
    imprimeBotao(e.tamanhoTela.larg / 2 + 50, e.tamanhoTela.alt / 2 - 150, e.tamanhoTela.larg / 2 + 280, e.tamanhoTela.alt / 2 - 110,
    e.tamanhoTela.larg / 2 + 170, e.tamanhoTela.alt / 2 - 130,
    1, "Menu", 25, preto, branco);
    tela_atualiza();
}

int testaBotaoPause(float px, float py, float alturaTela, float larguraTela) {
    if (py >= alturaTela / 2 - 150 && py <= alturaTela / 2 - 110) {
        if (px >= larguraTela / 2 - 280 && px <= larguraTela / 2 - 30) {
            return 1;
        }
        else if (px >= larguraTela / 2 + 50 && px <= larguraTela / 2 + 280) {
            return 2;
        }
    }

    return 0;
}