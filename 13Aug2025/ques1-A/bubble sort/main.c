/*
Algorithm: Generic Bubble Sort

1. Start from the first element of the array.
2. Compare current element with next using comparison function.
3. If elements are in wrong order, swap them.
4. Repeat for all elements, reducing range each pass.
5. Continue until no swaps needed (optimization).

Pseudo Code:
procedure BubbleSort(A[1..n], size, cmp) 
    for i ← 1 to n-1 do
        swapped ← false
        for j ← 1 to n-i do
            if cmp(A[j], A[j+1]) > 0 then
                swap A[j] and A[j+1]
                swapped ← true
            end if
        end for
        if swapped = false then break
    end for
end procedure

Time Complexity: O(n) best, O(n^2) average/worst
Space Complexity: O(1) - In-place sorting
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generic bubble sort function
void bubbleSort(void *arr, int n, size_t size, int (*cmp)(const void *, const void *)) {
    char *a = (char *)arr;              // Cast for byte arithmetic
    void *tmp = malloc(size);           // Temporary swap space
    
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;                // Track if any swaps occurred
        
        // Compare adjacent elements, reduce range each pass
        for (int j = 0; j < n - i - 1; j++) {
            void *curr = a + j * size;          // Current element
            void *next = a + (j + 1) * size;    // Next element
            
            // Swap if elements are in wrong order
            if (cmp(curr, next) > 0) {
                memcpy(tmp, curr, size);        // tmp = curr
                memcpy(curr, next, size);       // curr = next
                memcpy(next, tmp, size);        // next = tmp
                swapped = 1;
            }
        }
        
        // Early termination if array is sorted
        if (!swapped) break;
    }
    
    free(tmp);
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
    char x = *(char*)a, y = *(char*)b;
    return x - y;
}

int cmpStr(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

void main() {
    // Integer example
    int nums[] = {64, 34, 25, 12, 22, 11, 90};
    int nSize = sizeof(nums) / sizeof(nums[0]);
    
    printf("Original integers: ");
    for (int i = 0; i < nSize; i++) printf("%d ", nums[i]);
    
    bubbleSort(nums, nSize, sizeof(int), cmpInt);
    
    printf("\nSorted integers:   ");
    for (int i = 0; i < nSize; i++) printf("%d ", nums[i]);
    printf("\n\n");
    
    // Float example
    float vals[] = {3.14f, 2.71f, 1.41f, 1.73f};
    int vSize = sizeof(vals) / sizeof(vals[0]);
    
    printf("Original floats: ");
    for (int i = 0; i < vSize; i++) printf("%.2f ", vals[i]);
    
    bubbleSort(vals, vSize, sizeof(float), cmpFloat);
    
    printf("\nSorted floats:   ");
    for (int i = 0; i < vSize; i++) printf("%.2f ", vals[i]);
    printf("\n\n");
    
    // Character example
    char chars[] = {'z', 'b', 'x', 'a', 'm'};
    int cSize = sizeof(chars) / sizeof(chars[0]);
    
    printf("Original chars: ");
    for (int i = 0; i < cSize; i++) printf("'%c' ", chars[i]);
    
    bubbleSort(chars, cSize, sizeof(char), cmpChar);
    
    printf("\nSorted chars:   ");
    for (int i = 0; i < cSize; i++) printf("'%c' ", chars[i]);
    printf("\n\n");
    
    // String example
    char *strs[] = {"banana", "apple", "orange", "grape"};
    int sSize = sizeof(strs) / sizeof(strs[0]);
    
    printf("Original strings: ");
    for (int i = 0; i < sSize; i++) printf("\"%s\" ", strs[i]);
    
    bubbleSort(strs, sSize, sizeof(char*), cmpStr);
    
    printf("\nSorted strings:   ");
    for (int i = 0; i < sSize; i++) printf("\"%s\" ", strs[i]);
    printf("\n");
}