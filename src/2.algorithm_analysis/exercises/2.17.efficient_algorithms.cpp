#include <vector>
#include <iostream>
using namespace std;

int minSubSum( const vector<int>& a)
{
    int minSum = 0, thisSum = 0;

    for(int j = 0; j < a.size() - 1; j++)
    {
        thisSum += a[j];

        if(thisSum <= minSum)
        {
            minSum = thisSum;
        }
        else if(thisSum > 0)
        {
            thisSum = 0;
        }
    }
        
    return minSum;
}

int minPositiveSubSum( const vector<int>& a)
{
    //Todo
    return 0;
}

int main()
{
    vector<int> arr = {-2, 11, -4, 13, -5, -2};
    cout<< minSubSum(arr)<<endl;
    //cout<< minPositiveSubSum(arr)<<endl;
}