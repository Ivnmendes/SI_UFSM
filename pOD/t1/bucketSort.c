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
static int getBucketIndex(int value, int interval, int minValue, int nBuckets);
static void configureBuckets(int tamVet, int minValue, int maxValue, int *nBuckets, int *interval);

/* Sorting function*/
void BucketSort(int arr[], int t, void (*sortFunc)(int[], int)) {
  int i, j, k;

  int maxValue = INT_MIN, minValue = INT_MAX;
  for (i = 0; i < t; i++) {
    if (arr[i] > maxValue) {
      maxValue = arr[i];
    } 
    if (arr[i] < minValue) {
      minValue = arr[i];
    } 
  }

  int nBuckets, interval;
  configureBuckets(t, minValue, maxValue, &nBuckets, &interval);

  /* Start buckets*/
  int **buckets = malloc(nBuckets * sizeof(int *));
  int *bucketSizes = calloc(nBuckets, sizeof(int)); 
  int *bucketCapacities = calloc(nBuckets, sizeof(int)); 
  if (buckets == NULL || bucketSizes == NULL || bucketCapacities == NULL) {
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
      free(bucketSizes);
      free(bucketCapacities);
      exit(-1);
    }
  }

  /* Initialize bucket capacities*/
  for (i = 0; i < nBuckets; ++i) {
      bucketCapacities[i] = interval;
  }

  /* Fill the buckets with respective elements*/
  for (i = 0; i < t; i++) {
    int pos = getBucketIndex(arr[i], interval, minValue, nBuckets);
    if (bucketSizes[pos] >= bucketCapacities[pos]) {
        bucketCapacities[pos] = bucketSizes[pos] + interval;
        buckets[pos] = realloc(buckets[pos], bucketCapacities[pos] * sizeof(int));
        if (buckets[pos] == NULL) {
          fprintf(stderr, "Can't allocate memory for bucket %d!\n", pos);
          for (j = 0; j < pos; j++) {
            free(buckets[j]);
          }
          free(buckets);
          free(bucketSizes);
          free(bucketCapacities);
          exit(-1);
        }
    }

    buckets[pos][bucketSizes[pos]++] = arr[i];
  }

  for (i = 0; i < nBuckets; i++) {
    sortFunc(buckets[i], bucketSizes[i]);
  }
  

  /* Put sorted elements on arr*/
  for (i = 0, j = 0; i < nBuckets; i++) {
    for (k = 0; k < bucketSizes[i]; k++) {
      arr[j++] = buckets[i][k];
    }
  }

  /* Free the allocated memory */
  for (i = 0; i < nBuckets; i++) {
    free(buckets[i]);
  }

  free(buckets);
  free(bucketSizes);
  free(bucketCapacities);
  return;
}

static int getBucketIndex(int value, int interval, int minValue, int nBuckets) {
  int pos = (value - minValue) / interval;
  if (pos >= nBuckets) {
    pos = nBuckets - 1; 
  }
  return pos;
}

static void configureBuckets(int tamVet, int minValue, int maxValue, int *nBuckets, int *interval) {
  int targetPerBucket = (int)sqrt(tamVet);
  int range = maxValue - minValue + 1;

  *nBuckets = (tamVet / targetPerBucket);
  if (*nBuckets > range) {
    *nBuckets = range;
  } else if (*nBuckets < 1) {
    *nBuckets = 1;
  }

  *interval = (int)ceil((double)range / *nBuckets);
}