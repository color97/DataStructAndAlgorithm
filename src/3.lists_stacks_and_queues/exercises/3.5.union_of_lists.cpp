#include "src/3.lists_stacks_and_queues/codes/3.5_list.h"
#include <iostream>

template<typename Object>
List<Object> get_union(const List<Object>& l1, const List<Object>& l2)
{
    List<Object> theUnion = l1;
    
    typename List<Object>::const_iterator l2CItr = l2.begin();
    for(typename List<Object>::iterator itr = theUnion.begin(); itr != theUnion.end(); ++itr)
    {
        while (l2CItr != l2.end() && *itr >= *l2CItr)
        {
            theUnion.insert(itr, *l2CItr);
            ++l2CItr;
        }  
    }
    
    while (l2CItr != l2.end())
    {
        theUnion.push_back(*l2CItr);
        ++l2CItr;
    }  

    return theUnion;
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

    List<int> theUnion = get_union(L1, L2);
    std::cout<<"union: ";
    for(auto& x : theUnion)
    {
        std::cout<<x<<", ";
    }
}