# Fibonacci Number Calculator - Question 7

This program implements two different approaches to calculate the nth Fibonacci number, showcasing the trade-offs between time complexity and numerical accuracy.

## Problem Statement
Write a function to calculate the nth fibonacci series in the most optimal way.

## Solutions Implemented

### 1. Iterative Approach - O(n)
```c
long long fibonacci(int n)
```
- **Time Complexity:** O(n)
- **Space Complexity:** O(1)
- **Accuracy:** Perfect for all valid inputs
- **Advantages:** Simple, accurate, memory efficient
- **Use Case:** When accuracy is crucial

### 2. Binet's Formula - O(1)
```c
long long fibonacci_binet(int n)
```
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)
- **Accuracy:** Limited due to floating-point precision
- **Advantages:** Constant time complexity
- **Use Case:** When speed is more important than perfect accuracy for large numbers

## Binet's Formula Derivation

### Step 1: Characteristic Equation
The Fibonacci recurrence relation is: F(n) = F(n-1) + F(n-2)

Assume a solution of the form F(n) = r^n, then:
```
r^n = r^(n-1) + r^(n-2)
r^2 = r + 1
r^2 - r - 1 = 0
```

### Step 2: Solving the Quadratic
Using the quadratic formula:
```
r = (1 ± √5) / 2
```

This gives us two roots:
- φ (phi) = (1 + √5) / 2 ≈ 1.618 (Golden Ratio)
- ψ (psi) = (1 - √5) / 2 ≈ -0.618

### Step 3: General Solution
The general solution is:
```
F(n) = A·φ^n + B·ψ^n
```

### Step 4: Finding Constants
Using initial conditions F(0) = 0 and F(1) = 1:

For F(0) = 0:
```
A + B = 0
Therefore: B = -A
```

For F(1) = 1:
```
A·φ + B·ψ = 1
A·φ - A·ψ = 1
A(φ - ψ) = 1
A = 1/(φ - ψ) = 1/√5
```

### Step 5: Final Formula
```
F(n) = (φ^n - ψ^n) / √5
```

Where:
- φ = (1 + √5) / 2
- ψ = (1 - √5) / 2

## Why Binet's Formula Becomes Inaccurate

### 1. Floating-Point Precision Limits
- **Double precision:** ~15-16 decimal digits
- **φ^n grows exponentially:** For large n, φ^n becomes very large
- **Subtraction of large numbers:** (φ^n - ψ^n) involves subtracting two large numbers, amplifying rounding errors

### 2. Mathematical Analysis
- As n increases, |ψ^n| becomes very small (since |ψ| < 1)
- The formula essentially becomes: F(n) ≈ φ^n / √5
- For large n, we're computing: `round(very_large_number / √5)`
- Small errors in φ^n get magnified when divided by √5

### 3. Error Propagation Example
For n = 50:
- φ^50 ≈ 1.259 × 10^10 (requires high precision)
- Any rounding error in this calculation affects the final result
- The error becomes significant when converted to integer

### 4. Practical Limitations
```c
// Accurate up to approximately n ≤ 70-75
printf("F(70) iterative: %lld\n", fibonacci(70));     // Accurate
printf("F(70) Binet:     %lld\n", fibonacci_binet(70)); // May differ
```

## Compilation and Usage

```bash
gcc -o fibonacci main.c -lm
./fibonacci
```

## Better Alternatives for Large Numbers

For the most optimal solution considering both time and accuracy, **Matrix Exponentiation** with O(log n) complexity is recommended:

```c
// O(log n) time, perfect accuracy
long long fibonacci_matrix(int n) {
    // Uses matrix [[1,1],[1,0]]^n approach
}
```

## Comparison Table

| Method | Time | Space | Accuracy | Best Use Case |
|--------|------|-------|----------|---------------|
| Iterative | O(n) | O(1) | Perfect | Small to medium n |
| Binet's | O(1) | O(1) | Limited | Quick approximations |
| Matrix Exp | O(log n) | O(1) | Perfect | Large n, optimal solution |

## Conclusion

While Binet's formula provides theoretical O(1) complexity, the iterative approach is more practical for most applications due to its perfect accuracy. For truly optimal performance with large numbers, matrix exponentiation offers the best balance of speed