/*
Algorithm: Generic Insertion Sort

1. Start from the second element (index 1) of the array.
2. Store the current element as key.
3. Compare the key with elements before it using a comparison function.
4. Shift all elements greater than key one position to the right.
5. Insert the key at its correct position.
6. Repeat steps 2-5 for all elements from index 1 to n-1.

Pseudo Code:
procedure GenericInsertionSort(A[1..n], elementSize, compareFunction) 
    for i ← 2 to n do
        key ← A[i]
        j ← i - 1
        while j >= 1 and compareFunction(A[j], key) > 0 do
            A[j+1] ← A[j]
            j ← j - 1
        end while
        A[j+1] ← key
    end for
end procedure

Time Complexity:
- Best Case: O(n) (when the array is already sorted)
- Average Case: O(n^2)
- Worst Case: O(n^2) (when the array is reverse sorted)

Space Complexity:
- O(1) (in-place sorting, only uses temporary variable for key)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generic insertion sort
void insertionSort(void *arr, int n, size_t size, int (*cmp)(const void*, const void*)) {
    char *a = (char*)arr;
    void *key = malloc(size);
    
    for (int i = 1; i < n; i++) {
        memcpy(key, a + i * size, size);           // Store current element
        int j = i - 1;
        
        // Shift elements right until correct position found
        while (j >= 0 && cmp(a + j * size, key) > 0) {
            memcpy(a + (j + 1) * size, a + j * size, size);
            j--;
        }
        
        memcpy(a + (j + 1) * size, key, size);     // Insert key
    }
    
    free(key);
}

// Comparison functions
int cmpInt(const void *a, const void *b) {
    int x = *(int*)a, y = *(int*)b;
    return (x > y) - (x < y);
}

int cmpFloat(const void *a, const void *b) {
    float x = *(float*)a, y = *(float*)b;
    return (x > y) - (x < y);
}

int cmpChar(const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}

int cmpStr(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

// Helper function to print arrays
void printInts(int *arr, int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void printFloats(float *arr, int n) {
    for (int i = 0; i < n; i++) printf("%.2f ", arr[i]);
    printf("\n");
}

void printChars(char *arr, int n) {
    for (int i = 0; i < n; i++) printf("'%c' ", arr[i]);
    printf("\n");
}

void printStrs(char **arr, int n) {
    for (int i = 0; i < n; i++) printf("\"%s\" ", arr[i]);
    printf("\n");
}

int main() {
    printf("=== GENERIC INSERTION SORT DEMO ===\n\n");
    
    // Integer example
    int nums[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(nums) / sizeof(nums[0]);
    
    printf("INTEGERS:\n");
    printf("Original: "); printInts(nums, n);
    insertionSort(nums, n, sizeof(int), cmpInt);
    printf("Sorted:   "); printInts(nums, n);
    printf("\n");
    
    // Float example
    float vals[] = {3.14f, 2.71f, 1.41f, 1.73f};
    n = sizeof(vals) / sizeof(vals[0]);
    
    printf("FLOATS:\n");
    printf("Original: "); printFloats(vals, n);
    insertionSort(vals, n, sizeof(float), cmpFloat);
    printf("Sorted:   "); printFloats(vals, n);
    printf("\n");
    
    // Character example
    char chars[] = {'z', 'b', 'x', 'a', 'm'};
    n = sizeof(chars) / sizeof(chars[0]);
    
    printf("CHARACTERS:\n");
    printf("Original: "); printChars(chars, n);
    insertionSort(chars, n, sizeof(char), cmpChar);
    printf("Sorted:   "); printChars(chars, n);
    printf("\n");
    
    // String example
    char *strs[] = {"banana", "apple", "orange", "grape"};
    n = sizeof(strs) / sizeof(strs[0]);
    
    printf("STRINGS:\n");
    printf("Original: "); printStrs(strs, n);
    insertionSort(strs, n, sizeof(char*), cmpStr);
    printf("Sorted:   "); printStrs(strs, n);
    
    return 0;
}