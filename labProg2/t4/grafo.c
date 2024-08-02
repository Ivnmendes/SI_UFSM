#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"
#include "grafo.h"

typedef struct aresta _aresta;
typedef struct vertice _vertice;
struct aresta {
    _vertice *orig;             //Vertice de origem  
    _vertice *dest;             //Vertice de destino
    void *peso;                 //Peso da aresta
    _aresta *prox;              //Proxima aresta da lista  
};

struct vertice {
    void *dado;                 //Peso do vertice
    bool marcado;
    int identificador;
    _aresta *aresta;            //Lista de arestas ligadas ao vertice
    _vertice *prox;             //Proximo vertice da lista
};

struct _grafo {
    int nVertices;              //Numero de vertices
    int nArestas;               //Numero de arestas
    int tamDadoVertice;         //Tamanho do dado do peso do vertice
    int tamDadoAresta;          //Tamanho do dado do peso da aresta
    Fila percurso;              //Fila usada pelas funcoes de percurso
    Fila vizinhoPercurso;       //Fila usada para salvar o vizinho nas funcoes de percurso
    _vertice *v;                //Lista de vertices
};

Grafo grafo_cria(int tam_no, int tam_aresta) {
    Grafo self = (Grafo) malloc(sizeof(struct _grafo));
    if(self == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        exit(-1);
    }

    self->nVertices = 0;
    self->nArestas = 0;
    self->tamDadoVertice = tam_no;
    self->tamDadoAresta = tam_aresta;
    self->vizinhoPercurso = fila_cria(4);
    self->percurso = fila_cria(sizeof(_aresta));
    self->v = NULL;

    return self;
}

void grafo_destroi(Grafo self) {
    _vertice *aux = self->v;
    while(aux != NULL) { 
        _aresta *auxA = aux->aresta;
        while(auxA != NULL) {
            _aresta *auxA2 = auxA;
            auxA = auxA->prox;
            if(auxA2 != NULL) {
                free(auxA2->peso);
                free(auxA2);
            }
        }

        _vertice *aux2 = aux;
        aux = aux->prox;
        if(aux2 != NULL) {
            free(aux2->dado);
            free(aux2);
        }
    }

    fila_destroi(self->percurso);
    fila_destroi(self->vizinhoPercurso);
    free(self);
}

// Vertices

static _vertice* obtem_vertice_pos(Grafo self, int pos) {
    _vertice *v = self->v;      //Vertice inicial

    while(v != NULL && v->identificador != pos) { 
        v = v->prox;
    }

    return v;
}

static _vertice* cria_vertice(void *pdado, int pos, int tamDado) {
    _vertice *aux = (_vertice*) malloc(sizeof(_vertice));
    if(aux == NULL) {
        printf("Erro: Falta de memória!\n");
        exit(-1);
    }

    aux->identificador = pos;
    aux->marcado = false;
    aux->aresta = NULL;
    aux->prox = NULL;

    //Aloca memoria suficiente para armazenar o dado e move ele para aux->dado;
    aux->dado = malloc(tamDado);
    if(aux->dado == NULL) {
        printf("Erro: Falta de memória!\n");
        exit(-1);
    }
    memmove(aux->dado, pdado, (size_t) tamDado);

    return aux;
}

int grafo_insere_no(Grafo self, void *pdado) {
    int contPos = 0;
    _vertice *v = self->v;      //Vertice inicial
    _vertice *aux = NULL;

    while(v != NULL) { 
        aux = v;
        v = v->prox;
        contPos++;    
    }

    v = cria_vertice(pdado, contPos, self->tamDadoVertice);


    //Atualiza o numero de vertices do grafo e insere o novo vertice na lista de vertices
    self->nVertices++;

    if (aux == NULL) {
        //A lista de vertices estava vazia, então o novo vertice é o primeiro
        self->v = v;
    } else {
        //Insere o novo vertice no final da lista
        aux->prox = v;
    }

    return contPos;
}

