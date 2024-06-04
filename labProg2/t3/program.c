// comando para compilar: gcc -Wall -o arvore.o arvore.c program.c sorteioPalavras.c tela.c tecla.c interface.c tamTela.h estado.h
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arvore.h"
#include "interface.h"
#include "sorteioPalavras.h"
#include "tecla.h"
#include "tela.h"

#include "tamTela.h"
#include "estado.h"

void testeArvore() {
    arv_t* arvore = cria_arv_vazia();

    assert(estaVazia(arvore));

    arvore = insereElem(arvore, "abc");
    arvore = insereElem(arvore, "def");
    arvore = insereElem(arvore, "hij");
    arvore = insereElem(arvore, "klm");
    arvore = insereElem(arvore, "nop");
    arvore = insereElem(arvore, "mop");
    arvore = insereElem(arvore, "map");
    arvore = insereElem(arvore, "kap");

    assert(!estaVazia(arvore));

    imprimeArvore(arvore, 0, altura(arvore));
    printf("\n\n");
    printInOrder(arvore);

    removeElem(&arvore, "nop");

    imprimeArvore(arvore, 0, altura(arvore));
    printf("\n\n");
    printInOrder(arvore);
}

bool iniciaJogo(estado* e) {
    tecla_ini();

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

    e->tamanhoTela.lin = tela_nlin();
    e->tamanhoTela.col = tela_ncol();

    e->tempoInicial = tela_relogio();

    e->equilibrada = true;

    e->estado = normal;
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
    tecla_fim();
}

void leituraDeTecla(estado* e) {
    char aux;
    aux = tecla_le_char();
    size_t tam = strlen(e->palavraAtual);
    if(aux >= 'a' && aux <= 'z') {
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
    }
}

void inserePalavra(estado* e) {
    if(e->palavraDoComputador == NULL) {
        sorteiaPalavra(&e->palavraDoComputador, e->silabas);
        e->tempoInsercao = tela_relogio();
        e->tempoSorteado = rand() % 4 + 1; //Garante que o tempo mínimo é de 1 segundo
    } else if (tela_relogio() - e->tempoInsercao >= e->tempoSorteado) {
        e->arvore = insereElem(e->arvore, e->palavraDoComputador);
        e->equilibrada = estaEquilibrado(e->arvore);

        free(e->palavraDoComputador);
        e->palavraDoComputador = NULL;
        e->tempoInsercao = 0;
        e->tempoSorteado = 0;
    }
}

typedef enum {jogo, historico, sair} modoJogo;

int main() {
    srand(time(NULL));
    tela_ini();
    estado jogo;
    iniciaJogo(&jogo);

    while (jogo.equilibrada) {
        switch(jogo.estado) {
            case normal:
                leituraDeTecla(&jogo);
                inserePalavra(&jogo);        
                imprimeJogo(jogo);
                break;
            case desequilibrado:
                break;
            case parado:
                break;
            default:
                break;
        }
    }
    finalizaJogo(&jogo);

    tela_fim();
    printf("Finalizado\n");
    return 0;
}