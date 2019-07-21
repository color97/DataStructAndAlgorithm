#pragma once

#include <vector>

using namespace std;

template <typename T>
void shellSort( vector<T>& a)
{
    for (size_t gap = a.size() / 2; gap > 0; gap /= 2)
    {
        for(size_t p = gap; p < a.size(); p++)
        {
            T tmp = std::move(a[p]);
            size_t i = p;
            for (; i >= gap && tmp < a[i - gap]; i -= gap)
            {
                a[i] = std::move(a[i - gap]);
            }
            a[i] = std::move(tmp);
        }
    }
    
}
