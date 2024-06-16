#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool leHistorico(int* pontosHistorico[10], char nomesHistorico[10][10]) {
    File* arquivoHistorico;
    arquivoHistorico = fopen("./historico/historico.txt", r);
    if (arquivoHistorico == NULL) {
        return false;
    }

    int i = 0;
    while(!feof(arquivoHistorico) && i < 10) {
        if (fscanf(arquivoHistorico, "%d", &pontosHistorico[i]) != 1) {
            fclose(arquivoHistorico);
            return false;
        }
        char aux[5];
        fgets(aux, sizeof(aux), arquivoHistorico);
        aux[strcspn(aux, "\n")] = 0;
        strcpy(nomesHistorico[i], aux);

        i++;
    }

    fclose(arquivoHistorico);
}

bool atualizaHistorico(int pontos, char* nome, int* pontosHistorico[10], char nomesHistorico[10][10]) {
    File* arquivoHistorico;
    arquivoHistorico = fopen("./historico/historico.txt", r+);
    if (arquivoHistorico == NULL) {
        return false;
    }

    for(int i = 0; i < 10; i++) {
        if (pontos > pontosHistorico[i]) {
            int auxPontos;
            char auxNome[10];
            for(int j = i; j < 10; j++) {
                auxPontos = pontosHistorico[j];
                pontosHistorico[j] = pontos;
                pontos = auxPontos;

                strcpy(auxNome, nomesHistorico[j]);
                strcpy(nomesHistorico[j], nome);
                strcpy(nome, auxNome);
            }

            break;
        }
    }

    
}