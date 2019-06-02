#include "3.5_list.h"
#include <iostream>

int main()
{
    List<int> list1;

    list1.push_back(0);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    List<int> list2(list1);

    std::cout << *list1.begin() << std::endl;
    list1.pop_front();
    std::cout << list1.front() << std::endl;

    list1.pop_back();
    std::cout << list1.back() << std::endl;

    std::cout << list1.size() << std::endl;
    std::cout << list2.size() << std::endl;

    return 0;
}