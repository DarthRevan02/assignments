# Power function in C
Here is an implementation of the power function in C.

The **most optimal** way to find out the power of a number raised to another is by using logrithms. Yes, there is a O($logn$) method to figure out the power (leetcode question), but it only works for integers. What if you have to figure out $a^b$ when both $a$ and $b$ are $float$??

We have to use the type of maths they had to use back in the day when solving problems by hand.

## Logrithms

Let me take you back to the early 17th century when computation was a laborious task. Imagine trying to multiply large numbers like 47,382 × 93,847 by hand. Astronomers and navigators faced such calculations daily.

**The Problem**: Multiplication and division of large numbers was extraordinarily time-consuming and error-prone.

**The Insight**: John Napier observed that any positive number can be expressed as a power of another number. If we could find a systematic way to work with these exponents, we could transform:
- Multiplication → Addition
- Division → Subtraction  
- Powers → Multiplication

**The Mathematical Foundation**: 
For any base $b > 0, b ≠ 1$, the logarithm $\log_b(x)$ answers the question: "To what power must we raise $b$ to get $x$?"

Formally: If $b^y = x$, then $\log_b(x) = y$

**The Revolutionary Properties**:
1. $\log_b(xy) = \log_b(x) + \log_b(y)$ (multiplication becomes addition)
2. $\log_b(x/y) = \log_b(x) - \log_b(y)$ (division becomes subtraction)
3. $\log_b(x^n) = n \cdot \log_b(x)$ (exponentiation becomes multiplication)

**For our power function**: When computing $a^b$ with floating-point numbers, we leverage the natural logarithm:

$$a^b = e^{b \cdot \ln(a)}$$

This works because $e^{\ln(a)} = a$, so raising both sides to the power $b$ gives us our desired result.

Logarithms didn't just solve a computational problem - they revealed a fundamental structure in mathematics that connects exponential growth, harmonic series, and the very fabric of calculus itself.

