#ifndef ESTADO
#define ESTADO

#include "tamTela.h"
#include "arvore.h"

typedef struct {
    int pontos;
    double tempoInicial;
    arv_t* arvore;
    char* silabas[185];
    char* palavraAtual;
    char* palavraDoComputador;
    double tempoInsercao;
    double tempoSorteado;
    bool equilibrada;
    tamTela tamanhoTela;
    enum {normal, parado} estado;
} estado;

#endif