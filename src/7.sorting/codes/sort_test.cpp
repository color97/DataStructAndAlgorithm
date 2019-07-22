#include <iostream>
#include <vector>

#include "src/7.sorting/codes/7.2.insertion_sort.h"
#include "src/7.sorting/codes/7.4.shell_sort.h"
#include "src/7.sorting/codes/7.5.heap_sort.h"
#include "src/7.sorting/codes/7.6.merge_sort.h"

using namespace std;

template <typename T>
void printVector(const vector<T>& a)
{
    for(auto& element : a)
    {
        cout<<element<<", ";
    }
    cout<<endl;
}

int main()
{
    const vector<int> originData = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15 };
    cout<< "origin: "<<endl;
    printVector(originData);

    auto testData = originData;
    insertionSort(testData);
    cout<< "insertionSort: "<<endl;
    printVector(testData);

    testData = originData;
    insertionSort(testData.begin(), testData.end());
    cout<< "insertionSort: "<<endl;
    printVector(testData);

    testData = originData;
    shellSort(testData);
    cout<< "shellSort: "<<endl;
    printVector(testData);

    
    testData = originData;
    heapSort(testData);
    cout<< "heapSort: "<<endl;
    printVector(testData);

    testData = originData;
    mergeSort(testData);
    cout<< "mergeSort: "<<endl;
    printVector(testData);

    return 0;
}