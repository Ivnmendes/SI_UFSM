#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arvore.h"
#include "telag.h"

typedef struct _no no_t;
struct _no {
    char* val;
    no_t* esq;
    no_t* dir;
   float posicaoX;
};


arv_t* cria_arv_vazia() { // Cria uma árvore vazia
    return NULL;
}

static arv_t* cria_no(char* dado) { // Cria um nó, alocando a memória necessária para ele e para a string que vai conter, além de inicializar seus filhos como vazios
    no_t* no = malloc(sizeof(no_t));
    assert(no != NULL);


    no->val = malloc(strlen(dado) * 1 + 1);
    assert(no->val != NULL);
    strcpy(no->val, dado);

    no->posicaoX = 0;

    no->esq = cria_arv_vazia();
    no->dir = cria_arv_vazia();

    return no;
}

bool estaVazia(arv_t* self) { return self == NULL;}

bool eFolha(arv_t *self) { return estaVazia(self->esq) && estaVazia(self->dir);}

static int maiorNum(int x, int y) {
    if (x>y) {
        return x;
    }

    return y;
}

int altura(arv_t* self) {
    if(estaVazia(self)) {
        return -1;
    }

    return 1 + maiorNum(altura(self->esq), altura(self->dir));
}

static int calculaFatorEquilibrioNo(arv_t* self) {
    return altura(self->esq) - altura(self->dir);
}

bool estaEquilibrado(arv_t* self) {
    if(estaVazia(self)) {
        return true;
    }
    if(abs(calculaFatorEquilibrioNo(self)) > 2) {
        return false;
    }

    return estaEquilibrado(self->esq) && estaEquilibrado(self->dir);
}


arv_t* insereElem(arv_t* self, char* dado) {
    if (estaVazia(self)) { // Se a arvore esta vazia, cria o no na posicao inicial
        return cria_no(dado);           
    } else if(strcmp(dado, self->val) == 0) { //Verifica se o dado ja existe, se sim nao faz nada
        ;
    } else if (strcmp(dado, self->val) < 0) { // Se a string é "menor" que a do nó percorre pela esquerda
        self->esq = insereElem(self->esq, dado);
    } else {
        self->dir = insereElem(self->dir, dado);
    }

    return self; // retorna a árvore atualizada
}

static char* maiorValor(arv_t* self) {
    if(estaVazia(self)) {
        return NULL;
    }
    if(estaVazia(self->dir)) {
        return self->val;
    }

    return maiorValor(self->dir);
}

bool removeElem(arv_t** self, char* dado) {
    bool removido = false;
    arv_t* atual = *self;
    if(estaVazia(atual)) { // Se a arvore esta vazia nao e possivel remover
        return removido;
    } else if (strcmp(dado, atual->val) == 0) {
        if(eFolha(atual)) { // esta na folha, remocao facil, sem necessidade de reorganizar a arvore
            free(atual->val);
            free(atual);
            *self = NULL;
        } else { // nao esta na folha
            char* novoValor;
            arv_t** noParaRemover;
            if(!estaVazia(atual->esq)) { // Busca o maior valor na subarvore esquerda, se ela nao estiver vazia
                novoValor = maiorValor(atual->esq);
                noParaRemover = &atual->esq; // Salva o nó que vai ser movido para removelo depois
            } else {
                novoValor = maiorValor(atual->dir);
                noParaRemover = &atual->dir;
            }
            atual->val = malloc(strlen(novoValor) *  + 1);
            strcpy(atual->val, novoValor);
            removeElem(noParaRemover, novoValor);
        }

        removido = true;
    } else if (strcmp(dado, atual->val) < 0) { // dado menor que o valor do nó, procura na esquerda
        removido = removeElem(&atual->esq, dado);
    } else {
        removido = removeElem(&atual->dir, dado);
    }

    return removido;
}

void destroiArvore(arv_t* self) {
    if (estaVazia(self)) {
        return;
    }

    destroiArvore(self->esq);
    destroiArvore(self->dir);
    
    free(self->val);
    free(self);
}

static void imprimeNo(arv_t* self, float alt, float larg, int tFonte) {
    tela_texto(larg, alt, tFonte, preto, self->val);
    float px1, px2, py1, py2;
    tela_retangulo_texto(larg, alt, tFonte, self->val, &px1, &py1, &px2, &py2);
    tela_retangulo(px1 - 5, alt - 10, px2 + 5, alt + 10, 2, preto, transparente);
}

static float calculaDeslocamento(arv_t* self, float alt, float larg) {
    if (estaVazia(self)) {
        return 0;
    }

    float px1, px2, py1, py2;
    tela_retangulo_texto(larg, alt, 15, self->val, &px1, &py1, &px2, &py2);
    int espacoOcupado = (px1 - px2) / 2; // px1 - px2 é o espaco ocupado pelo texto, dividindo por dois obtemos o centro
    // retorna o espaco ocupado pelo no pai + espaco ocupado pela subarvore esquerda + espaco ocupado pela subarvore direita
    return espacoOcupado + calculaDeslocamento(self->esq, alt, larg) + calculaDeslocamento(self->dir, alt, larg);
}

void imprimeArvore(arv_t* self, float altAtual, float largAtual) {
    if (estaVazia(self)) {
        return;
    }

    float px1, px2, py1, py2;
    tela_retangulo_texto(largAtual, altAtual, 15, self->val, &px1, &py1, &px2, &py2);

    float valorEsq = calculaDeslocamento(self->esq, altAtual, largAtual);   // Espaco ocupado pela subarvore esquerda
    float valorDir = calculaDeslocamento(self->dir, altAtual, largAtual);   // Espaco ocupado pela subarvore direita
    
    imprimeNo(self, altAtual, largAtual, 15);

    float largEsq = largAtual + valorEsq + valorDir;
    
    altAtual += 60;
    if(!estaVazia(self->esq)) {
        imprimeArvore(self->esq, altAtual, largAtual - abs(largAtual - largEsq - 10));
        tela_linha(largAtual, altAtual - 50, largAtual - abs(largAtual - largEsq - 10), altAtual - 10, 2, preto);
    }
    
    if(!estaVazia(self->dir)) {
        imprimeArvore(self->dir, altAtual, largAtual + abs(largAtual - largEsq - 10));   
        tela_linha(largAtual, altAtual - 50, largAtual + abs(largAtual - largEsq - 10), altAtual - 10, 2, preto);
    }
}