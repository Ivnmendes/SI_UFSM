// comando para compilar: gcc -Wall -o arvore.o arvore.c program.c sorteioPalavras.c telag.c interface.c tamTela.h estado.h -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arvore.h"
#include "interface.h"
#include "sorteioPalavras.h"
#include "telag.h"
#include "manipulaHistorico.h"

#include "tamTela.h"
#include "estado.h"

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

bool iniciaJogo(estado* e) {
    e->pontos = 0;
    e->arvore = cria_arv_vazia();
    if(!leArquivoSilabas(e->silabas)) {
        printf("Nao foi possivel ler o arquivo de silabas!\n");
        return false;
    }

    char* palavraAtual = malloc(sizeof(char));
    if(palavraAtual == NULL) {
        printf("Erro: Falta de memoria");
        return false;
    }
    palavraAtual[0] = '\0';
    e->palavraAtual = palavraAtual;

    e->palavraDoComputador = NULL;

    e->tamanhoTela.larg = LARGURA_TELA;
    e->tamanhoTela.alt = ALTURA_TELA;

    e->tempoInicial = tela_relogio();

    e->equilibrada = true;

    e->estado = jogando;
    return true;
}

void finalizaJogo(estado* e) {
    destroiArvore(e->arvore);
    liberaSilabas(e->silabas);
    if(e->palavraAtual != NULL) {
        free(e->palavraAtual);
    }
    if(e->palavraDoComputador != NULL) {
        free(e->palavraDoComputador);
    }
}

void leituraDeTecla(estado* e) {
    char aux;
    aux = tela_tecla();
    size_t tam = strlen(e->palavraAtual);
    if(strlen(e->palavraAtual) < 15 && aux >= 'a' && aux <= 'z') { //strlen(x) < 15... testa se a palavra digitada ja e grande demais, evitando bugs visuais
        e->palavraAtual = realloc(e->palavraAtual, tam + 2); //Aumenta a memoria alocada para incluir a nova letra e o \0
        assert(e->palavraAtual != NULL);
        e->palavraAtual[tam] = aux;
        e->palavraAtual[tam + 1] = '\0';
    } else if(aux == '\b') {
        if(tam > 0) {
            e->palavraAtual[tam - 1] = '\0';
            e->palavraAtual = realloc(e->palavraAtual, tam); //Diminui a memoria alocada
            assert(e->palavraAtual != NULL);
        }
    } else if(aux == '\n') {
        if(tam > 0) {
            int pontAux = strlen(e->palavraAtual) * 100;
            if (removeElem(&e->arvore, e->palavraAtual)) {
                e->pontos += pontAux;
            } else {
                if(e->pontos >= pontAux) {
                    e->pontos -= pontAux;
                }
            }

            // retorna a palavra ao estado 0
            free(e->palavraAtual);
            e->palavraAtual = malloc(1);
            assert(e->palavraAtual != NULL);
            e->palavraAtual[0] = '\0';
        }
    } else if (aux == '\e') {
        e->estado = parado;
    }
}

void inserePalavra(estado* e) {
    if(e->palavraDoComputador == NULL) {
        sorteiaPalavra(&e->palavraDoComputador, e->silabas);
        e->tempoInsercao = tela_relogio();
        e->tempoSorteado = rand() % 6 + 1 - (tela_relogio() - e->tempoInicial) / 20; // Garante que o tempo mínimo é de 1 segundo
        // Se passaram-se 20 segundos reduz 1 segundo do tempo de insercao, se 40 reduz dois...
    } else if (tela_relogio() - e->tempoInsercao >= e->tempoSorteado) {
        e->arvore = insereElem(e->arvore, e->palavraDoComputador);
        e->equilibrada = estaEquilibrado(e->arvore);

        free(e->palavraDoComputador);
        e->palavraDoComputador = NULL;
        e->tempoInsercao = 0;
        e->tempoSorteado = 0;
    }
}

