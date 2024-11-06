#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>

/*  source:
*       bucket-sort:  https://www.programiz.com/dsa/bucket-sort 
*       shell-sort:   http://desenvolvendosoftware.com.br/algoritmos/ordenacao/shell-sort.html
*   comandos para rodar:
*       gcc -ansi bucketShellSort.c -o bucketShSort.out -lm
*       
*/

void BucketSort(int arr[], int t, int nBuckets, int interval, int min_value);
void ShellSort(int arr[], int t);
int getBucketIndex(int value, int interval, int min_value);

/* Sorting function*/
void BucketSort(int arr[], int t, int nBuckets, int interval, int min_value) {
  int i, j, k;

  /* Start buckets*/
  int **buckets = malloc(nBuckets * sizeof(int *));
  int *bucket_sizes = calloc(nBuckets, sizeof(int)); 
  int *bucket_capacities = calloc(nBuckets, sizeof(int)); 
  if (buckets == NULL || bucket_sizes == NULL || bucket_capacities == NULL) {
    fprintf(stderr, "Can't allocate memory for buckets.\n");
    exit(-1);
  }

  for (i = 0; i < nBuckets; i++) {
    buckets[i] = malloc(interval * sizeof(int));
    if (buckets[i] == NULL) {
      fprintf(stderr, "Can't allocate memory to %d bucket interval.\n", i);
      for (j = 0; j < i; j++) {
        free(buckets[j]);
      }
      free(buckets);
      free(bucket_sizes);
      exit(-1);
    }
  }

  /* Initialize bucket capacities*/
  for (i = 0; i < nBuckets; ++i) {
      bucket_capacities[i] = interval;
  }

  /* Fill the buckets with respective elements*/
  for (i = 0; i < t; i++) {
    int pos = getBucketIndex(arr[i], interval, min_value);

    if (bucket_sizes[pos] >= bucket_capacities[pos]) {
        bucket_capacities[pos] = bucket_sizes[pos] + interval;
        buckets[pos] = realloc(buckets[pos], bucket_capacities[pos] * sizeof(int));
        if (buckets[pos] == NULL) {
          printf("Can't allocate memory for bucket %d!\n", pos);
          exit(1);
        }
    }

    buckets[pos][bucket_sizes[pos]++] = arr[i];
  }


  for (i = 0; i < nBuckets; ++i) {
    ShellSort(buckets[i], bucket_sizes[i]);
  }
  
  /* Put sorted elements on arr*/
  for (i = 0, j = 0; i < nBuckets; ++i) {
    for (k = 0; k < bucket_sizes[i]; k++) {
      arr[j++] = buckets[i][k];
    }
  }

  /* Free the allocated memory */
  for (i = 0; i < nBuckets; i++) {
    free(buckets[i]);
  }

  free(buckets);
  free(bucket_sizes);

  return;
}

/* Function to sort the elements of each bucket*/
void ShellSort(int arr[], int t) {
  int gap = 1;
  int i;

  /* Find initial gap in Knuth's sequence (3^k - 1) / 2 */
  while (gap < t) {
    gap = 3 * gap + 1;
  }

  while (gap > 0) {
    for (i = gap; i < t; i += gap) {
      int j = i;
      int temp = arr[i];

      while ((j >= gap) && (temp < arr[j - gap])) {
        arr[j] = arr[j - gap];
        j -= gap;
      }

      arr[j] = temp;
    }

    gap /= 3;
  }
}

int getBucketIndex(int value, int interval, int min_value) {
  return (value - min_value) / interval;
}

int main(int argc, char *argv[]){
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
        if(vet[i] > maior)
            maior = vet[i];
    }

    int max_value = INT_MIN, min_value = INT_MAX;
    for (i = 0; i < tamVet; i++) {
      if (vet[i] > max_value) max_value = vet[i];
      if (vet[i] < min_value) min_value = vet[i];
    }
    int interval = ceil((double)(max_value - min_value) / nBuckets);

    BucketSort(vet, tamVet, nBuckets, interval, min_value);

    /*
    for(i = 0; i < tamVet; i++) {
      printf("%d\n", vet[i]);
    }
    */

   end = clock();

   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", cpu_time_used);

  exit(0);    
}