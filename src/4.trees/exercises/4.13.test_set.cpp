#include "src/4.trees/exercises/4.13.set.h"
#include <iostream>

int main()
{
    Set<int> set;

    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.printTree();
    set.insert(2);
    set.printTree();
    Set<int>::iterator itr = set.insert(5);
    std::cout<<"*itr: "<<*itr<<endl;
    std::cout<<"*(--itr): "<<*(--itr)<<endl;
    std::cout<<"remove(3): "<<set.remove(3)<<endl;
    set.printTree();

    return 0;
}