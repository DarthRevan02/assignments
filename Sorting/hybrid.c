#include "intSort.h"

long long hybridSort(int arr[], int n, long long *swaps) {
  const int firstThreshold = 14;    // Threshold for switching to heap sort
  const int secondThreshold = 4000; // Threshold for switching to quick sort
  if (n <= firstThreshold) {
    // insert sort for 2-14 elements
    return insertSort(arr, n, swaps);
  } else if (n <= secondThreshold) {
    // heap sort for 15-4000 elements
    return heapSort001(arr, n, swaps);
  } else {
    // quick sort for >4000 elements
    return quickSortRecursive(arr, n, swaps);
  }
}
