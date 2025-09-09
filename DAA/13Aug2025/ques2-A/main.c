#include <stdio.h>
#include <stdlib.h>

// Structure for Tridiagonal Matrix Storage (Case 1)
// Only stores main diagonal and two secondary diagonals
typedef struct {
    double *main;    // Main diagonal (n elements)
    double *upper;   // Upper diagonal (n-1 elements)
    double *lower;   // Lower diagonal (n-1 elements)
    int n;           // Matrix dimension
} TridiagonalMatrix;

// Structure for Pentadiagonal Matrix Storage (Case 2)
// Stores 5 diagonals: main + 2 secondary from each side
typedef struct {
    double *main;     // Main diagonal (n elements)
    double *upper1;   // First upper diagonal (n-1 elements)
    double *upper2;   // Second upper diagonal (n-2 elements)
    double *lower1;   // First lower diagonal (n-1 elements)
    double *lower2;   // Second lower diagonal (n-2 elements)
    int n;            // Matrix dimension
} PentadiagonalMatrix;

/*
ALGORITHM: Tridiagonal Matrix Addition
1. Check if dimensions match
2. Add corresponding diagonal elements
3. Store result in new tridiagonal matrix

PSEUDOCODE:
FOR i = 0 to n-1:
    result.main[i] = A.main[i] + B.main[i]
FOR i = 0 to n-2:
    result.upper[i] = A.upper[i] + B.upper[i]
    result.lower[i] = A.lower[i] + B.lower[i]

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(n) - only storing 3n-2 elements instead of n²
*/
TridiagonalMatrix* addTridiagonal(TridiagonalMatrix* A, TridiagonalMatrix* B) {
    if (A->n != B->n) {
        printf("Error: Matrix dimensions don't match\n");
        return NULL;
    }
    
    TridiagonalMatrix* result = (TridiagonalMatrix*)malloc(sizeof(TridiagonalMatrix));
    result->n = A->n;
    result->main = (double*)malloc(result->n * sizeof(double));
    result->upper = (double*)malloc((result->n - 1) * sizeof(double));
    result->lower = (double*)malloc((result->n - 1) * sizeof(double));
    
    // Add main diagonal elements
    for (int i = 0; i < result->n; i++) {
        result->main[i] = A->main[i] + B->main[i];
    }
    
    // Add upper and lower diagonal elements
    for (int i = 0; i < result->n - 1; i++) {
        result->upper[i] = A->upper[i] + B->upper[i];
        result->lower[i] = A->lower[i] + B->lower[i];
    }
    
    return result;
}

/*
ALGORITHM: Tridiagonal Matrix Subtraction
Similar to addition but with subtraction operation

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(n)
*/
TridiagonalMatrix* subtractTridiagonal(TridiagonalMatrix* A, TridiagonalMatrix* B) {
    if (A->n != B->n) {
        printf("Error: Matrix dimensions don't match\n");
        return NULL;
    }
    
    TridiagonalMatrix* result = (TridiagonalMatrix*)malloc(sizeof(TridiagonalMatrix));
    result->n = A->n;
    result->main = (double*)malloc(result->n * sizeof(double));
    result->upper = (double*)malloc((result->n - 1) * sizeof(double));
    result->lower = (double*)malloc((result->n - 1) * sizeof(double));
    
    for (int i = 0; i < result->n; i++) {
        result->main[i] = A->main[i] - B->main[i];
    }
    
    for (int i = 0; i < result->n - 1; i++) {
        result->upper[i] = A->upper[i] - B->upper[i];
        result->lower[i] = A->lower[i] - B->lower[i];
    }
    
    return result;
}

/*
ALGORITHM: Tridiagonal Matrix Multiplication
Complex operation - result may not be tridiagonal
For true tridiagonal multiplication, result would be pentadiagonal

PSEUDOCODE:
FOR i = 0 to n-1:
    FOR j = max(0, i-2) to min(n-1, i+2):
        result[i][j] = 0
        FOR k = max(0, max(i-1, j-1)) to min(n-1, min(i+1, j+1)):
            result[i][j] += A[i][k] * B[k][j]

TIME COMPLEXITY: O(n) for tridiagonal × tridiagonal
SPACE COMPLEXITY: O(n) - result stored as pentadiagonal
*/
PentadiagonalMatrix* multiplyTridiagonal(TridiagonalMatrix* A, TridiagonalMatrix* B) {
    if (A->n != B->n) {
        printf("Error: Matrix dimensions don't match\n");
        return NULL;
    }
    
    int n = A->n;
    PentadiagonalMatrix* result = (PentadiagonalMatrix*)malloc(sizeof(PentadiagonalMatrix));
    result->n = n;
    result->main = (double*)calloc(n, sizeof(double));
    result->upper1 = (double*)calloc(n-1, sizeof(double));
    result->upper2 = (double*)calloc(n-2, sizeof(double));
    result->lower1 = (double*)calloc(n-1, sizeof(double));
    result->lower2 = (double*)calloc(n-2, sizeof(double));
    
    // Multiplication logic for tridiagonal matrices
    for (int i = 0; i < n; i++) {
        // Main diagonal calculation
        result->main[i] += A->main[i] * B->main[i];
        
        // Upper diagonal contributions
        if (i > 0) {
            result->main[i] += A->lower[i-1] * B->upper[i-1];
        }
        if (i < n-1) {
            result->main[i] += A->upper[i] * B->lower[i];
        }
        
        // First upper diagonal
        if (i < n-1) {
            result->upper1[i] += A->main[i] * B->upper[i];
            result->upper1[i] += A->upper[i] * B->main[i+1];
            if (i > 0) {
                result->upper1[i] += A->lower[i-1] * B->main[i+1];
            }
        }
        
        // First lower diagonal
        if (i > 0) {
            result->lower1[i-1] += A->main[i] * B->lower[i-1];
            result->lower1[i-1] += A->lower[i-1] * B->main[i-1];
            if (i < n-1) {
                result->lower1[i-1] += A->upper[i] * B->main[i-1];
            }
        }
        
        // Second upper diagonal
        if (i < n-2) {
            result->upper2[i] += A->upper[i] * B->upper[i+1];
        }
        
        // Second lower diagonal
        if (i > 1) {
            result->lower2[i-2] += A->lower[i-1] * B->lower[i-2];
        }
    }
    
    return result;
}

