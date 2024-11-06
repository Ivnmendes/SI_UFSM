#ifndef _SORT_H_
#define _SORT_H_

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

void Sort(int arr[], int size);


#endif
