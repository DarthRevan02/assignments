# Catalan Number: Counting Binary Trees

This program calculates the number of binary trees that can be formed with a given number of unlabelled nodes using the Catalan number sequence.

## Problem Statement

Given `n` unlabelled nodes, find the number of distinct binary trees that can be formed. The answer is given by the nth Catalan number.

## Approach

- **Recursive Solution:** Calculates the Catalan number using recursion (inefficient for large `n`).
- **Dynamic Programming Solution:** Uses a bottom-up DP approach for efficient computation.

The program uses the optimized dynamic programming approach by default.

## How to Run

1. Compile the code:
	```sh
	gcc main.c -o main
	```
2. Run the executable:
	```sh
	./main
	```
3. Enter the number of nodes when prompted.

## Example

```
Enter the number of nodes: 3
Number of binary trees with 3 unlabelled nodes: 5
```

## Files

- `main.c` : Source code for calculating the Catalan number.
- `README.md` : This file.

## Author

Aadi Jain

## Date

August 19, 2025