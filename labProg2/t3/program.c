#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "arvore.h"

int main() {
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
    return 0;
}