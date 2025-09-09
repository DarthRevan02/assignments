/*
TIME COMPLEXITY ANALYSIS:

SPACE COMPLEXITY ANALYSIS:
*/

#include <stdio.h>
#include <math.h>

// This creates a generic function macro, that will resolve to the appropriate function 
// based on the type of the arguments passed during compile time.
#define calculate_power(base, exponent) _Generic((base) + (exponent), \
    int: calculate_power_int, \
    default: calculate_power_double \
)(base, exponent)

// Function to calculate power for double values, using exp and log for better precision
double calculate_power_double(double base, double exponent) {

    // e^( y * ln(x) ) = e^(ln(x^y)) = x^y

    printf("Calculating power for doubles: %.2f^%.2f\n", base, exponent);
    return exp(exponent * log(base));
}

/*
- This function is better suited for integer calculations, using a more efficient method.
- This only works for non-negative integer exponents.
- This only works for small integer bases and exponents, as it does not handle large values that could overflow.
*/
int calculate_power_int(int base, int exponent) {
    printf("Calculating power for integers: %d^%d\n", base, exponent);
    
    if (base == 0 && exponent == 0) {
        return 1; // 0^0 is considered as 1 in many contexts
    }
    if (exponent < 0) {
        return 0; // Negative exponent for integers is not handled
    }
    if (exponent == 0) {
        return 1; // Any number to the power of 0 is 1
    }
    
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base; // If exponent is odd, multiply by base
            exponent = (exponent - 1) / 2; // Reduce exponent by 1 and divide by 2
        }
        else {
            exponent /= 2; // Divide exponent by 2
        }
        base *= base; // Square the base
    }
    return result;
}

int main() {
    double base = 3.141;
    double exponent = 2.78;
    double result = calculate_power(base, exponent);
    printf("The result of %.2f raised to the power of %.2f is %.2f\n", base, exponent, result);
    printf("The result of %.2f raised to the power of %.2f using pow() is %.2f\n", base, exponent, pow(base, exponent));


    int int_base = -4;
    int int_exponent = 9;
    // 4^10 works well with the integer power function
    // but 4^16 will overflow for int, so we should use the double version for larger powers
    // This is a good test case for the integer power function.

    int int_result = calculate_power(int_base, int_exponent);
    printf("The result of %d raised to the power of %d is %d\n", int_base, int_exponent, int_result);
    printf("The result of %d raised to the power of %d using pow() is %.2f\n", int_base, int_exponent, pow(int_base, int_exponent));
    return 0;
}