#include <vector>
using namespace std;

int maxSubSum4( const vector<int>& a)
{
    int maxSum = 0, thisSum = 0;

    for(int j = 0; j < a.size() - 1; j++)
    {
        thisSum += a[j];

        if(thisSum >= maxSum)
        {
            maxSum = thisSum;
        }
        else if(thisSum < 0)
        {
            thisSum = 0;
        }        
    }
    
    return maxSum;
}