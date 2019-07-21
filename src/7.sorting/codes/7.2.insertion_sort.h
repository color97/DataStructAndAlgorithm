#pragma once

#include <vector>

using namespace std;

template <typename T>
void insertionSort( vector<T>& a)
{
    for (size_t p = 1; p < a.size(); p++)
    {
        T tmp = std::move(a[p]);
        size_t i = p;
        //for (; i > 0 && tmp <= a[i - 1]; i--)
        for (; i > 0 && tmp < a[i - 1]; i--)
        {
            a[i] = std::move(a[i - 1]);
        }
        a[i] = std::move(tmp);
    }
}

template <typename Iterator, typename Comparator>
void insertionSort( const Iterator& begin, const Iterator& end, const Comparator& lessThan)
{
    if (begin == end)
    {
        return;
    }
    
    for (Iterator p = begin + 1; p != end; ++p)
    {
        auto tmp = std::move(*p);
        Iterator itr = p;
        for(; itr != begin && lessThan(tmp, *(itr - 1)); --itr)
        {
            *itr = std::move(*(itr - 1));
        }
        *itr = std::move(tmp);

    }
}

template <typename Iterator>
void insertionSort( const Iterator& begin, const Iterator& end )
{
    insertionSort(begin, end, less<decltype(*begin)>{ } );
}