#ifndef _INSTSORT_H_
#define _INSTSORT_H_

#define LL long long

// Functions to perform sorting,returning the number of comparisons
// The number of swaps is passed back through a pointer


LL bubbleSort(int arr[], int n, LL *swaps);         // Bubble Sort
LL quickSort(int arr[], int n, LL *swaps);          // Recursive Quick Sort
LL insertSort(int arr[], int n, LL *swaps);         // Insertion Sort
LL shellSort(int arr[], int n, LL *swaps);          // Shell Sort
LL selectSort(int arr[], int n, LL *swaps);         // Selection Sort
LL heapSort(int arr[], int n, LL *swaps);           // Heap Sort - Recursive Heapify
LL mergeSort(int arr[], int n, LL *swaps);          // Merge Sort
LL countingSort(int arr[], int n, LL *swaps);       // Counting Sort
LL radixSort(int arr[], int n, LL *swaps);          // Radix Sort
LL bucketSort(int arr[], int n, LL *swaps);         // Bucket Sort

#endif // _INTSORT_H_
