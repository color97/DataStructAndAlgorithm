#include <iostream>
#include <vector>

#include "src/7.sorting/exercises/7.25.quick_sort_one_recursive.h"

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
    quickSort(testData);
    cout<< "quickSort: "<<endl;
    printVector(testData);

    return 0;
}