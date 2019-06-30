#include "src/4.trees/exercises/4.12.map.h"

#include <iostream>
#include <string>

using namespace std;


int main()
{
    Map<string, int> theMap;

    theMap.insert(Map<string, int>::Pair{"Tony", 35});
    theMap.insert(Map<string, int>::Pair{"Steve", 70});

    theMap.erase("Steve");

    cout<<theMap["Tony"]<<endl;
    cout<<theMap["Peter"]<<endl;

    return 0;
}