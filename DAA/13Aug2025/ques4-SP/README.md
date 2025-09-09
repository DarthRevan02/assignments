# N-Queens Problem Solution (N=8)

## Overview
This program solves the classic N-Queens problem for N=8 using a backtracking algorithm. The N-Queens problem involves placing N chess queens on an N×N chessboard so that no two queens attack each other.

## Algorithm
- **Approach**: Backtracking with constraint satisfaction
- **Strategy**: Place queens row by row, checking for conflicts at each step
- **Optimization**: Early pruning when conflicts are detected

## Complexity Analysis
- **Time Complexity**: O(N^N) in the worst case cause we check for every column in every row
- **Space Complexity**: O(N) for the board array and recursion stack
- **For N=8**: Approximately 40,320 operations in worst case

## How to Run
```bash
gcc -o nqueens main.c -Wall -Wextra
./nqueens
```

## Output
- Displays all 92 possible solutions for the 8-Queens problem
- Each solution shows both compact format and visual board representation
- Includes statistics and fun facts about the problem


## Sample Output
```
Solution 1: [0, 4, 7, 5, 2, 6, 1, 3]

Solution 1:
   0 1 2 3 4 5 6 7 
0  Q . . . . . . . 
1  . . . . Q . . . 
2  . . . . . . . Q 
3  . . . . . Q . . 
4  . . Q . . . . . 
5  . . . . . . Q . 
6  . Q . . . . . . 
7  . . . Q . . . . 
```

The program correctly finds all 92 distinct solutions for the 8-Queens problem!
