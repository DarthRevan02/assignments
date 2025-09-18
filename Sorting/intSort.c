#include "intSort.h"

//Function to perform bubble sort,returning the number of comparisons 
// The number of swaps is passed back through a pointer

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