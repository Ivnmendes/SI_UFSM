#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "manipulaHistorico.h"

bool leHistorico(int pontosHistorico[10]) {
    FILE* arquivoHistorico;
    arquivoHistorico = fopen("./historico/historico.txt", "r");
    if (arquivoHistorico == NULL) {
        return false;
    }

    int i = 0;
    while(!feof(arquivoHistorico) && i < 10) {    
        fscanf(arquivoHistorico, "%d", &pontosHistorico[i]);
        i++;
    }

    fclose(arquivoHistorico);
    return true;
}

bool escreveHistorico(int pontosHistorico[10]) {
    FILE* arquivoHistorico;
    arquivoHistorico = fopen("./historico/historico.txt", "w+");
    if (arquivoHistorico == NULL) {
        return false;
    }

    for(int i = 0; i < 10 && pontosHistorico[i] != 0; i++) {
        fprintf(arquivoHistorico, "%d\n", pontosHistorico[i]);
    }

    fclose(arquivoHistorico);
    return true;
}

int verificaHistorico(int pontos, int pontosHistorico[10]) {
    int x = -1;

    for(int i = 0; i < 10; i++) {
        if (pontos > pontosHistorico[i]) {
            x = i;
            break;
        }
    }

    return x;
}

void atualizaHistorico(int posVetor, int pontos, int pontosHistorico[10]) {
    int auxPontos;
    for(int i = posVetor; i < 10; i++) {
        auxPontos = pontosHistorico[i];
        pontosHistorico[i] = pontos;
        pontos = auxPontos;
    }
}