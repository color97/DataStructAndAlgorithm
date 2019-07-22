#pragma once

#include <vector>

using namespace std;

template <typename T>
void mergeSort(vector<T>& a, vector<T>& tmpArray, int left, int right);

template <typename T>
void mergeSort(vector<T>& a)
{
    vector<T> tmpArray(a.size());
    mergeSort(a, tmpArray, 0, a.size() - 1);
}


template <typename T>
void merge(vector<T>& a, vector<T>& tmpArray, int leftPos, int rightPos, int rightEnd);

template <typename T>
void mergeSort(vector<T>& a, vector<T>& tmpArray, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    const int center = (left + right) / 2;
    mergeSort(a, tmpArray, left, center);
    mergeSort(a, tmpArray, center + 1, right);
    merge(a, tmpArray, left, center + 1, right);
}


template <typename T>
void merge(vector<T>& a, vector<T>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
    const int numElements = rightEnd - leftPos + 1;

    const int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    while (leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if (a[leftPos] <= a[rightPos])
        {
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        }
        else
        {
            tmpArray[tmpPos++] = std::move(a[rightPos++]);
        }
    }
    
    while (leftPos <= leftEnd)
    {
        tmpArray[tmpPos++] = std::move(a[leftPos++]);
    }

    while (rightPos <= rightEnd)
    {
        tmpArray[tmpPos++] = std::move(a[rightPos++]);
    }

    // 将 tmpArray 复制回原数组 a
    for (size_t i = (rightEnd - numElements + 1); i  < numElements; ++i)
    {
        a[i] = std::move(tmpArray[i]);
    }
}