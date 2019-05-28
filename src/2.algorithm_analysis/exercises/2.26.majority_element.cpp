#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

bool majority_element(int& majorityElement, const vector<int>& a)
{
    if(a.size() == 0)
    {
        return false;
    }
    else if(a.size() == 1)
    {
        majorityElement = a[0];
        return true;
    }
    
    vector<int> b;
    for (size_t i = 0; i < a.size(); i = i + 2)
    {
        if (a[i] == a[i + 1])
        {
            b.push_back(i);
        }    
    }
    if(!majority_element(majorityElement, b))
    {
        majorityElement = a.back();
        return true;
    }
    return false;
}

int majority_element1(const vector<int>& a)
{
    unordered_map<int, int> elementCount;

    for( auto& element : a)
    {
        if(!elementCount.count(element))
        {
            elementCount.emplace(element, 0);
        }
        elementCount[element]++;
    }

    for( auto& pair : elementCount)
    {
        if (pair.second > a.size() / 2)
        {
            cout<<"majority element: "<<pair.first<<endl;
            return pair.first;
        }
        
    }

    cout<< "majority element not found\n";
    return -1;
}

int main()
{
    vector<int> a = {3, 3, 4, 2, 4, 4, 2, 4, 4};
    int canditate = -1;
    cout<<"existence: "<<majority_element(canditate, a)<<", majority element: "<<canditate<<endl;

    majority_element1(a);
}