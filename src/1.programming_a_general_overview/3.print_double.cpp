#include<cstdio>
#include <random>

#define ABS(x)  ((x) > 0 ? (x) : -(x))

void printDigit(int digit)
{
    printf("%d", digit);
}

class Solution
{
public:
    void print_double(double decimal)
    {
        int n = int(decimal);
        printOut(n);

        print_decimal(ABS(decimal - n));
    }

    void printOut(int n)
    {
        if( n >= 10 || n <= -10)
            printOut(n / 10);
        
        printDigit( ABS(n) % 10);
    }

    void print_decimal(double decimal)
    {
        if(decimal >= 0.1)
        {
            print_double(decimal * 10);
        }
        printDigit(int(decimal * 10));
        
    }
};

int main()
{ 
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-1000.0, 0.0);
    for (int n = 0; n < 10; ++n) {
        double decimal = dis(gen);
        printf("double decimal: %f, print_double: ", decimal);
        Solution solution;
        solution.print_double(decimal);
        printf("\n");
    }
        
}
