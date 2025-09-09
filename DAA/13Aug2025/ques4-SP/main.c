/*
 * N-Queens Problem Solution for N = 8
 * 
 * TIME COMPLEXITY ANALYSIS:
 * - Worst case: O(N^N) - placing queens on each row and checking all columns
 * 
 * SPACE COMPLEXITY ANALYSIS:
 * - O(N) for the board array (storing column position for each row)
 * - O(N) for recursion stack depth (maximum N recursive calls)
 * - Total: O(N) = O(8) for N=8
 * 
 * ALGORITHM: Backtracking with constraint checking
 * - Place queens row by row
 * - For each row, try placing queen in each column
 * - Check if placement is safe (no conflicts with previous queens)
 * - If safe, recursively solve for next row
 * - If no solution found, backtrack and try next column
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8  // Size of the chessboard (8x8)

// Global variables
int board[N];  // board[i] represents the column position of queen in row i
int solutionCount = 0;  // Counter for total number of solutions found

/*
 * Function: isSafe
 * Purpose: Check if placing a queen at position (row, col) is safe
 * Parameters: row - current row, col - current column
 * Returns: true if safe, false if conflicts exist
 * 
 * Checks three types of conflicts:
 * 1. Column conflict: Same column as previous queens
 * 2. Main diagonal conflict: (row1-row2) == (col1-col2)
 * 3. Anti-diagonal conflict: (row1-row2) == (col2-col1)
 */
bool isSafe(int row, int col) {
    // Check all previously placed queens (rows 0 to row-1)
    for (int i = 0; i < row; i++) {
        // Check column conflict: queens in same column
        if (board[i] == col) {
            return false;
        }
        
        // Check diagonal conflicts
        // Main diagonal: difference in rows equals difference in columns
        if (abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;  // No conflicts found, position is safe
}

/*
 * Function: printBoard
 * Purpose: Display the current solution on the chessboard
 * Uses 'Q' for queen positions and '.' for empty squares
 */
void printBoard() {
    printf("\nSolution %d:\n", solutionCount);
    printf("   ");
    
    // Print column headers
    for (int i = 0; i < N; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Print each row of the board
    for (int i = 0; i < N; i++) {
        printf("%d  ", i);  // Row header
        for (int j = 0; j < N; j++) {
            if (board[i] == j) {
                printf("Q ");  // Queen position
            } else {
                printf(". ");  // Empty square
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Function: printSolution
 * Purpose: Print the solution in a compact format
 * Shows the column position of queen in each row
 */
void printSolution() {
    printf("Solution %d: [", solutionCount);
    for (int i = 0; i < N; i++) {
        printf("%d", board[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]\n");
}

/*
 * Function: solveNQueens
 * Purpose: Recursive backtracking function to solve N-Queens
 * Parameters: row - current row being processed
 * Returns: true if solution found, false otherwise
 * 
 * ALGORITHM STEPS:
 * 1. Base case: if all rows processed, solution found
 * 2. For current row, try placing queen in each column
 * 3. Check if placement is safe using isSafe()
 * 4. If safe, place queen and recursively solve next row
 * 5. If recursive call succeeds, continue searching for more solutions
 * 6. Backtrack: remove queen and try next column
 */
bool solveNQueens(int row) {
    // Base case: all queens placed successfully
    if (row >= N) {
        solutionCount++;
        printSolution();        // Print compact format
        printBoard();           // Print visual board
        return true;
    }
    
    // Try placing queen in each column of current row
    for (int col = 0; col < N; col++) {
        // Check if placing queen at (row, col) is safe
        if (isSafe(row, col)) {
            // Place queen: store column position for this row
            board[row] = col;
            
            // Recursively solve for next row
            // Note: we continue searching even after finding a solution
            // to find all possible solutions
            solveNQueens(row + 1);
            
            // Backtrack: this is implicit as we'll overwrite board[row]
            // in the next iteration or when function returns
        }
    }
    
    return false;
}

/*
 * Function: main
 * Purpose: Entry point of the program
 * Initializes the board and starts the solving process
 */
int main() {
    printf("N-Queens Problem Solution for N = %d\n", N);
    printf("=======================================\n\n");
    
    // Initialize board array (optional, as we overwrite values anyway)
    for (int i = 0; i < N; i++) {
        board[i] = -1;
    }
    
    printf("Searching for all possible solutions...\n");
    
    // Start solving from row 0
    solveNQueens(0);
    
    // Print final statistics
    printf("\n=======================================\n");
    printf("Total solutions found: %d\n", solutionCount);
    printf("Board size: %d x %d\n", N, N);
    
    return 0;
}

/*
 * ADDITIONAL NOTES:
 * 
 * 1. OPTIMIZATION OPPORTUNITIES:
 *    - Use bit manipulation for faster conflict checking
 *    - Implement symmetry breaking to reduce redundant calculations
 *    - Use iterative deepening for memory efficiency
 * 
 * 2. PROBLEM CHARACTERISTICS:
 *    - For N=8: exactly 92 distinct solutions
 *    - First solution typically found quickly due to backtracking efficiency
 *    - Problem becomes exponentially harder as N increases
 * 
 * 3. REAL-WORLD APPLICATIONS:
 *    - Constraint satisfaction problems
 *    - Resource allocation
 *    - Scheduling problems
 *    - Circuit design and VLSI layout
 */