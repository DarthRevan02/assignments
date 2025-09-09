/*
Ques 7:
Write a function to calculate the nth fibonacci series in the most optimal way.
*/

#include <stdio.h>
#include <math.h>

/*
TIME COMPLEXITY: O(n)
Using an iterative approach to calculate the nth Fibonacci number.
This is efficient and avoids the exponential time complexity of the recursive approach.
*/
long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}


/*
TIME COMPLEXITY: O(1)
Binet's Formula can be used to calculate the nth Fibonacci number in constant time.
But it is not always accurate for large n due to floating-point precision issues.
*/
long long fibonacci_binet(int n){
    double phi = (1 + sqrt(5)) / 2;
    double psi = (1 - sqrt(5)) / 2;
    return (long long)((pow(phi, n) - pow(psi, n)) / sqrt(5));
}

int main(){
    int n;

    printf("Enter the position in Fibonacci series: ");
    scanf("%d", &n);

    printf("Fibonacci number at position %d is (binet): %lld\n", n, fibonacci_binet(n));
}