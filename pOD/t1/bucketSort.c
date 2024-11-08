/*Algoritmo original do bucket sort*/
#include "bucketSort.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/*                source:
*       bucket-sort:  https://www.programiz.com/dsa/bucket-sort 
*/

void BucketSort(int arr[], int t, void (*sortFunc)(int[], int));
static int getBucketIndex(int value, int interval, int min_value, int nBuckets);
static void configureBuckets(int tamVet, int min_value, int max_value, int *nBuckets, int *interval);

/* Sorting function*/
void BucketSort(int arr[], int t, void (*sortFunc)(int[], int)) {
  int i, j, k;

  int max_value = INT_MIN, min_value = INT_MAX;
  for (i = 0; i < t; i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    } 
    if (arr[i] < min_value) {
      min_value = arr[i];
    } 
  }

  int nBuckets, interval;
  configureBuckets(t, min_value, max_value, &nBuckets, &interval);

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
      free(bucket_capacities);
      exit(-1);
    }
  }

  /* Initialize bucket capacities*/
  for (i = 0; i < nBuckets; ++i) {
      bucket_capacities[i] = interval;
  }

  /* Fill the buckets with respective elements*/
  for (i = 0; i < t; i++) {
    int pos = getBucketIndex(arr[i], interval, min_value, nBuckets);
    if (bucket_sizes[pos] >= bucket_capacities[pos]) {
        bucket_capacities[pos] = bucket_sizes[pos] + interval;
        buckets[pos] = realloc(buckets[pos], bucket_capacities[pos] * sizeof(int));
        if (buckets[pos] == NULL) {
          fprintf(stderr, "Can't allocate memory for bucket %d!\n", pos);
          for (j = 0; j < pos; j++) {
            free(buckets[j]);
          }
          free(buckets);
          free(bucket_sizes);
          free(bucket_capacities);
          exit(-1);
        }
    }

    buckets[pos][bucket_sizes[pos]++] = arr[i];
  }

  for (i = 0; i < nBuckets; i++) {
    sortFunc(buckets[i], bucket_sizes[i]);
  }
  

  /* Put sorted elements on arr*/
  for (i = 0, j = 0; i < nBuckets; i++) {
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
  free(bucket_capacities);
  return;
}

static int getBucketIndex(int value, int interval, int min_value, int nBuckets) {
  int pos = (value - min_value) / interval;
  if (pos >= nBuckets) {
    pos = nBuckets - 1; 
  }
  return pos;
}

static void configureBuckets(int tamVet, int min_value, int max_value, int *nBuckets, int *interval) {
  int targetPerBucket = (int)sqrt(tamVet);
  int range = max_value - min_value + 1;

  *nBuckets = (tamVet / targetPerBucket);
  if (*nBuckets > range) {
    *nBuckets = range;
  } else if (*nBuckets < 1) {
    *nBuckets = 1;
  }

  *interval = (int)ceil((double)range / *nBuckets);
}