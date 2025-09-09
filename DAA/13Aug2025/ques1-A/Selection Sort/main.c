/*
Algorithm: Generic Selection Sort

1. Start from the first element of the array.
2. Find the minimum element in the unsorted part using comparison function.
3. Swap it with the first element of the unsorted part.
4. Move boundary forward and repeat until sorted.

Pseudo Code:
procedure SelectionSort(A[1..n], size, cmp)
    for i ← 1 to n-1 do
        min ← i
        for j ← i+1 to n do
            if cmp(A[j], A[min]) < 0 then
                min ← j
            end if
        end for
        if min ≠ i then
            swap A[i] and A[min]
        end if
    end for
end procedure

Time Complexity: O(n^2) - Best, Average, Worst Case
Space Complexity: O(1) - In-place sorting
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function: selectionSort
 * -----------------------
 * Generic selection sort implementation that works with any data type.
 * 
 * How it works:
 * - Cast void pointer to char pointer for byte-level operations
 * - For each position, find the minimum element in remaining array
 * - Swap minimum element with current position
 * - Continue until entire array is sorted
 * 
 * Parameters:
 *   arr  - pointer to array to be sorted (any data type)
 *   n    - number of elements in the array
 *   size - size of each element in bytes (use sizeof(datatype))
 *   cmp  - comparison function that returns:
 *          < 0 if first element is smaller
 *          = 0 if elements are equal  
 *          > 0 if first element is larger
 */
void selectionSort(void *arr, int n, size_t size, int (*cmp)(const void *, const void *)) {
    char *a = (char *)arr;              // Cast to char* for byte arithmetic
    void *tmp = malloc(size);           // Temporary storage for swapping
    
    // Outer loop: iterate through each position (0 to n-2)
    for (int i = 0; i < n - 1; i++) {
        int min = i;                    // Assume current element is minimum
        
        // Inner loop: find actual minimum in unsorted portion (i+1 to n-1)
        for (int j = i + 1; j < n; j++) {
            // Compare element at j with current minimum
            // a + j * size gives pointer to element at index j
            if (cmp(a + j * size, a + min * size) < 0) {
                min = j;                // Update minimum index
            }
        }
        
        // Swap only if minimum is not already at position i
        if (min != i) {
            // Three-step swap using memcpy for any data type:
            memcpy(tmp, a + i * size, size);        // tmp = arr[i]
            memcpy(a + i * size, a + min * size, size);  // arr[i] = arr[min]
            memcpy(a + min * size, tmp, size);      // arr[min] = tmp
        }
    }
    
    free(tmp);                          // Free temporary memory
}

/*
 * Comparison Functions for Different Data Types
 * --------------------------------------------
 * Each function takes two void pointers, casts them to appropriate type,
 * compares the values, and returns standard comparison result.
 */

/*
 * Function: cmpInt
 * ----------------
 * Compares two integers for selection sort.
 * 
 * Parameters:
 *   a, b - void pointers to integers to compare
 * 
 * Returns:
 *   -1 if *a < *b, 0 if *a == *b, 1 if *a > *b
 */
int cmpInt(const void *a, const void *b) {
    int x = *(int*)a;                   // Dereference first integer
    int y = *(int*)b;                   // Dereference second integer
    return (x > y) - (x < y);           // Efficient comparison trick
}

/*
 * Function: cmpFloat
 * ------------------
 * Compares two floating-point numbers for selection sort.
 * 
 * Parameters:
 *   a, b - void pointers to floats to compare
 * 
 * Returns:
 *   -1 if *a < *b, 0 if *a == *b, 1 if *a > *b
 */
int cmpFloat(const void *a, const void *b) {
    float x = *(float*)a;               // Dereference first float
    float y = *(float*)b;               // Dereference second float
    return (x > y) - (x < y);           // Handle floating-point comparison
}

/*
 * Function: cmpChar
 * -----------------
 * Compares two characters for selection sort.
 * 
 * Parameters:
 *   a, b - void pointers to characters to compare
 * 
 * Returns:
 *   Difference in ASCII values (negative, zero, or positive)
 */
int cmpChar(const void *a, const void *b) {
    char x = *(char*)a;                 // Dereference first character
    char y = *(char*)b;                 // Dereference second character
    return x - y;                       // ASCII difference
}

/*
 * Function: cmpStr
 * ----------------
 * Compares two strings for selection sort.
 * 
 * Parameters:
 *   a, b - void pointers to string pointers (char**) to compare
 * 
 * Returns:
 *   Standard strcmp result (negative, zero, or positive)
 */
int cmpStr(const void *a, const void *b) {
    // Cast to char** because we have array of string pointers
    return strcmp(*(char**)a, *(char**)b);
}

/*
 * Function: main
 * --------------
 * Demonstrates generic selection sort with different data types.
 * Shows how to use the same sorting function for integers, floats,
 * characters, and strings by providing appropriate comparison functions.
 */
void main() {
    // Example 1: Sort integers
    printf("Sorting integers...\n");
    int nums[] = {64, 25, 12, 22, 11, 90};
    int nSize = sizeof(nums) / sizeof(nums[0]);     // Calculate array size
    
    // Call: selectionSort(array, count, element_size, comparison_function)
    selectionSort(nums, nSize, sizeof(int), cmpInt);
    
    // Example 2: Sort floating-point numbers
    printf("Sorting floats...\n");
    float vals[] = {3.14f, 2.71f, 1.41f, 1.73f, 0.57f};
    int vSize = sizeof(vals) / sizeof(vals[0]);
    selectionSort(vals, vSize, sizeof(float), cmpFloat);
    
    // Example 3: Sort characters  
    printf("Sorting characters...\n");
    char chars[] = {'z', 'b', 'x', 'a', 'm', 'k'};
    int cSize = sizeof(chars) / sizeof(chars[0]);
    selectionSort(chars, cSize, sizeof(char), cmpChar);
    
    // Example 4: Sort strings
    printf("Sorting strings...\n");
    char *strs[] = {"banana", "apple", "orange", "grape", "kiwi"};
    int sSize = sizeof(strs) / sizeof(strs[0]);
    
    // Note: for strings, element size is sizeof(char*) not sizeof(string)
    selectionSort(strs, sSize, sizeof(char*), cmpStr);
}