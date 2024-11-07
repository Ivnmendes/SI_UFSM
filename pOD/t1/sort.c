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

static void quick_sort(int arr[], int left, int right);
static void swap(int arr[], int x, int y);
static int partition(int arr[], int left, int right);

void QuickSort(int arr[], int t);
void CocktailSort(int arr[], int t);
void InsertionSort(int arr[], int t);
void ShellSort(int arr[], int t);

void QuickSort(int arr[], int t) {
  int i;
  quick_sort(arr, 0, t - 1);
}

static void quick_sort(int arr[], int left, int right) {
  if(left < right) {
    int index_pivot = partition(arr, left, right);
    quick_sort(arr, left, index_pivot - 1);
    quick_sort(arr, index_pivot + 1, right);
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

static int partition(int arr[], int left, int right) {
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

static void swap(int arr[], int x, int y) {
  int aux = arr[x];
  arr[x] = arr[y];
  arr[y] = aux;
}
