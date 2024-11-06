#ifndef _BUCKETSORT_H_
#define _BUCKETSORT_H_

void BucketSort(int arr[], int t, int nBuckets, int interval, int min_value, void (*sortFunc)(int[], int));
int getBucketIndex(int value, int interval, int min_value);

#endif