#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "grafo.h"
#include "fila.h"

bool teste1() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    grafo_insere_no(self, &x);
    x = 10;
    grafo_insere_no(self, &x);
    x = 15;
    grafo_insere_no(self, &x);
    x = 20;
    grafo_insere_no(self, &x);
    x = 25;
    grafo_insere_no(self, &x);
    if(grafo_nnos(self) != 5) {
        return false;
    }
    x = 30;
    grafo_insere_no(self, &x);
    if(grafo_nnos(self) != 6) {
        grafo_destroi(self);
        return false;
    }
    grafo_remove_no(self, 5);
    if(grafo_nnos(self) != 5) {
        grafo_destroi(self);
        return false;
    }

    x = 100;
    grafo_altera_valor_no(self, 3, &x);
    int y;
    grafo_valor_no(self, 3, &y);
    if(y != 100) {
        grafo_destroi(self);
        return false;
    }

    grafo_destroi(self);
    return (self != NULL) ? true : false;    
}

bool teste2() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    grafo_insere_no(self, &x);
    x = 10;
    grafo_insere_no(self, &x);
    x = 15;
    grafo_insere_no(self, &x);
    x = 20;
    grafo_insere_no(self, &x);
    x = 25;
    grafo_insere_no(self, &x);

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

    int z;
    if(!grafo_valor_aresta(self, 1, 2, &z) || z != -1) {
        grafo_destroi(self);
        return false;
    }
    grafo_altera_valor_aresta(self, 1, 2, NULL);
    if(grafo_valor_aresta(self, 1, 2, &z)) {
        grafo_destroi(self);
        return false;
    }


    if(!grafo_valor_aresta(self, 2, 4, &z) || z != 15) {
        grafo_destroi(self);
        return false;
    }
    
    grafo_destroi(self);
    return (self != NULL) ? true : false;    
}

bool teste3() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    grafo_insere_no(self, &x);
    x = 10;
    grafo_insere_no(self, &x);
    x = 15;
    grafo_insere_no(self, &x);
    x = 20;
    grafo_insere_no(self, &x);
    x = 25;
    grafo_insere_no(self, &x);

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

    grafo_arestas_que_partem(self, 0);
    int z;
    int k;
    int i = 0;
    while(grafo_proxima_aresta(self, &z, &k)) {
        if(i == 0) {
            if(z != 1 || k != 3) {
                grafo_destroi(self);
                return false;
            }
        } else {
            if(z != 3 || k != 9) {
                grafo_destroi(self);
                return false;
            }
        }

        i++;
    }

    grafo_arestas_que_chegam(self, 3);
    i = 0;
    while(grafo_proxima_aresta(self, &z, &k)) {
        if(i == 0) {
            if(z != 0 || k != 9) {
                grafo_destroi(self);
                return false;
            }
        } else {
            if(z != 1 || k != 6) {
                grafo_destroi(self);
                return false;
            }
        }

        i++;
    }

    grafo_destroi(self);
    return (self != NULL) ? true : false;    
}

bool teste4() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    grafo_insere_no(self, &x);
    x = 10;
    grafo_insere_no(self, &x);
    x = 15;
    grafo_insere_no(self, &x);
    x = 20;
    grafo_insere_no(self, &x);
    x = 25;
    grafo_insere_no(self, &x);

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
    y = 20;
    grafo_altera_valor_aresta(self, 4, 2, &y);
    
    if(!grafo_tem_ciclo(self)) {
        grafo_destroi(self);
        return false;
    }

    grafo_altera_valor_aresta(self, 4, 2, NULL);

    if(grafo_tem_ciclo(self)) {
        grafo_destroi(self);
        return false;
    }

    y = 20;
    grafo_altera_valor_aresta(self, 2, 3, &y);

    if(!grafo_tem_ciclo(self)) {
        grafo_destroi(self);
        return false;
    }
    
    grafo_destroi(self);
    return (self != NULL) ? true : false;    
}

bool teste5() {
    Grafo self = grafo_cria(sizeof(int), sizeof(int));
    int x = 5;
    grafo_insere_no(self, &x);
    x = 10;
    grafo_insere_no(self, &x);
    x = 15;
    grafo_insere_no(self, &x);
    x = 20;
    grafo_insere_no(self, &x);
    x = 25;
    grafo_insere_no(self, &x);

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

    Fila ordem = grafo_ordem_topologica(self);

    if(ordem == NULL) {
        grafo_destroi(self);
        return false;
    }

    fila_remove(ordem, &x);
    if(x != 0) {
        grafo_destroi(self);
        return false;
    }

    fila_remove(ordem, &x);
    if(x != 1) {
        grafo_destroi(self);
        return false;
    }

    fila_remove(ordem, &x);
    if(x != 3) {
        grafo_destroi(self);
        return false;
    }
    
    fila_remove(ordem, &x);
    if(x != 2) {
        grafo_destroi(self);
        return false;
    }

    fila_remove(ordem, &x);
    if(x != 4) {
        grafo_destroi(self);
        return false;
    }

    fila_destroi(ordem);

    y = 18;
    grafo_altera_valor_aresta(self, 4, 2, &y);

    ordem = grafo_ordem_topologica(self);

    if(ordem != NULL) {
        grafo_destroi(self);
        return false;
    }    

    grafo_destroi(self);
    return (self != NULL) ? true : false;   
}

int main() {
    assert(teste1());
    assert(teste2());
    assert(teste3());
    assert(teste4());
    assert(teste5());
    printf("Passou em todos os testes!\n");
    return 0;
}