/**
 * Random Maze Generator and Solver
 *
 * TIME COMPLEXITY ANALYSIS:
 * - Maze Generation: O(WIDTH * HEIGHT) - Each cell is visited a constant number of times.
 * - Maze Solving: O(WIDTH * HEIGHT) - In the worst case, the backtracking algorithm visits each cell once.
 *
 * SPACE COMPLEXITY ANALYSIS:
 * - O(WIDTH * HEIGHT) for the maze grid.
 * - O(WIDTH * HEIGHT) for the recursion stack depth in the worst case.
 * - Total: O(WIDTH * HEIGHT)
 *
 * ALGORITHM:
 * - Generation: Randomized Depth-First Search (DFS). It carves paths by recursively visiting neighbors in a random order.
 * - Solving: Backtracking. It explores paths from start to end, marking the correct path and backtracking from dead ends.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // For using bool, true, and false

// --- Maze Constants ---
#define WIDTH 31         // Must be an odd number
#define HEIGHT 21        // Must be an odd number
#define WALL '#'
#define PATH ' '
#define START 'S'
#define END 'E'
#define SOLUTION_PATH '.'

// --- Global Data Structures ---
char maze[HEIGHT][WIDTH]; // Global grid for the maze

// Structure to hold coordinates for cleaner code
typedef struct {
    int r, c;
} Point;

/*
 * Function: initialize_maze
 * Purpose: Fills the entire maze grid with WALL characters to start.
 */
void initialize_maze() {
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            maze[r][c] = WALL;
        }
    }
}

/*
 * Function: print_maze
 * Purpose: Displays the current state of the maze grid to the console.
 */
void print_maze() {
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Function: shuffle
 * Purpose: Randomizes the order of an array of points.
 * Parameters: array - The array of Point structs to shuffle.
 * n - The number of elements in the array.
 * Algorithm: Fisher-Yates shuffle algorithm.
 */
void shuffle(Point array[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Point temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/*
 * Function: generate_maze
 * Purpose: Recursively carves paths into the maze using Randomized DFS.
 * Parameters: r - The current row of the generation algorithm.
 * c - The current column of the generation algorithm.
 */
void generate_maze(int r, int c) {
    maze[r][c] = PATH; // Mark the current cell as a path

    // Find all valid neighbors (2 cells away) that are still walls
    Point neighbors[4];
    int count = 0;
    if (r >= 2 && maze[r - 2][c] == WALL) neighbors[count++] = (Point){r - 2, c};
    if (r < HEIGHT - 2 && maze[r + 2][c] == WALL) neighbors[count++] = (Point){r + 2, c};
    if (c >= 2 && maze[r][c - 2] == WALL) neighbors[count++] = (Point){r, c - 2};
    if (c < WIDTH - 2 && maze[r][c + 2] == WALL) neighbors[count++] = (Point){r, c + 2};

    // Shuffle the neighbors to ensure randomness
    shuffle(neighbors, count);

    // Recursively visit each neighbor
    for (int i = 0; i < count; i++) {
        Point next = neighbors[i];
        if (maze[next.r][next.c] == WALL) {
            // Carve the path between the current cell and the chosen neighbor
            maze[(r + next.r) / 2][(c + next.c) / 2] = PATH;
            generate_maze(next.r, next.c);
        }
    }
}

/*
 * Function: solve_maze
 * Purpose: Recursively finds a path from a given point to the exit.
 * Parameters: r - The current row of the solver.
 * c - The current column of the solver.
 * Returns: true if a path to the end is found, false otherwise.
 */
bool solve_maze(int r, int c) {
    // Base Case: Success! We have reached the end of the maze.
    if (r == HEIGHT - 2 && c == WIDTH - 1) {
        maze[r][c] = END;
        return true;
    }

    // Check for invalid moves: out of bounds, into a wall, or onto an existing path
    if (r < 0 || r >= HEIGHT || c < 0 || c >= WIDTH || maze[r][c] == WALL || maze[r][c] == SOLUTION_PATH) {
        return false;
    }

    // Place a marker on the current cell as part of the potential solution
    maze[r][c] = SOLUTION_PATH;

    // Recursively try to solve from all four directions
    if (solve_maze(r + 1, c)) return true; // Down
    if (solve_maze(r, c + 1)) return true; // Right
    if (solve_maze(r - 1, c)) return true; // Up
    if (solve_maze(r, c - 1)) return true; // Left

    // Backtrack: If no direction led to a solution, this path is a dead end.
    // Un-mark the cell and return failure.
    maze[r][c] = PATH;
    return false;
}

/*
 * Function: main
 * Purpose: Entry point of the program.
 * Orchestrates the maze generation and solving process.
 */
int main() {
    // Seed the random number generator to get a different maze each time
    srand(time(NULL));

    printf("Random Maze Generator and Solver\n");
    printf("=================================\n\n");

    // 1. Fill the grid with walls
    initialize_maze();

    // 2. Carve paths to generate the maze, starting from (1,1)
    generate_maze(1, 1);

    // 3. Define the entrance and exit points
    maze[1][0] = START;
    maze[HEIGHT - 2][WIDTH - 1] = END;

    // 4. Print the final generated maze
    printf("--- Randomly Generated Maze ---\n");
    print_maze();

    // 5. Attempt to solve the maze starting from the entrance
    printf("Searching for a solution...\n");
    if (solve_maze(1, 0)) {
        // Restore the START character as the solver overwrites it
        maze[1][0] = START;
        printf("--- Solved Maze ---\n");
        print_maze();
    } else {
        printf("No solution was found for this maze.\n");
    }

    return 0;
}