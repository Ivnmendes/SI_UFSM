#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#include "bucketSort.h"
#include "sort.h"

#ifdef INSERTION_SORT
  #define Sort InsertionSort
  #define SORT_NAME "InsertionSort"
#elif defined QUICK_SORT
  #define Sort QuickSort
  #define SORT_NAME "QuickSort"
#elif defined COCKTAIL_SORT
  #define Sort CocktailSort
  #define SORT_NAME "CocktailSort"
#elif defined SHELL_SORT
  #define Sort ShellSort
  #define SORT_NAME "ShellSort"
#else
  #error "Nenhum algoritmo de ordenação definido. Defina INSERTION_SORT ou QUICK_SORT."
#endif

/*          Como rodar
*   gcc -ansi -DINSERTION_SORT -o program.out program.c bucketSort.c sort.c -lm
*       No lugar de -DInsertion_Sort passe uma das seguintes flags
*           -DINSERTION_SORT, -DQUICK_SORT, -DCOCKTAIL_SORT, -DSHELL_SORT
*   Para executar ./program.out NDeElementos < txtDeEntrada.txt
*/
int main(int argc, char *argv[]){
  printf("\n%s: %d numeros\n", SORT_NAME, atoi(argv[1]));
  clock_t start, end;
  double cpu_time_used;

  start = clock();

  int  i;
  int *vet;
  int tamVet;
  char linha[16];
  int maior = -1;

  if(argc < 2){
    printf("Uso: %s <numero de elementos a ordenar parcialmente>\n", argv[0]);
    exit(0);
  }
  tamVet = atoi(argv[1]);
  int nBuckets = (int)sqrt(tamVet);
  vet = (int *) malloc(sizeof(int) * tamVet);

  for(i=0; i<tamVet; i++){
    fgets(linha, 16, stdin);
    sscanf(linha, "%d", &vet[i]);
    if(vet[i] > maior) {
      maior = vet[i];
    }
  }

  int max_value = INT_MIN, min_value = INT_MAX;
  for (i = 0; i < tamVet; i++) {
    if (vet[i] > max_value) {
      max_value = vet[i];
    } 
    if (vet[i] < min_value) {
      min_value = vet[i];
    } 
  }
  int interval = ceil((double)(max_value - min_value) / nBuckets);

  BucketSort(vet, tamVet, nBuckets, interval, min_value, Sort);

  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Tempo de execução: %f segundos\n", cpu_time_used);

  exit(0);    
}