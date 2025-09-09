#include <stdio.h>

// Function to calculate nth Catalan number
long long catalan(int n) {
    if (n <= 1) {
        return 1;
    }
    
    long long result = 0;
    for (int i = 0; i < n; i++) {
        result += catalan(i) * catalan(n - 1 - i);
    }
    
    return result;
}

// Optimized function using dynamic programming
long long catalanDP(int n) {
    if (n <= 1) {
        return 1;
    }
    
    long long dp[n + 1];
    dp[0] = dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = 0;
        for (int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }
    
    return dp[n];
}

int main() {
    int n;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    
    if (n < 0) {
        printf("Number of nodes cannot be negative.\n");
        return 1;
    }
    
    long long result = catalanDP(n);
    printf("Number of binary trees with %d unlabelled nodes: %lld\n", n, result);
    
    return 0;
}