void iniciaVetoresHistorico(int pontosHistorico[10]) {
    for (int i = 0; i < 10; i++) {
        pontosHistorico[i] = 0;
    }
}

bool verificaPontuacao(estado e, int pontosHistorico[10]) {
    int posAtualizar = verificaHistorico(e.pontos, pontosHistorico);
    if (posAtualizar != -1) {
        atualizaHistorico(posAtualizar, e.pontos, pontosHistorico);
        return escreveHistorico(pontosHistorico);
    }

    return true;
}

typedef enum {menu, partida, exibeHistorico, sair} modoJogo;

int main() {
    srand(time(NULL));
    tela_inicio(LARGURA_TELA, ALTURA_TELA, "jogo da arvore");
    modoJogo modoAtual = menu;
    int pontosHistorico[10];

    iniciaVetoresHistorico(pontosHistorico);
    if (!leHistorico(pontosHistorico)) {
        printf("Nao foi possivel abrir o arquivo do historico, programa encerrado!");
        return -1;
    }


    while (modoAtual != sair) {
        switch (modoAtual) {
        case menu:
            imprimeMenu(ALTURA_TELA, LARGURA_TELA);
            if (tela_rato_apertado()) {
                int px, py;
                tela_rato_pos(&px, &py);
                
                int opMenu = testaBotaoMenu(px, py, LARGURA_TELA, ALTURA_TELA);

                switch (opMenu) {
                case 2:
                    modoAtual = partida;
                    break;
                case 3:
                    modoAtual = exibeHistorico;
                    break;
                case 4:
                    modoAtual = sair;
                    break;
                default:
                    break;
                }
            }
            break;
        case partida:
            estado jogo;
            iniciaJogo(&jogo);
            while (jogo.estado != final) {
                switch(jogo.estado) {
                    case jogando:
                        leituraDeTecla(&jogo);
                        inserePalavra(&jogo);        
                        imprimeJogo(jogo);
                        if (!jogo.equilibrada) { jogo.estado = finalizando; }
                        break;
                    case parado:
                        imprimeTelaPause(jogo);
                        if (tela_rato_apertado()) {
                            int px, py;
                            tela_rato_pos(&px, &py);

                            int botaoPause = testaBotaoPause(px, py, jogo.tamanhoTela.alt, jogo.tamanhoTela.larg);
                            if (botaoPause == 1) {
                                jogo.estado = jogando;
                            } else if (botaoPause == 2) {
                                jogo.estado = final;
                                modoAtual = menu;
                            }
                        }                            
                        break;
                    case finalizando:
                        imprimeFimDeJogo(jogo);
                        if (tela_rato_apertado()) {
                            int px, py;
                            tela_rato_pos(&px, &py);

                            int botaoFimDeJogo = testaBotaoFimDeJogo(px, py, jogo.tamanhoTela.alt, jogo.tamanhoTela.larg);
                            if (botaoFimDeJogo == 1) {
                                if (!verificaPontuacao(jogo, pontosHistorico)) {
                                    printf("Nao foi possivel salvar a pontuacao no historico!\n");
                                    return -1;
                                }
                                jogo.estado = final;
                            } else if (botaoFimDeJogo == 2) {
                                if (!verificaPontuacao(jogo, pontosHistorico)) {
                                    printf("Nao foi possivel salvar a pontuacao no historico!\n");
                                    return -1;
                                }
                                modoAtual = menu;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
            finalizaJogo(&jogo);
            jogo.estado = final;
            break;
        case exibeHistorico:
            imprimeHistorico(LARGURA_TELA, ALTURA_TELA, pontosHistorico);
            if (tela_rato_apertado()) {
                int px, py;
                tela_rato_pos(&px, &py);

                if(testaBotaoHistorico(px, py, ALTURA_TELA)) {
                    modoAtual = menu;
                }
            }
            break;
        default:
            printf("erro desconhecido!\n");
            return -1;
            break;
        }
    }
    tela_fim();
    return 0;
}