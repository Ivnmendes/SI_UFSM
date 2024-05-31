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
    bool equilibrada;
    tamTela tamanhoTela;
} estado;

#endif