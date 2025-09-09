/*
Algorithm:
1. Read 10 digits (0-9) from the user.
2. Sort the digits to handle duplicates.
3. Generate all unique permutations using backtracking.
4. Print each permutation to a file.
5. Count and print repeating digits and their frequencies.
6. Calculate and print the total number of unique permutations.

Pseudocode:
function permute(arr, l, r, output_file):
    if l == r:
        print arr to output_file
    else:
        for i from l to r:
            if arr[i] is not a duplicate for this position:
                swap arr[l] and arr[i]
                permute(arr, l+1, r, output_file)
                swap arr[l] and arr[i] // backtrack

function count_repeats(arr):
    create frequency array freq[10] = {0}
    for each digit in arr:
        freq[digit]++
    for i in 0 to 9:
        if freq[i] > 1:
            print digit i repeats freq[i] times

function count_permutations(arr):
    n = length of arr
    freq = frequency of each digit
    total = n!
    for each freq[i] > 1:
        total /= freq[i]!
    return total

Time Complexity:
- Generating all unique permutations: O(n! / (freq1! * freq2! ...)), where freqX is the frequency of each repeating digit.
- For 10 unique digits: O(10!) = 3628800
- For duplicates: Reduced by dividing by factorials of frequencies.

Space Complexity:
- O(n) for recursion stack and temporary arrays.

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 10   // We are dealing with digits 0–9 (total 10)

// ----------------------------------------------------
// Utility function: Swap two integers
// Used in the backtracking method for permutation generation
// ----------------------------------------------------
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ----------------------------------------------------
// Part 1: Generate all permutations (assuming NO duplicates)
// Method: Backtracking with recursive swapping
//
// Parameters:
//   arr   -> array of digits
//   start -> current position to fix a digit
//   end   -> last index in the array
//   fptr  -> file pointer to write permutations
//
// Logic:
//   - Fix one digit at 'start'
//   - Recursively permute remaining elements
//   - Swap back (backtrack) to restore original order
// ----------------------------------------------------
void generatePermutations(int *arr, int start, int end, FILE *fptr) {
    if (start == end) {
        // Base case: one valid permutation is formed
        for (int i = 0; i <= end; i++)
            fprintf(fptr, "%d", arr[i]);  // Write permutation to file
        fprintf(fptr, "\n");
        return;
    }

    // Try placing each possible digit at index 'start'
    for (int i = start; i <= end; i++) {
        swap(&arr[start], &arr[i]);                   // Fix digit at 'start'
        generatePermutations(arr, start + 1, end, fptr); // Recurse on remaining
        swap(&arr[start], &arr[i]);                   // Backtrack
    }
}

// ----------------------------------------------------
// Part 2: Generate UNIQUE permutations (handles duplicates)
//
// Idea:
//   - Instead of swapping, use a frequency array of digits (0–9)
//   - At each recursion level, try each digit that still has count > 0
//   - Decrement its frequency, recurse, then restore (backtrack)
//
// Parameters:
//   freq[]  -> frequency array of digits
//   n       -> total number of elements in input
//   level   -> current recursion depth
//   result[]-> stores one candidate permutation
//   fptr    -> file pointer to write permutations
// ----------------------------------------------------
void generateUniquePermutations(int *freq, int n, int level, int *result, FILE *fptr) {
    if (level == n) {
        // Base case: all positions filled, write to file
        for (int i = 0; i < n; i++)
            fprintf(fptr, "%d", result[i]);
        fprintf(fptr, "\n");
        return;
    }

    // Try all possible digits 0–9
    for (int d = 0; d < MAX_DIGITS; d++) {
        if (freq[d] > 0) {              // Use digit only if available
            freq[d]--;                  // Use it
            result[level] = d;          // Place it in current position
            generateUniquePermutations(freq, n, level + 1, result, fptr); // Recurse
            freq[d]++;                  // Backtrack (restore)
        }
    }
}

// ----------------------------------------------------
// Function: printDuplicates
// Checks for duplicate digits in the given array
// and prints their frequency
//
// Parameters:
//   arr -> input array
//   n   -> size of array
// ----------------------------------------------------
void printDuplicates(int *arr, int n) {
    int freq[MAX_DIGITS] = {0};

    // Count frequency of each digit
    for (int i = 0; i < n; i++)
        freq[arr[i]]++;

    printf("Duplicate check:\n");
    int found = 0;

    // Print digits that appear more than once
    for (int i = 0; i < MAX_DIGITS; i++) {
        if (freq[i] > 1) {
            printf("Digit %d repeats %d times\n", i, freq[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No duplicates found.\n");
}

// ----------------------------------------------------
// MAIN FUNCTION
// ----------------------------------------------------
int main() {
    // ------------------------
    // Example 1: Distinct digits 0–9
    // ------------------------
    int digits[MAX_DIGITS];
    for (int i = 0; i < MAX_DIGITS; i++) digits[i] = i;

    FILE *fptr = fopen("permutations.txt", "w");
    if (!fptr) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Generating all permutations of 0–9 (10! = 3,628,800)...\n");
    generatePermutations(digits, 0, MAX_DIGITS - 1, fptr);
    fclose(fptr);
    printf("All permutations saved in permutations.txt\n");

    // ------------------------
    // Example 2: Array with duplicates
    // ------------------------
    int arr[] = {1, 1, 2, 3}; // sample array with duplicates
    int n = sizeof(arr) / sizeof(arr[0]);

    // Prepare frequency array
    int freq[MAX_DIGITS] = {0};
    for (int i = 0; i < n; i++) freq[arr[i]]++;

    // Print duplicate info
    printDuplicates(arr, n);

    FILE *fptr2 = fopen("unique_permutations.txt", "w");
    if (!fptr2) {
        printf("Error opening file!\n");
        return 1;
    }

    // Store current permutation being built
    int *result = (int *)malloc(n * sizeof(int));

    printf("Generating unique permutations for array with duplicates...\n");
    generateUniquePermutations(freq, n, 0, result, fptr2);

    fclose(fptr2);
    free(result);

    printf("Unique permutations saved in unique_permutations.txt\n");

    return 0;
}
