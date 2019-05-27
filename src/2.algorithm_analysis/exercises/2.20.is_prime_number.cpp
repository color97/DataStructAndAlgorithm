#include <iostream>
#include <cmath>

// O(N^(1/2))
bool isPrimeNumber(const int n)
{
    int sqrtN = sqrt(n);
    for (size_t i = 2; i <= sqrtN; i++)
    {
       if (n % 2 == 0)
       {
           return false;
       }      
    }
    
    return true;
}

// O(logN)
int countOfBinaryDigit(const int n)
{
    int count = 1, quotient = n;
    while (quotient = quotient / 2)
    {
        count++;
    }
    
    return count;
}