#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/*  source:
*       bucket: https://www.programiz.com/dsa/bucket-sort 
*       quick:  https://joaoarthurbm.github.io/eda/posts/quick-sort/
*/

struct Node {
  int data;
  struct Node *next;
};

void BucketSort(int arr[], int t, int nBuckets, int interval, int min_value);
void QuickSort(int arr[], int left, int right);
int partition(int arr[],  int left, int right);
void swap(int arr[], int x, int y);
int getBucketIndex(int value, int interval, int min_value);

/* Sorting function*/
void BucketSort(int arr[], int t, int nBuckets, int interval, int min_value) {
  int i, j;
  struct Node **buckets;

  /* Create buckets and allocate memory size*/
  buckets = (struct Node **)malloc(sizeof(struct Node *) * nBuckets);

  /* Initialize empty buckets*/
  for (i = 0; i < nBuckets; ++i) {
    buckets[i] = NULL;
  }

  /* Fill the buckets with respective elements*/
  for (i = 0; i < t; ++i) {
    struct Node *current;
    int pos = getBucketIndex(arr[i], interval, min_value);
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  for (i = 0; i < nBuckets; ++i) {
    buckets[i] = QuickSort(buckets[i], 0, interval - 1);
  }
  
  /* Put sorted elements on arr*/
  for (j = 0, i = 0; i < nBuckets; ++i) {
    struct Node *node;
    node = buckets[i];
    while (node) {
      arr[j++] = node->data;
      node = node->next;
    }
  }
  return;
}

void QuickSort(int arr[], int left, int right) {
    if(left < right) {
        int index_pivot = partition(arr, left, right);
        QuickSort(arr, left, index_pivot - 1);
        QuickSort(arr, index_pivot + 1, right);
    }
}

int partition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left;
    int j;

    for(j = left + 1; j <= right; j++) {
        if (arr[j] <= pivot) {
            i += 1;
            swap(arr, i, j);
        }
    }

    swap(arr, left, i);

    return i;
}

void swap(int arr[], int x, int y) {
    int aux = arr[x];
    arr[x] = arr[y];
    arr[y] = aux;
}

int getBucketIndex(int value, int interval, int min_value) {
  return (value - min_value) / interval;
}

int main(int argc, char *argv[]){
    int  i;
    int *vet;
    char linha[16];
    int tamVet;
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
    int interval = ceil((double)(max_value - min_value + 1) / nBuckets);

    BucketSort(vet, tamVet, nBuckets, interval, min_value);

    for(i = 0; i < tamVet; i++) {
        printf("%d\n", vet[i]);
    }
    exit(0);    
}
