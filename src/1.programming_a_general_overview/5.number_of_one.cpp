#include <iostream>
#include <random>

class Solution
{
public:
    size_t number_of_one(int N)
    {
        if ( 0 == N )
        {
            return 0;
        }
        
        if(N % 2 != 0)
        {
            return number_of_one((N - 1) / 2) + 1;
        }
        else
        {
            return number_of_one( N / 2);
        }        
    }
};

int main()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 10000);
    int N = dis(gen);
    
    Solution solution;
    std::cout<<"N: "<< N <<", number of 1 in N binary: "<<solution.number_of_one(N)<<std::endl;
}