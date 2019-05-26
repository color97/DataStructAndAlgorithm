#include <vector>
//#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

class Solution
{
public:
    int selection_problem(const vector<int>& numbers, const int k)
    {
        vector<int> kNumbers(k);
        for(int i = 0; i < k; i++)
        {
            kNumbers[i] = numbers[i];
        }
        for (size_t i = 0; i < k; i++)
        {
            for(size_t j = 0; j < k - i - 1; j++)
            {
                if(kNumbers[j] < kNumbers[j+1])
                {
                    std::swap(kNumbers[j], kNumbers[j+1]);
                }
            }
        }
        for (size_t i = k; i < numbers.size(); i++)
        {
            if(kNumbers[k-1] < numbers[i])
            {
                for (vector<int>::iterator itr = kNumbers.begin(); itr < kNumbers.begin() +k; itr++)
                {
                    if(numbers[i] > *itr)
                    {
                        kNumbers.insert(itr, numbers[i]);
                        break;
                    }
                }
                
            }
        }
        return kNumbers[k - 1];
        
    }
};

int main()
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    const vector<int> Narray{10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    for(auto & N: Narray)
    {
        const int k = N / 2;
        vector<int> numbers(N);
        for( auto& number : numbers)
        {
            number = rand();
        }
        Solution solution;
        clock_t timeBegin = clock();
        const int kLargest = solution.selection_problem(numbers, k);
        clock_t timeEnd = clock();
        printf("N = %10d, cost time = %10.2fms, the %10dth largest is %d.\n", N, 1000.0 * (timeEnd - timeBegin)/CLOCKS_PER_SEC, k, kLargest);
        //cout<<"N = "<< N <<"cost time = "<<<<", the "<< k <<"th largest is "<< kLargest << ".\n";
    }
}