/*
ALGORITHM: Pentadiagonal Matrix Addition
Similar to tridiagonal but with 5 diagonals

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(n) - storing 5n-6 elements instead of n²
*/
PentadiagonalMatrix* addPentadiagonal(PentadiagonalMatrix* A, PentadiagonalMatrix* B) {
    if (A->n != B->n) {
        printf("Error: Matrix dimensions don't match\n");
        return NULL;
    }
    
    PentadiagonalMatrix* result = (PentadiagonalMatrix*)malloc(sizeof(PentadiagonalMatrix));
    result->n = A->n;
    result->main = (double*)malloc(result->n * sizeof(double));
    result->upper1 = (double*)malloc((result->n - 1) * sizeof(double));
    result->upper2 = (double*)malloc((result->n - 2) * sizeof(double));
    result->lower1 = (double*)malloc((result->n - 1) * sizeof(double));
    result->lower2 = (double*)malloc((result->n - 2) * sizeof(double));
    
    for (int i = 0; i < result->n; i++) {
        result->main[i] = A->main[i] + B->main[i];
    }
    
    for (int i = 0; i < result->n - 1; i++) {
        result->upper1[i] = A->upper1[i] + B->upper1[i];
        result->lower1[i] = A->lower1[i] + B->lower1[i];
    }
    
    for (int i = 0; i < result->n - 2; i++) {
        result->upper2[i] = A->upper2[i] + B->upper2[i];
        result->lower2[i] = A->lower2[i] + B->lower2[i];
    }
    
    return result;
}

/*
ALGORITHM: Pentadiagonal Matrix Subtraction
TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(n)
*/
PentadiagonalMatrix* subtractPentadiagonal(PentadiagonalMatrix* A, PentadiagonalMatrix* B) {
    if (A->n != B->n) {
        printf("Error: Matrix dimensions don't match\n");
        return NULL;
    }
    
    PentadiagonalMatrix* result = (PentadiagonalMatrix*)malloc(sizeof(PentadiagonalMatrix));
    result->n = A->n;
    result->main = (double*)malloc(result->n * sizeof(double));
    result->upper1 = (double*)malloc((result->n - 1) * sizeof(double));
    result->upper2 = (double*)malloc((result->n - 2) * sizeof(double));
    result->lower1 = (double*)malloc((result->n - 1) * sizeof(double));
    result->lower2 = (double*)malloc((result->n - 2) * sizeof(double));
    
    for (int i = 0; i < result->n; i++) {
        result->main[i] = A->main[i] - B->main[i];
    }
    
    for (int i = 0; i < result->n - 1; i++) {
        result->upper1[i] = A->upper1[i] - B->upper1[i];
        result->lower1[i] = A->lower1[i] - B->lower1[i];
    }
    
    for (int i = 0; i < result->n - 2; i++) {
        result->upper2[i] = A->upper2[i] - B->upper2[i];
        result->lower2[i] = A->lower2[i] - B->lower2[i];
    }
    
    return result;
}

// Utility functions for memory management
void freeTridiagonal(TridiagonalMatrix* matrix) {
    if (matrix) {
        free(matrix->main);
        free(matrix->upper);
        free(matrix->lower);
        free(matrix);
    }
}

void freePentadiagonal(PentadiagonalMatrix* matrix) {
    if (matrix) {
        free(matrix->main);
        free(matrix->upper1);
        free(matrix->upper2);
        free(matrix->lower1);
        free(matrix->lower2);
        free(matrix);
    }
}

// Display functions for testing
void printTridiagonal(TridiagonalMatrix* matrix) {
    printf("Tridiagonal Matrix %dx%d:\n", matrix->n, matrix->n);
    for (int i = 0; i < matrix->n; i++) {
        for (int j = 0; j < matrix->n; j++) {
            if (i == j) {
                printf("%.2f ", matrix->main[i]);
            } else if (i == j - 1 && j < matrix->n) {
                printf("%.2f ", matrix->upper[i]);
            } else if (i == j + 1 && i > 0) {
                printf("%.2f ", matrix->lower[j]);
            } else {
                printf("0.00 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
SPACE COMPLEXITY ANALYSIS:
- Regular NxN matrix: O(n²) space
- Tridiagonal storage: O(3n-2) ≈ O(n) space
- Pentadiagonal storage: O(5n-6) ≈ O(n) space
- Space savings: For n=1000, regular matrix needs 1M elements, 
  tridiagonal needs only ~3K elements (99.7% space reduction)

TIME COMPLEXITY ANALYSIS:
- All operations (add, subtract): O(n) instead of O(n²)
- Multiplication: O(n) for band matrices instead of O(n³)
*/