#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arvore.h"

bool leArquivoSilabas(char *silabas[185]) {
    FILE* arquivoSilabas;
    arquivoSilabas = fopen("./silabas/silabas.txt", "r");
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

char *sorteiaSilaba(char *silabas[185]) {
    return silabas[rand() % 185];
}

void sorteiaPalavra(char **palavra, char* silabas[185]) {
    int numSilabas = rand() % 2 + 1;

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
    for(int i = 0, i < 185, i++) {
        free(silabas[i]);
    }
}

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

int main() {
    return 0;
}