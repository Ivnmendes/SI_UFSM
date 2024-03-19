// l224a - trabalho 1 - revisão
//
// Aluno: ivan
//
// Você deve alterar este arquivo colocando seu nome na linha acima, e nas
// linhas delimitadas por comentários indicativos. O restante do arquivo não
// deve ser alterado para implementar a parte I do trabalho. Pode adicionar
// includes também.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// tipo de dados que representa um triângulo
typedef struct {
  float lado1;
  float lado2;
  float lado3;
  int tipo;
} triangulo;

// número máximo de triângulos suportado pelo programa

// tipo de dados que representa um vetor de triângulos
typedef struct {
  int max_triangulos;
  int n_triangulos;      // número de triângulos no vetor
  triangulo *triangulos; // vetor com os triângulos
} vetor_de_triangulos;

// Você deve implementar as funções faltantes e outras que achar necessário
// abaixo desta linha
bool le_triangulo(triangulo *t, FILE *arq);
vetor_de_triangulos *aloca_vetor_de_triangulos(int n_triangulos);

bool le_triangulos(vetor_de_triangulos *t, FILE *arq) {
    while (!feof(arq) && t->n_triangulos < t->max_triangulos) {
        if (!le_triangulo(&t->triangulos[t->n_triangulos], arq)) {
            return false;
        }
        t->n_triangulos++;
    }

    if ((feof(arq) && t->n_triangulos != t->max_triangulos) || (!feof(arq))) {
        printf("Numero de triangulos contidos no arquivo e diferente do registrado!\n");
        return false;
    }

    return true;
}

void classifica_triangulos(triangulo *t) {
    if (t->lado1 <= 0 || t->lado2 <= 0 || t->lado3 <= 0 || (t->lado1 >= t->lado2 + t->lado3 || t->lado2 >= t->lado1 + t->lado3 || t->lado3 >= t->lado1 + t->lado2)) {
        t->tipo = 0;
    } else if (t->lado1 == t->lado2 && t->lado1 == t->lado3) {
      t->tipo = 1;
    } else if (t->lado1 != t->lado2 && t->lado1 != t->lado3 && t->lado2 != t->lado3) {
      t->tipo = 2;
    } else {
      t->tipo = 3;
    }
}

void conta_triangulos(vetor_de_triangulos *t, int contagem[]) {
    for (int i = 0; i < t->n_triangulos; i++) {
        contagem[t->triangulos[i].tipo]++;
    }
}

vetor_de_triangulos *aloca_vetor_de_triangulos(int n_triangulos) {
    vetor_de_triangulos *vet;

    vet = (vetor_de_triangulos *) malloc(sizeof(vetor_de_triangulos));
    if (vet == NULL) {
        printf("Memoria insuficiente!\n");
        return NULL;
    }

    vet->triangulos = (triangulo *) malloc(n_triangulos * sizeof(triangulo));
    if (vet->triangulos == NULL) {
        printf("Memoria insuficiente!\n");
        return NULL;
    }

    vet->n_triangulos = 0;

    return vet;
}

// essa função deve existir e ser usada para a leitura de um triângulo.
// lê os valores dos 3 lados de um triângulo,
//   inicializa o triângulo apontado por t com esses valores.
// retorna true se bem sucedido ou false em caso de problema (que pode acontecer
// na
//   parte II)
bool le_triangulo(triangulo *t, FILE *arq) {
    if (fscanf(arq, "%f %f %f\n", &t->lado1, &t->lado2, &t->lado3) == 3) {
        return true;
    } else {
        printf("Erro na leitura do arquivo. Caracter invalido!\n");
        return false;
    }
}

// Você não deve alterar abaixo desta linha para a parte I do trabalho

int main() {
    FILE *arq;
    arq = fopen("./arquivo/triangulos.txt", "r");
    if (arq != NULL) {
        vetor_de_triangulos *vetor;
        int contadores[4] = {0};
        int max_triangulos;

        fscanf(arq, "%d\n", &max_triangulos);
        vetor = aloca_vetor_de_triangulos(max_triangulos);
        if (vetor == NULL || vetor->triangulos == NULL) {
            return -1;
        }
        vetor->max_triangulos = max_triangulos;

        if (le_triangulos(vetor, arq)) {
            for (int i = 0; i < vetor->n_triangulos; i++) {
                classifica_triangulos(&(vetor->triangulos[i]));
            }
            conta_triangulos(vetor, contadores);

            printf("Classificação dos triângulos:\n");
            printf("  %d equiláteros\n", contadores[1]);
            printf("  %d isósceles\n", contadores[3]);
            printf("  %d escalenos\n", contadores[2]);
            printf("  %d não triângulos\n", contadores[0]);

            return 1;
        } else {
            printf("Encerrando Programa...\n");
        }
        fclose(arq);
        free(vetor->triangulos);
        free(vetor);
    } else {
        printf("Erro ao abrir arquivo!\n");
    }

    return 0;
}
