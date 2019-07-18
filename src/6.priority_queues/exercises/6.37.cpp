#include <list>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stack>

using namespace std;

#define CAPATCITY   5

struct Box
{
    list<int> items;
    int       slack;

    Box(): slack(CAPATCITY)
    {}

    bool operator<(const Box& rhs) const
    {
        return slack < rhs.slack;
    }

    bool operator>(const Box& rhs) const
    {
        return  rhs < *this;
    }

    void printBoxInfo() const
    {
        cout<<"items: ";
        for(auto item : items)
        {
            cout<<item << " ";
        }
        cout<<", slack: "<<slack<<endl;
    }

    void putInItem(int item, int weight)
    {
        slack -= weight;
        items.push_back(item);
    }
};

void leastBoxA(const vector<int>& itemWeights)
{
    list<Box> boxes;

    for (size_t i = 0; i < itemWeights.size(); i++)
    {
        auto itr = boxes.begin();
        for( ; itr != boxes.end(); ++itr)
        {
            if (itemWeights[i] <= itr->slack)
            {
                break;
            }
        }

        if (boxes.end() == itr)
        {
            itr = boxes.insert(itr, Box());
        }
        
        itr->putInItem(i, itemWeights[i]);
    }

    cout<< "leastBoxA process over."<<endl;
    for( const auto& box : boxes)
    {
        box.printBoxInfo();
    }
}

void leastBoxB(const vector<int>& itemWeights)
{
    priority_queue<Box> BoxesHeap;

    for (size_t i = 0; i < itemWeights.size(); i++)
    {
        if (BoxesHeap.empty() || BoxesHeap.top().slack < itemWeights[i])
        {
            Box box;
            box.putInItem(i, itemWeights[i]);
            BoxesHeap.push(std::move(box));
        }
        else
        {
            Box box = BoxesHeap.top();
            box.putInItem(i, itemWeights[i]);
            BoxesHeap.pop();
            BoxesHeap.push(std::move(box));
        }
    }
    
    cout<< "leastBoxB process over."<<endl;
    for (; !BoxesHeap.empty(); BoxesHeap.pop())
    {
        BoxesHeap.top().printBoxInfo();
    }
    
}

// template<>
// struct greater<Box>
// {
//     bool operator() (const Box& lhs, const Box& rhs)const
//     {
//         return rhs < lhs;
//     }
// };

void leastBoxC(const vector<int>& itemWeights)
{
    priority_queue<Box, vector<Box>, greater<Box>> BoxesHeap;
    stack<Box> boxStash;
    for (size_t i = 0; i < itemWeights.size(); i++)
    {
        
        for (; !BoxesHeap.empty(); BoxesHeap.pop())
        {
            if (itemWeights[i] <= BoxesHeap.top().slack)
            {
                break;
            }
            boxStash.push(BoxesHeap.top());
        }
        
        if (BoxesHeap.empty())
        {
            Box box;
            box.putInItem(i, itemWeights[i]);
            BoxesHeap.push(std::move(box));
        }
        else
        {
            Box box = BoxesHeap.top();
            box.putInItem(i, itemWeights[i]);
            BoxesHeap.pop();
            BoxesHeap.push(std::move(box));
        }

        // 当栈顶box没有空间时，不再出栈
        while (!boxStash.empty() && boxStash.top().slack > 0)
        {
            BoxesHeap.push(boxStash.top());
            boxStash.pop();
        }
    }

    cout<< "leastBoxC process over."<<endl;
    for (; !boxStash.empty(); boxStash.pop())
    {
        boxStash.top().printBoxInfo();
    }
    for (; !BoxesHeap.empty(); BoxesHeap.pop())
    {
        BoxesHeap.top().printBoxInfo();
    }
}

int main()
{
    vector<int> items{2, 2, 3, 3};

    leastBoxA(items);

    leastBoxB(items);

    leastBoxC(items);

    sort(items.begin(), items.end(), [](int lhs, int rhs){ return lhs > rhs;});

    cout<<"after sort items from great to less."<<endl;
    leastBoxA(items);

    leastBoxB(items);

    leastBoxC(items);



    return 0;
}