#include <vector>

using namespace std;

class Solution
{
public:
    int selection_problem(const vector<int>& numbers, const int k)
    {
        vector<int> tmpNumbers(k);
        for(int i = 0; i < k; i++)
        {
            tmpNumbers[i] = numbers[i];
        }
        for (size_t i = 0; i < k; i++)
        {
            for(size_t j = 0; j < k - i - 1; j++)
            {
                if(tmpNumbers[j] < tmpNumbers[j+1])
                {
                    std::swap(tmpNumbers[j] < tmpNumbers[j+1]);
                }
            }
        }
        for (size_t i = k; i < numbers.size(); i++)
        {
            if(tmpNumbers[k-1] < numbers[i])
            {
                for (size_t j = 0; j < k; j++)
                {
                    if(numbers[i] > tmpNumbers[j])
                    {
                        tmpNumbers.insert(j, numbers[i]);
                    }
                }
                
            }
        }
        
        
    }
};

int main()
{

}