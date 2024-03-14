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

// tipo de dados que representa um triângulo
typedef struct {
    float lado1;
    float lado2;
    float lado3;
    int tipo;
} triangulo;

// número máximo de triângulos suportado pelo programa
#define MAX_TRIANGULOS 100

// tipo de dados que representa um vetor de triângulos
typedef struct {
    int n_triangulos;                     // número de triângulos no vetor
    triangulo triangulos[MAX_TRIANGULOS]; // vetor com os triângulos
} vetor_de_triangulos;

// Você deve implementar as funções faltantes e outras que achar necessário
// abaixo desta linha
bool le_triangulos(vetor_de_triangulos *t)
{
    for(int i = 0; i < t->n_triangulos; i++)
    {
        printf("Digite os lados do triângulo %d:\n", i+1);
        scanf("%f %f %f", &t->triangulos[i].lado1, &t->triangulos[i].lado2, &t->triangulos[i].lado3);
    }

    return true;
}

void classifica_triangulos(vetor_de_triangulos *t) 
{
    for (int i = 0; i < t->n_triangulos; i++) 
    {
        if (t->triangulos[i].lado1 > t->triangulos[i].lado2 + t->triangulos[i].lado3 || t->triangulos[i].lado2 > t->triangulos[i].lado1 + t->triangulos[i].lado3 || t->triangulos[i].lado3 > t->triangulos[i].lado1 + t->triangulos[i].lado2) 
        {
            t->triangulos[i].tipo = 0;
        }
        else if(t->triangulos[i].lado1 == t->triangulos[i].lado2 && t->triangulos[i].lado1 == t->triangulos[i].lado3) 
        {
            t->triangulos[i].tipo = 1;
        } 
        else if (t->triangulos[i].lado1 != t->triangulos[i].lado2 && t->triangulos[i].lado1 != t->triangulos[i].lado3 && t->triangulos[i].lado2 != t->triangulos[i].lado3)
        {
            t->triangulos[i].tipo = 2;
        }
        else 
        {
            t->triangulos[i].tipo = 3;
        }
    }
}

void conta_triangulos(vetor_de_triangulos *t, int contagem[]) 
{
    for (int i = 0; i < t->n_triangulos; i++) 
    {
        switch (t->triangulos[i].tipo) 
        {
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

// essa função deve existir e ser usada para a leitura de um triângulo.
// lê os valores dos 3 lados de um triângulo,
//   inicializa o triângulo apontado por t com esses valores.
// retorna true se bem sucedido ou false em caso de problema (que pode acontecer na
//   parte II)


// Você não deve alterar abaixo desta linha para a parte I do trabalho

int main()
{
    vetor_de_triangulos vetor;
    int n_t;
    int contadores[4] = { 0 };

    printf("Número de triângulos: ");
    scanf("%d", &n_t);
    if (n_t < 1 || n_t > MAX_TRIANGULOS) {
        printf("Deve ser entre %d e %d\n", 1, MAX_TRIANGULOS);
        return 5;
    }
    vetor.n_triangulos = n_t;

    le_triangulos(&vetor);
    classifica_triangulos(&vetor);
    conta_triangulos(&vetor, contadores);

    printf("Classificação dos triângulos:\n");
    printf("  %d equiláteros\n", contadores[1]);
    printf("  %d isósceles\n", contadores[2]);
    printf("  %d escalenos\n", contadores[3]);
    printf("  %d não triângulos\n", contadores[0]);
}