#include "src/3.lists_stacks_and_queues/codes/3.5_list.h"
#include <iostream>

template<typename Object>
List<Object> intersection(const List<Object>& l1, const List<Object>& l2)
{
    List<Object> theIntersection;
    
    typename List<Object>::const_iterator l1CItr = l1.begin();
    typename List<Object>::const_iterator l2CItr = l2.begin();
    while(l1CItr != l1.end() && l2CItr != l2.end())
    {
        if (*l1CItr == *l2CItr)
        {
            theIntersection.push_back(*l1CItr);
            l1CItr++;
            l2CItr++;
        }
        else if (*l1CItr < *l2CItr)
        {            
            l1CItr++;
        }
        else
        {   
            l2CItr++;
        }
        
    }

    return theIntersection;
}

int main()
{
    List<int> L1, L2;
    L1.push_back(2);
    L1.push_back(3);
    L1.push_back(5);

    L2.push_back(1);
    L2.push_back(3);
    L2.push_back(7);

    List<int> theIntersection = intersection(L1, L2);
    std::cout<<"intersection: ";
    for(auto& x : theIntersection)
    {
        std::cout<<x<<", ";
    }
}