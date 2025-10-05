#include "intSort.h"

//Function to perform bubble sort,returning the number of comparisons 
// The number of swaps is passed back through a pointer

// Merge Sort Helper
void merge(int arr[], int l, int m, int r, long long *swaps, long long *comparisons) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            (*swaps)++;
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

long long mergeSortActual(int arr[], int l, int r, long long *swaps) {
    long long comparisons = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        comparisons += mergeSortActual(arr, l, m, swaps);
        comparisons += mergeSortActual(arr, m + 1, r, swaps);
        merge(arr, l, m, r, swaps, &comparisons);
    }
    return comparisons;
}

long long mergeSort(int arr[], int n, long long *swaps) {
    *swaps = 0;
    return mergeSortActual(arr, 0, n - 1, swaps);
}

// Counting Sort (for non-negative integers)
long long countingSort(int arr[], int n, long long *swaps) {
    *swaps = 0;
    long long comparisons = 0;
    if (n <= 1) return 0;
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        comparisons++;
        if (arr[i] > max) max = arr[i];
    }
    int count[max + 1];
    for (int i = 0; i <= max; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[arr[i]]++;
    int idx = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i]-- > 0) {
            arr[idx++] = i;
            (*swaps)++;
        }
    }
    return comparisons;
}

// Radix Sort (for non-negative integers)
int getMax(int arr[], int n, long long *comparisons) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        (*comparisons)++;
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void countSortForRadix(int arr[], int n, int exp, long long *swaps, long long *comparisons) {
    int output[n], count[10] = {0};
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        (*swaps)++;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

long long radixSort(int arr[], int n, long long *swaps) {
    *swaps = 0;
    long long comparisons = 0;
    int m = getMax(arr, n, &comparisons);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSortForRadix(arr, n, exp, swaps, &comparisons);
    }
    return comparisons;
}

// Bucket Sort (for non-negative integers, assumes values in a known range)
#include <stdlib.h>
void insertionForBucket(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

long long bucketSort(int arr[], int n, long long *swaps) {
    *swaps = 0;
    long long comparisons = 0;
    if (n <= 0) return 0;
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        comparisons++;
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    int bucketCount = n;
    int **buckets = (int **)malloc(bucketCount * sizeof(int *));
    int *bucketSizes = (int *)calloc(bucketCount, sizeof(int));
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        int bi = (int)(((long long)(arr[i] - min) * (bucketCount - 1)) / (max - min + 1));
        buckets[bi][bucketSizes[bi]++] = arr[i];
    }
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        insertionForBucket(buckets[i], bucketSizes[i]);
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[idx++] = buckets[i][j];
            (*swaps)++;
        }
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
    return comparisons;
}

long long bubbleSort(int arr[], int n,long long *swaps){

        long long comparisons=0;
        *swaps=0;
        int i,j, temp;
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n-i-1;j++){
                comparisons++;
                if(arr[j]>arr[j+1]){
                    //Swap the elements
                    temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                    (*swaps)++;
                }
            }
        }
        return comparisons;
}

long long quickSortActual(int arr[], int low, int high, long long *swaps) {
    long long comparisons = 0;
    
    if (low < high) {
        // Partition the array
        int pivot = arr[high];
        int i = low - 1;
        int temp;
        
        for (int j = low; j < high; j++) {
            comparisons++;
            if (arr[j] <= pivot) {
                i++;
                // Swap elements
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                (*swaps)++;
            }
        }
        
        // Place pivot in correct position
        temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        (*swaps)++;
        
        int pi = i + 1;
        
        // Recursively sort elements before and after partition
        comparisons += quickSortActual(arr, low, pi - 1, swaps);
        comparisons += quickSortActual(arr, pi + 1, high, swaps);
    }
    
    return comparisons;
}

// Wrapper function to make inputs consistent
long long quickSort(int arr[], int n, long long *swaps) {
    *swaps = 0;
    return quickSortActual(arr, 0, n - 1, swaps);
}


long long insertSort(int arr[], int n, long long *swaps) {
    long long comparisons = 0;
    *swaps = 0;
    int i, j, key;
    
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                // Shift element
                arr[j + 1] = arr[j];
                (*swaps)++;
                j--;
            } else {
                break;
            }
        }
        // Place key in its correct position
        arr[j + 1] = key;
    }
    
    return comparisons;
}

long long selectSort(int arr[], int n, long long *swaps) {
    long long comparisons = 0;
    *swaps = 0;
    int i, j, min_idx, temp;
    
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            // Swap the elements
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            (*swaps)++;
        }
    }
    
    return comparisons;
}

long long shellSort(int arr[], int n, long long *swaps) {
    long long comparisons = 0;
    *swaps = 0;
    int i, j, temp, gap;
    
    // Start with a large gap and reduce it
    for (gap = n / 2; gap > 0; gap /= 2) {
        // Perform insertion sort for elements at current gap
        for (i = gap; i < n; i++) {
            temp = arr[i];
            for (j = i; j >= gap; j -= gap) {
                comparisons++;
                if (arr[j - gap] > temp) {
                    // Shift element
                    arr[j] = arr[j - gap];
                    (*swaps)++;
                } else {
                    break;
                }
            }
            // Place temp in its correct position
            arr[j] = temp;
        }
    }
    
    return comparisons;
}

long long heapify(int arr[], int n, int i, long long *swaps, long long *comparisons) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n) {
        (*comparisons)++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        (*comparisons)++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        // Swap elements
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        (*swaps)++;
        
        // Recursively heapify the affected subtree
        heapify(arr, n, largest, swaps, comparisons);
    }
    
    return *comparisons;
}

long long heapSort(int arr[], int n, long long *swaps) {
    long long comparisons = 0;
    *swaps = 0;
    int i, temp;

    // Build max heap
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, swaps, &comparisons);
    }

    // Extract elements from heap one by one
    for (i = n - 1; i > 0; i--) {
        // Move current root to end
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        (*swaps)++;
        
        // Call heapify on reduced heap
        heapify(arr, i, 0, swaps, &comparisons);
    }
    
    return comparisons;
}