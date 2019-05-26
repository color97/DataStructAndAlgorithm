#include <vector>

#define NOT_FOUND -1

using namespace std;

template<typename Comparable>
int binarySearch(const vector<Comparable>& a, const Comparable& x)
{
    int low = 0, high = a.size() - 1;
    
    while(low <= high)
    {
        int mid = (low + high) / 2;
        
        if(a[mid] < x)
        {
            low = mid + 1;
        }   
        else if(a[mid] > x)
        {
            high = mid - 1;
        }
        else
        {
            return mid;
        }     
    }

    return NOT_FOUND;
}