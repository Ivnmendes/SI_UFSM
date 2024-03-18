// l224a - trabalho 1 - revisão
//
// Aluno: ivan
//
// Você deve alterar este arquivo colocando seu nome na linha acima, e nas linhas 
// delimitadas por comentários indicativos. O restante do arquivo não deve ser
// alterado para implementar a parte I do trabalho.
// Pode adicionar includes também.

#include <stdio.h>
#include <stdbool.h>
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
    int n_triangulos;                     // número de triângulos no vetor
    triangulo *triangulos;                // vetor com os triângulos
} vetor_de_triangulos;

// Você deve implementar as funções faltantes e outras que achar necessário
// abaixo desta linha
bool le_triangulo(triangulo *t, FILE *arq);
vetor_de_triangulos *aloca_vetor_de_triangulos(int n_triangulos);

bool le_triangulos(vetor_de_triangulos *t, int n_t, FILE *arq)
{
    fscanf(arq, "%d\n", &t->n_triangulos);

    if (n_t != t->n_triangulos) {
        printf("Numero de triangulos inseridos diferente do registrado no arquivo!\n");
        return false;
    }

    *t = *aloca_vetor_de_triangulos(n_t);
    if (t == NULL) {
        return false;
    }
    
    for(int i = 0; i < t->max_triangulos; i++) {
        t->n_triangulos++;
        le_triangulo(&t->triangulos[i], arq);
        if (feof(arq)) {
            printf("Numero de triangulos contidos no arquivo e diferente do registrado/inserido!\n");
            return false;
        }
    }

    return true;
}

void classifica_triangulos(vetor_de_triangulos *t) 
{
    for (int i = 0; i < t->n_triangulos; i++) {
        if (t->triangulos[i].lado1 <= 0 || t->triangulos[i].lado2 <= 0 || t->triangulos[i].lado3 <= 0 || (t->triangulos[i].lado1 > t->triangulos[i].lado2 + t->triangulos[i].lado3 || t->triangulos[i].lado2 > t->triangulos[i].lado1 + t->triangulos[i].lado3 || t->triangulos[i].lado3 > t->triangulos[i].lado1 + t->triangulos[i].lado2)) {
            t->triangulos[i].tipo = 0;
        }
        else if(t->triangulos[i].lado1 == t->triangulos[i].lado2 && t->triangulos[i].lado1 == t->triangulos[i].lado3) {
            t->triangulos[i].tipo = 1;
        } 
        else if (t->triangulos[i].lado1 != t->triangulos[i].lado2 && t->triangulos[i].lado1 != t->triangulos[i].lado3 && t->triangulos[i].lado2 != t->triangulos[i].lado3) {
            t->triangulos[i].tipo = 2;
        }
        else {
            t->triangulos[i].tipo = 3;
        }
    }
}

void conta_triangulos(vetor_de_triangulos *t, int contagem[]) 
{
    for (int i = 0; i < t->n_triangulos; i++) {
        switch (t->triangulos[i].tipo) {
            case 0:
                contagem[0]++;
                break;
            case 1:
                contagem[1]++;
                break;
            case 2:
                contagem[3]++;
                break;
            case 3:
                contagem[2]++;
                break;
        }
    }
}

vetor_de_triangulos *aloca_vetor_de_triangulos(int n_triangulos) 
{
    vetor_de_triangulos *vet;

    vet = (vetor_de_triangulos *) malloc(sizeof(vetor_de_triangulos));
    vet->triangulos = (triangulo *) malloc(n_triangulos * sizeof(triangulo));

    vet->n_triangulos = 0;
    vet->max_triangulos = n_triangulos;
    
    if (vet == NULL) {
        printf("Memoria insuficiente!");
        return NULL;
    } else {
        return vet;
    }
}

// essa função deve existir e ser usada para a leitura de um triângulo.
// lê os valores dos 3 lados de um triângulo,
//   inicializa o triângulo apontado por t com esses valores.
// retorna true se bem sucedido ou false em caso de problema (que pode acontecer na
//   parte II)
bool le_triangulo(triangulo *t, FILE *arq)
{
    fscanf(arq, "%f %f %f", &t->lado1, &t->lado2, &t->lado3);
    return true;
}

// Você não deve alterar abaixo desta linha para a parte I do trabalho

int main()
{
    FILE *arq;
    arq = fopen("./arquivo/triangulos.txt", "r");
    if (arq != NULL) {
        vetor_de_triangulos vetor;
        int n_t;
        int contadores[4] = { 0 };

        printf("Número de triângulos: ");
        scanf("%d", &n_t);

        if (le_triangulos(&vetor, n_t, arq)) { 
            classifica_triangulos(&vetor);
            conta_triangulos(&vetor, contadores);

            printf("Classificação dos triângulos:\n");
            printf("  %d equiláteros\n", contadores[1]);
            printf("  %d isósceles\n", contadores[2]);
            printf("  %d escalenos\n", contadores[3]);
            printf("  %d não triângulos\n", contadores[0]);
            
            return 1;
        } else {
            printf("Encerrando Programa...\n");
        }
        fclose(arq);
    } else {
        printf("Erro ao abrir arquivo!\n");
    }

    return 0;
}