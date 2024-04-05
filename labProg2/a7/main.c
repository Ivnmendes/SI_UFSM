#include "fila.h"
#include <stdio.h>
#include <assert.h>

void ins_fila(Fila f, int v[])
{
    for (int i = 0; v[i] > 0; i++) {
        fila_insere(f, v[i]);
    }
}

bool filas_iguais(Fila a, Fila b)
{
    while (!fila_vazia(a) && !fila_vazia(b)) {
        if (fila_remove(a) != fila_remove(b)) return false;
    }
    if (fila_vazia(a) != fila_vazia(b)) return false;
    return true;
}

int main()
{
    Fila a = fila_cria(10);
    Fila b = fila_cria(10);
    int v[] = { 1, 2, 8, 6, 0 };
    ins_fila(a, v);
    ins_fila(b, v);
    ins_fila(a, v);
    ins_fila(b, v);
    assert(fila_remove(a) == 1);
    assert(fila_remove(b) == 1);
    for (int i = 1; i < 10; i++) {
        fila_insere(a, fila_remove(b));
        fila_insere(b, fila_remove(a));
    }
    assert(!fila_vazia(a));
    assert(filas_iguais(a, b));
    assert(fila_vazia(a));
    assert(fila_vazia(b));
    fila_destroi(a);
    fila_destroi(b);
}