void grafo_remove_no(Grafo self, int no) {
    if(no >= self->nVertices) {
        printf("Erro: No nao existe!");
    } else {
        int contPos = 0;
        _vertice *v = self->v;      //Vertice inicial
        _vertice *aux = NULL;

        while(v != NULL && v->identificador != no) { 
            aux = v;
            v = v->prox;
            contPos++;    
        }

        //Remove as arestas que partem do vertice
        _aresta *a = v->aresta;
        _aresta *auxAresta = NULL;
        while(v->aresta != NULL) {
            auxAresta = a;
            a = a->prox;
            free(auxAresta->peso);
            free(auxAresta);
            self->nArestas--;
        }

        //Remove as arestas que terminam no vertice
        for(int i = 0; i < self->nVertices; i++) {
            _vertice *verticeAux = obtem_vertice_pos(self, i);

            a = verticeAux->aresta;
            auxAresta = NULL;
            while(a != NULL) {
                if (v == a->dest) { //O vertice destino da aresta é igual ao vertice a ser removido
                    if(auxAresta == NULL) { //Se a é a primeira aresta
                        verticeAux->aresta = a->prox;
                        free(a->peso); 
                        free(a);
                    } else {
                        auxAresta->prox = a->prox;
                        free(a->peso);
                        free(a);
                    }

                    self->nArestas--;
                }

                auxAresta = a;
                a = a->prox;
            }

            verticeAux = verticeAux->prox;
        }

        //Libera o vertice e o dado
        if(aux == NULL) {   //Se é o primeiro vertice do grafo
            self->v = v->prox;
            free(v->dado);
            free(v);
            v = self->v;
        } else {
            aux->prox = v->prox;
            free(v->dado);
            free(v);
            v = aux->prox;
        }

        self->nVertices--;
        //Atualiza o indice de todos os vertices seguintes da lista
        for(int i = contPos; i < self->nVertices; i++) {
            v->identificador = contPos;
            v = v->prox;
        }
    }
}

void grafo_altera_valor_no(Grafo self, int no, void *pdado) {
    if(no >= self->nVertices) {
        printf("Erro: No nao existe!");
    } else {
        _vertice *v = self->v;      //Vertice inicial

        while(v != NULL && v->identificador != no) { 
            v = v->prox;
        }

        //Copia o dado para o vertice "no"
        if(pdado != NULL) {
            memmove(v->dado, pdado, self->tamDadoVertice);
        }
    }
}

void grafo_valor_no(Grafo self, int no, void *pdado) {
    if(no >= self->nVertices) {
        printf("Erro: No nao existe!");
    } else {
        _vertice *v = self->v;      //Vertice inicial

        while(v != NULL && v->identificador != no) { 
            v = v->prox;
        }

        //Copia o dado do vertice "no" para pdado
        if(v != NULL) {
            memmove(pdado, v->dado, self->tamDadoVertice);
        }
    }
}

int grafo_nnos(Grafo self) { return self->nVertices; }

// Arestas

static _aresta* cria_aresta(void *pdado, _vertice *origem, _vertice *destino, int tamDoDado) {
    _aresta *aux = (_aresta*) malloc(sizeof(_aresta));
    if(aux == NULL) {
        printf("Erro: Falta de memória!\n");
        exit(-1);
    }

    aux->orig = origem;
    aux->dest = destino;
    aux->prox = NULL;

    aux->peso = malloc(tamDoDado);
    if(aux->peso == NULL) {
        printf("Erro: Falta de memória!\n");
        exit(-1);
    }
    memmove(aux->peso, pdado, (size_t) tamDoDado);

    return aux;
}

void grafo_altera_valor_aresta(Grafo self, int origem, int destino, void *pdado) {
    if(origem > self->nVertices || destino > self->nVertices) {
        printf("Erro: Um ou mais nos fornecidos nao existem!");
    } else {
        _vertice *verticeOrigem = obtem_vertice_pos(self, origem);
        _vertice *verticeDestino = obtem_vertice_pos(self, destino);


        //Verifica se a aresta existe
        bool arestaExiste;
        _aresta *a = verticeOrigem->aresta;
        _aresta *aux = NULL;
        while(a != NULL && a->dest->identificador != destino) { 
            aux = a;
            a = a->prox;
        }
        arestaExiste = (a == NULL) ? false : true;

        if(arestaExiste) {
            if(pdado != NULL) {
                memmove(a->peso, pdado, self->tamDadoAresta);
            } else { //Remocao da aresta
                if(aux == NULL) { //Se a é a primeira aresta
                    verticeOrigem->aresta = a->prox;
                    free(a->peso); 
                    free(a);
                } else {
                    aux->prox = a->prox;
                    free(a->peso);
                    free(a);
                }

                self->nArestas--;
            }
        } else {
            if(aux == NULL) {       //Se nao tem nenhuma aresta
                verticeOrigem->aresta = cria_aresta(pdado, verticeOrigem, verticeDestino, self->tamDadoAresta);
                self->nArestas++;
            } else {
                aux->prox = cria_aresta(pdado, verticeOrigem, verticeDestino, self->tamDadoAresta);
                self->nArestas++;
            }
        }

        // TODO: remocao de aresta
    }
}

