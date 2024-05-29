#include <stdbool.h>

typedef struct _no arv_t;

arv_t* cria_arv_vazia();

bool estaVazia(arv_t* self);

bool eFolha(arv_t* self);

int altura(arv_t* self);

bool estaEquilibrado(arv_t* self);

arv_t* insereElem(arv_t* self, char* dado);

bool removeElem(arv_t** self, char* dado);

void imprimeArvore(arv_t* self, int espaco, int alturaArvore);

void printInOrder(arv_t* node);