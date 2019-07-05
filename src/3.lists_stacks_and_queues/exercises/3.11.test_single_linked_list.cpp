#include "src/3.lists_stacks_and_queues/exercises/3.11.single_linked_list.h"
#include <iostream>

using namespace std;

int main()
{
    SingleLinkedList<int> list;

    list.add(1);
    list.print();
    cout<<"list size: "<<list.size()<<endl;

    list.add(2);
    list.print();
    list.remove(3);
    cout<<"list size: "<<list.size()<<endl;
    
    list.add(3);
    list.remove(2);
    cout<<"list size: "<<list.size()<<endl;
}