bool grafo_valor_aresta(Grafo self, int origem, int destino, void *pdado) {
    if(origem > self->nVertices || destino > self->nVertices) {
        printf("Erro: Um ou mais nos fornecidos nao existem!");
    } else {
        _vertice *verticeOrigem = obtem_vertice_pos(self, origem);

        //Verifica se a aresta existe
        bool arestaExiste;
        _aresta *a = verticeOrigem->aresta;
        while(a != NULL && a->dest->identificador != destino) { 
            a = a->prox;
        }
        arestaExiste = (a == NULL) ? false : true;

        if(arestaExiste) {
            memmove(pdado, a->peso, self->tamDadoAresta);
            return true;
        }
    }

    return false;
}

void grafo_arestas_que_partem(Grafo self, int origem) {
    //Se existem elementos na fila esvazia ela
    while(!fila_vazia(self->percurso)) {
        fila_remove(self->percurso, NULL);
        fila_remove(self->vizinhoPercurso, NULL);
    }

    _vertice *verticeOrigem = obtem_vertice_pos(self, origem);
    _aresta *a = verticeOrigem->aresta;
    //Enfileira todas as arestas comecadas em origem
    while(a != NULL) {
        fila_insere(self->percurso, a);
        int x = a->dest->identificador;
        fila_insere(self->vizinhoPercurso, &x);
        a = a->prox;
    }
}

void grafo_arestas_que_chegam(Grafo self, int destino) {
    //Se existem elementos na fila esvazia ela
    while(!fila_vazia(self->percurso)) {       
        fila_remove(self->percurso, NULL);
        fila_remove(self->vizinhoPercurso, NULL);
    }

    _vertice *verticeDestino = obtem_vertice_pos(self, destino);

    _vertice *verticeAux = self->v;
    for(int i = 0; i < self->nVertices; i++) {

        _aresta *a = verticeAux->aresta;
        while(a != NULL) {
            if (verticeDestino == a->dest) { //O vertice destino da aresta é igual ao vertice fornecido
                fila_insere(self->percurso, a); //Enfileira a aresta
                int x = a->orig->identificador;
                fila_insere(self->vizinhoPercurso, &x);
            }

            a = a->prox;
        }

        verticeAux = verticeAux->prox;
    }
}

bool grafo_proxima_aresta(Grafo self, int *vizinho, void *pdado) {
    if(fila_vazia(self->percurso)) {
        return false;
    }

    _aresta *aux = (_aresta*) malloc(sizeof(_aresta));
    if(aux == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        exit(-1);
    }

    fila_remove(self->percurso, aux);
    if (aux == NULL) {
        return false;
    }

    memmove(pdado, aux->peso, self->tamDadoAresta);
    
    int x;
    fila_remove(self->vizinhoPercurso, &x);
    *vizinho = x;

    return true;
}

// Algoritmos

typedef enum { nao_visitado, em_visita, ja_visitado } marca_t;

static bool acha_ciclo(_vertice *v, int nVertices, marca_t marca[nVertices]) {
    if (marca[v->identificador] == em_visita) return true;
    if (marca[v->identificador] == ja_visitado) return false;
    
    marca[v->identificador] = em_visita;

    _aresta *aresta = v->aresta;
    while (aresta != NULL) {
        if (acha_ciclo(aresta->dest, nVertices, marca)) return true;
        aresta = aresta->prox;
    }
    
    marca[v->identificador] = ja_visitado;
    return false;
} 

bool grafo_tem_ciclo(Grafo self) {
    marca_t marca[self->nVertices];

    for (int i = 0; i < self->nVertices; i++) {
        marca[i] = nao_visitado;  // todos marcados como não visitados
    }

    _vertice *v = self->v;
    while (v != NULL) {
        if (marca[v->identificador] == nao_visitado) {
            if (acha_ciclo(v, self->nVertices, marca)) {
                return true;
            }
        }
        v = v->prox;
    }

    return false;
}

Fila grafo_ordem_topologica(Grafo self) {

}

void imprimeNo(Grafo self) {
    _vertice *v = self->v;
    int cont = 0;
    while(v != NULL) {
        printf("i: %d - id: %d - dado: %d\n", cont, v->identificador, *(int*) v->dado);
        cont++;
        v = v->prox;
    }
}

void imprimeArestas(Grafo self) {
    _vertice *v = self->v;
    while(v != NULL) {
        _aresta *a = v->aresta;
        while(a != NULL) {
            printf("Aresta %d-%d peso: %d\n", a->orig->identificador, a->dest->identificador, *(int*) a->peso);
            a = a->prox;
        }

        v = v->prox;
    }
}