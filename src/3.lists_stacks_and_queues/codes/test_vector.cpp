#include "3.5_vector.h"
#include <iostream>

using namespace std;

int main()
{
    Vector<int> vector1(4);
    vector1[0] = 0;
    vector1[1] = 1;
    vector1[2] = 2;
    vector1[3] = 3;
    vector1.push_back(4);

    Vector<int> vector2 = vector1;

    for(Vector<int>::const_iterator citr = vector2.begin(); citr != vector2.end(); ++citr)
    {
        cout<<*citr<<endl;
    }

    return 0;
}