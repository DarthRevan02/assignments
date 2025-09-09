# Random Maze Generator and Solver

### Overview

This program procedurally generates a perfect, random maze using a Randomized Depth-First Search algorithm. After generation, it employs a backtracking algorithm to find and display the solution path from a designated start point to an end point.

### Algorithm

* **Maze Generation: Randomized Depth-First Search (DFS)**
    * The algorithm starts with a grid full of walls.
    * It begins carving paths from a starting cell, recursively moving to unvisited neighboring cells in a random order.
    * This process ensures that every cell in the maze is reachable, creating a "perfect" maze with no loops and a single solution between any two points.

* **Maze Solving: Backtracking**
    * The solver starts at the entrance ('S') and explores a path as far as possible.
    * If it hits a dead end, it "backtracks" by retracing its steps and trying an alternative path from the last junction.
    * The correct path is marked with '.' characters until the exit ('E') is found.

### Complexity Analysis

* **Time Complexity:** **O(W \* H)**, where W is the width and H is the height. Both the generation and solving algorithms visit each cell in the grid a constant number of times.
* **Space Complexity:** **O(W \* H)**. This is required to store the maze grid itself. The recursion stack depth can also reach O(W \* H) in the worst-case scenario of a long, winding path.

### How to Run

1.  **Compile the program** using a C compiler like GCC:
    ```bash
    gcc -o maze main.c -Wall -Wextra
    ```
2.  **Execute the compiled file:**
    ```bash
    ./maze
    ```

### Output

The program will first display the randomly generated maze with a start ('S') and end ('E'). It will then print the solved version of the same maze, with the correct path marked by '.' characters.

### Sample Output

**--- Randomly Generated Maze ---**

```bash
S##############################
# # # # # #
### # ### # # # # # # #####
# # # # # # # # #
##### ### # # ### #
# # # # # # #
####### # # # ##### ### ###
# # # # # # # #
# ### ### ### # ### # #
# # # # # # #
# ### ### # # ####### #####
# # # # # # # # # #
# # ### # # # ### # # # ###
# # # # # #
############################# E
```

**--- Solved Maze ---**
```bash
S..............................#
#.#...#.....#.#...#...#.......#
#.###.#.###.#.#.#.#.#.#.#####.#
#...#...#.#...#.#.#.#.#.#.....#
###.#####.###.#.#.###.#.#######
#.#.......#.#.#.#...#...#.....#
#.#######.#.#.#.#####.###.###.#
#.....#...#.#...#...#.#...#.#.#
#####.#.###.###.###.#.###.#.#.#
#...#.#...#...#...#...#...#...#
#.#.###.###.#.#.#######.#####.#
#.#.#...#.#.#.#.#.....#.#...#.#
#.#.#.###.#.#.#.###.#.#.#.###.#
#...#.....#...#...#.#...#.....#
#############################.E
```