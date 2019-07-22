#pragma once

#include <vector>

using namespace std;

template <typename T>
void percolateDown(vector<T>& a, int hole, int n);

template <typename T>
void heapSort(vector<T>& a)
{
    // build heap
    for(int i = a.size() / 2 - 1; i >= 0; i--)
    {
        percolateDown(a, i, a.size());
    }

    // while deleteMax
    for(int j = a.size() - 1; j >= 0; j--)
    {
        std::swap(a[0], a[j]);
        percolateDown(a, 0, j);
    }
}

// https://en.wikipedia.org/wiki/D-ary_heap 
// the item at position 0 of the array (using zero-based numbering) forms the root of the tree, 
// the items at positions 1 through d are its children, the next d^2 items are its grandchildren, etc. 
// Thus, the parent of the item at position i (for any i > 0) is the item at position ⌊(i − 1)/d⌋ 
// and its children are the items at positions di + 1 through di + d. 
inline int getLeftChild(int i)
{
    return i * 2 + 1;
}

template <typename T>
void percolateDown(vector<T>& a, int hole, int n)
{
    T tmp = std::move(a[hole]);

    int child = 0;
    for (; getLeftChild(hole) < n; hole = child)
    {
        child = getLeftChild(hole);

        if (child != n - 1 && a[child] < a[child + 1])
        {
            child++;
        }

        if (tmp < a[child])
        {
            a[hole] = std::move(a[child]);
        }
        else
        {
            break;
        }
        
    }
    a[hole] = std::move(tmp);
}