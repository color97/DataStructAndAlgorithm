 #pragma once

#include <vector>

using namespace std;

template <typename T>
const T& median3(vector<T>& a, int left, int right)
{
    const int center = (left + right) / 2;
    if (a[center] < a[left])
    {
        std::swap(a[left], a[center]);
    }
    if (a[right] < a[left])
    {
        std::swap(a[left], a[right]);
    }
    if (a[right] < a[center])
    {
        std::swap(a[center], a[right]);
    }
    
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

template <typename T>
void insertionSort(vector<T>& a, int left, int right)
{
    for( int p = 1; p < a.size(); p++)
    {
        T tmp = std::move(a[p]);
        int i = p;
        for(; i > 0 && tmp < a[i - 1]; i--)
        {
            a[i] = std::move(a[i - 1]);
        }
        a[i] = std::move(tmp);
    }
}

template <typename T>
void quickSort(vector<T>& a, int left, int right)
{
    if (left + 10 > right)
    {
        insertionSort(a, left, right);
        return;
    }
    
    while(left < right)
    {
        const T& pivot = median3(a, left, right);

        int i = left, j = right - 1;
        for( ; ; )
        {
            while(a[++i] < pivot) { }
            while(pivot < a[--j]) { }
            if (i < j)
            {
                std::swap(a[i], a[j]);
            }
            else
            {
                break;
            }
        }
        std::swap(a[i], a[right - 1]);
        quickSort(a, left, i - 1);
        
        left = i + 1;
    }
}


template <typename T>
void quickSort(vector<T>& a)
{
    quickSort(a, 0, a.size() - 1);
}