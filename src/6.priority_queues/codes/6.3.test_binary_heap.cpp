#include "src/6.priority_queues/codes/6.3.heap.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> items{13, 21,16, 24, 31, 19, 6, 65, 26, 32};
    BinaryHeap<int> bheap{items};

    bheap.insert(14);
    bheap.deleteMin();

    return 0;
}