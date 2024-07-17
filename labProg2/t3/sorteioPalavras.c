#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

bool leArquivoSilabas(char *silabas[185]) {
    FILE* arquivoSilabas;
    arquivoSilabas = fopen("./arquivos/silabas/silabas.txt", "r");
    if(arquivoSilabas == NULL) {
        return false;
    }

    int cont = 0;
    char aux[5];
    while(fgets(aux, sizeof(aux), arquivoSilabas)) {
        aux[strcspn(aux, "\n")] = 0;
        silabas[cont] = malloc(strlen(aux) * 1 + 1);
        assert(silabas[cont] != NULL);
        strcpy(silabas[cont], aux);
        cont++;
    }

    fclose(arquivoSilabas);
    return true;
}

static char *sorteiaSilaba(char *silabas[185]) { //sorteia uma silaba aleatoria do vetor
    return silabas[rand() % 185];
}

void sorteiaPalavra(char **palavra, char* silabas[185]) {
    int numSilabas = rand() % 2 + 1; //N de silabas vai de 2 a 4
    char *aux = sorteiaSilaba(silabas);
    
    *palavra = malloc(strlen(aux) + 1);
    assert(*palavra != NULL);
    strcpy(*palavra, aux);

    for (int i = 0; i < numSilabas; i++) {
        aux = sorteiaSilaba(silabas);
        *palavra = realloc(*palavra, strlen(*palavra) + strlen(aux) + 1);
        assert(*palavra != NULL);
        strcat(*palavra, aux);
    }
}

void liberaSilabas(char *silabas[185]) {
    for(int i = 0; i < 185; i++) {
        free(silabas[i]);
    }
}
