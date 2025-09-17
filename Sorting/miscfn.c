#include <math.h>
#include "miscfn.h"

// Function to calculate the average of an array of doubles
double calcAvg(double arr[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}

// Function to calculate the standard deviation of an array of doubles
double calcSD(double arr[], int n, double mean)
{
    double sumSqDiff = 0.0;
    for (int i = 0; i < n; i++)
    {
        sumSqDiff += pow(arr[i] - mean, 2);
    }
    return sqrt(sumSqDiff / n);
}

// Function to calculate the average of an array of long long
double calcAvgLL(long long arr[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}
// Function to calculate the standard deviation of an array of long long
double calcSDLL(long long arr[], int n, double mean)
{
    double sumSqDiff = 0.0;
    for (int i = 0; i < n; i++)
    {
        sumSqDiff += pow(arr[i] - mean, 2);
    }
    return sqrt(sumSqDiff / n);
}