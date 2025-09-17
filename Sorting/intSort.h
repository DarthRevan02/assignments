#ifndef _INSTSORT_H_
#define _INSTSORT_H_

#define LL long long

// Functions to perform sorting,returning the number of comparisons
// The number of swaps is passed back through a pointer

LL bubbleSort(int arr[], int n, LL *swaps);         // Bubble Sort
LL quickSort(int arr[], int n, LL *swaps); // Recursive Quick Sort
LL insertSort(int arr[], int n, LL *swaps);         // Insertion Sort
LL shellSort(int arr[], int n, LL *swaps);       // Shell Sort
LL selectSort(int arr[], int n, LL *swaps);         // Selection Sort
LL heapSort(int arr[], int n, LL *swaps);        // Heap Sort - Recursive Heapify

#endif // _INTSORT_H_
