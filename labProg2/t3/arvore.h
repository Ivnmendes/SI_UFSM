#include <stdbool.h>

typedef struct _no arv_t;

arv_t* cria_arv_vazia(); //Cria uma árvore que aponta para NULL

int tamanhoDoNo(arv_t* self); //Retorna o tamanho do no

bool estaVazia(arv_t* self); //Verifica se a árvore está vazia

bool eFolha(arv_t* self); //Verifica se o nó é uma folha

int altura(arv_t* self); //Checa a altura da árvore

bool estaEquilibrado(arv_t* self); //Verifica se a árvore está equilibrada

arv_t* insereElem(arv_t* self, char* dado); //Insere um elemento na árvore

void destroiArvore(arv_t* self); //Libera a memoria alocada para cada no

bool removeElem(arv_t** self, char* dado); //Remove um elemento, retorna false caso nao encontre nenhum e true caso seja removido

float imprimeArvore(arv_t* self, float altAtual, float largAtual);//Desenha a árvore na teça, retorna a largura do nó pai impresso (desnecessário no resto do programa, usado na recursão)