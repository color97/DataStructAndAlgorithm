#include <vector>
#include <iostream>
using namespace std;

struct MaxSubSequence
{
public:
    int maxSubSum = 0;
    int left = 0;
    int right = 0;

public:
    MaxSubSequence operator+ (const MaxSubSequence& rhs) const
    {
        MaxSubSequence tmpMaxSubSequence;
        tmpMaxSubSequence.maxSubSum = this->maxSubSum + rhs.maxSubSum;
        tmpMaxSubSequence.left = this->left;
        tmpMaxSubSequence.right = rhs.right;
        return tmpMaxSubSequence;
    }
};

MaxSubSequence maxSubSum1( const vector<int>& a)
{
    MaxSubSequence maxSubSequence;

    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = i; j < a.size(); j++)
        {
            int thisSum = 0;

            for (size_t k = i; k < j; k++)
            {
                thisSum += a[k];
            }
            if (thisSum > maxSubSequence.maxSubSum)
            {
                maxSubSequence.maxSubSum = thisSum;
                maxSubSequence.left = i;
                maxSubSequence.right = j - 1;
            }
        }      
    }
    
    return maxSubSequence;
}

MaxSubSequence maxSubSum2( const vector<int>& a)
{
    MaxSubSequence maxSubSequence;

    for (size_t i = 0; i < a.size(); i++)
    {
        int thisSum = 0;
        for (size_t j = i; j < a.size(); j++)
        {
            thisSum += a[j];

            if (thisSum > maxSubSequence.maxSubSum)
            {
                maxSubSequence.maxSubSum = thisSum;
                maxSubSequence.left = i;
                maxSubSequence.right = j;
            }
        }       
    }
    
    return maxSubSequence;
}


MaxSubSequence maxSubSumRec( const vector<int>& a, int left, int right)
{
    MaxSubSequence maxSubSequence;

    if (left == right)
    {
        maxSubSequence.left = maxSubSequence.right = left;
        maxSubSequence.maxSubSum = a[left] > 0 ? a[left] : 0;
        return maxSubSequence;
    }

    int center = (left + right) / 2;
    MaxSubSequence leftMaxSub = maxSubSumRec(a, left, center);
    MaxSubSequence rightMaxSub = maxSubSumRec(a, center + 1, right);
    maxSubSequence = leftMaxSub.maxSubSum > rightMaxSub.maxSubSum ? leftMaxSub : rightMaxSub;

    MaxSubSequence maxLeftBorderSub;
    maxLeftBorderSub.right = center;
    int maxLeftBorderSubSum = 0;
    for (int i = center; i >= left; i--)
    {
       maxLeftBorderSubSum += a[i];
       if (maxLeftBorderSubSum >= maxLeftBorderSub.maxSubSum)
       {
           maxLeftBorderSub.maxSubSum = maxLeftBorderSubSum;
           maxLeftBorderSub.left = i;
       }     
    }
    
    MaxSubSequence maxRightBorderSub;
    maxRightBorderSub.left = center + 1;
    int maxRightBorderSubSum = 0;
    for (int j = center + 1; j <= right; j++)
    {
       maxRightBorderSubSum += a[j];
       if (maxRightBorderSubSum >= maxRightBorderSub.maxSubSum)
       {
           maxRightBorderSub.maxSubSum = maxRightBorderSubSum;
           maxRightBorderSub.right = j;
       }     
    }

    MaxSubSequence middleMaxSubSequence = maxLeftBorderSub + maxRightBorderSub;
    
    return maxSubSequence.maxSubSum > middleMaxSubSequence.maxSubSum ? maxSubSequence : middleMaxSubSequence;
}

MaxSubSequence maxSubSum3( const vector<int>& a)
{
    return maxSubSumRec(a, 0, a.size() - 1);
}

MaxSubSequence maxSubSum4( const vector<int>& a)
{
    MaxSubSequence maxSubSequence;
    maxSubSequence.maxSubSum = maxSubSequence.left = maxSubSequence.right = 0;
    int thisSum = 0;

    for(int j = 0; j < a.size() - 1; j++)
    {
        thisSum += a[j];

        if(thisSum >= maxSubSequence.maxSubSum)
        {
            maxSubSequence.maxSubSum = thisSum;
            maxSubSequence.right = j;
        }
        else if(thisSum < 0)
        {
            thisSum = 0;
            maxSubSequence.left = j + 1;
        }        
    }
    
    return maxSubSequence;
}

int main()
{
    vector<int> arr = {-2, 11, -4, 13, -5, -2};
    MaxSubSequence maxSubSequence = maxSubSum1(arr);
    cout<< maxSubSequence.maxSubSum<<", left: "<<maxSubSequence.left<<", right: "<<maxSubSequence.right <<endl;
    maxSubSequence = maxSubSum2(arr);
    cout<< maxSubSequence.maxSubSum<<", left: "<<maxSubSequence.left<<", right: "<<maxSubSequence.right <<endl;
    maxSubSequence = maxSubSum3(arr);
    cout<< maxSubSequence.maxSubSum<<", left: "<<maxSubSequence.left<<", right: "<<maxSubSequence.right <<endl;
    maxSubSequence = maxSubSum3(arr);
    cout<< maxSubSequence.maxSubSum<<", left: "<<maxSubSequence.left<<", right: "<<maxSubSequence.right <<endl;
    
}