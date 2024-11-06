#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "bucketSort.h"

/*              source:
*   QuickSort:        https://joaoarthurbm.github.io/eda/posts/quick-sort/
*   CocktailSort:     https://pt.wikipedia.org/wiki/Cocktail_sort
*   InsertionSort:    https://www.geeksforgeeks.org/insertion-sort-algorithm/
*   ShellSort:        http://desenvolvendosoftware.com.br/algoritmos/ordenacao/shell-sort.html
*/

void QuickSort(int arr[], int left, int right);
void CocktailSort(int arr[], int t);
void InsertionSort(int arr[], int t);
void ShellSort(int arr[], int t);
int partition(int arr[], int left, int right);
void swap(int arr[], int x, int y);

void quick_sort(int arr[], int t) {
  QuickSort(arr, 0, t - 1);
}

void QuickSort(int arr[], int left, int right) {
  if(left < right) {
    int index_pivot = partition(arr, left, right);
    QuickSort(arr, left, index_pivot - 1);
    QuickSort(arr, index_pivot + 1, right);
  }
}

void CocktailSort(int arr[], int t) {
  int i, bottom, top, swapped, aux;
  bottom = 0;
  top = t - 1;
  swapped = 0;
  while(!swapped && bottom < top) {
    swapped = 1;
    for (i = bottom; i < top; i++) {
      if (arr[i] > arr[i+1]) {
        swap(arr, i, i + 1);
        swapped = 0;
      }  
    }

    top--;
    
    for (i = top; i > bottom; i--) {
      if (arr[i] < arr[i - 1]) {
        swap(arr, i, i - 1);
        swapped = 0;
      }
    }

    bottom++;
  }
}

void InsertionSort(int arr[], int t) {
  int i;
  for (i = 1; i < t; ++i) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

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

#ifdef INSERTION_SORT
  #define Sort InsertionSort
#elif defined QUICK_SORT
  #define Sort QuickSort
#elif defined COCKTAIL_SORT
  #define Sort CocktailSort
#elif defined SHELL_SORT
  #define Sort ShellSort
#else
    #error "Nenhum algoritmo de ordenação definido. Defina INSERTION_SORT ou QUICK_SORT."
#endif