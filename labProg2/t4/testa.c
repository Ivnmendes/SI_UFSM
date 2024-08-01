#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "grafo.h"
#include "fila.h"

bool teste1() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 10;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 15;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 20;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 25;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    if(grafo_nnos(self) != 5) {
        return false;
    }
    x = 30;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    if(grafo_nnos(self) != 6) {
        return false;
    }
    grafo_remove_no(self, 5);
    if(grafo_nnos(self) != 5) {
        return false;
    }

    x = 100;
    grafo_altera_valor_no(self, 3, &x);
    int y;
    grafo_valor_no(self, 3, &y);
    if(y != 100) {
        return false;
    }
    imprimeNo(self);

    grafo_destroi(self);
    return true;    
}

bool teste2() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 10;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 15;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 20;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 25;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    printf("\n\n");

    int y = 3;
    grafo_altera_valor_aresta(self, 0, 1, &y);
    y = 6;
    grafo_altera_valor_aresta(self, 1, 3, &y);
    y = 9;
    grafo_altera_valor_aresta(self, 0, 3, &y);
    y = 12;
    grafo_altera_valor_aresta(self, 3, 2, &y);
    y = 15;
    grafo_altera_valor_aresta(self, 2, 4, &y);
    y = -1;
    grafo_altera_valor_aresta(self, 1, 2, &y);
    imprimeArestas(self);
    printf("\n\n");
    grafo_altera_valor_aresta(self, 1, 2, NULL);
    imprimeArestas(self);

    int z;
    if(grafo_valor_aresta(self, 2, 5, &z)) {
        printf("\nvalor: %d\n", z);
    }
    
    grafo_destroi(self);
    return true;    
}

bool teste3() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 10;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 15;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 20;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    x = 25;
    printf("Inserido em %d\n", grafo_insere_no(self, &x));
    printf("\n\n");

    int y = 3;
    grafo_altera_valor_aresta(self, 0, 1, &y);
    y = 6;
    grafo_altera_valor_aresta(self, 1, 3, &y);
    y = 9;
    grafo_altera_valor_aresta(self, 0, 3, &y);
    y = 12;
    grafo_altera_valor_aresta(self, 3, 2, &y);
    y = 15;
    grafo_altera_valor_aresta(self, 2, 4, &y);
    imprimeArestas(self);
    printf("\n\n");

    grafo_arestas_que_partem(self, 0);
    int z;
    int k;
    while(grafo_proxima_aresta(self, &z, &k)) {
        printf("Chega em %d, peso %d\n", z, k);
    }

    printf("\n");

    grafo_arestas_que_chegam(self, 3);
    while(grafo_proxima_aresta(self, &z, &k)) {
        printf("Parte de %d, peso %d\n", z, k);
    }
    grafo_destroi(self);

    return true;    
}

bool teste4() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    
    grafo_destroi(self);
    return true;    
}

int main() {
    //assert(teste1());
    //assert(teste2());
    assert(teste3());
    //assert(teste4());
    return 0;
}