#include "src/4.trees/codes/4.4.avl_tree.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    AvlTree<int> avlTree;
    vector<int> elements = {3, 2, 1, 4, 5, 6, 7, 16, 15};

    for( int element : elements)
    {
        avlTree.insert(element);
        cout<<"after insert : "<<element<<endl;
        avlTree.printTree();
        cout<<endl;
    }
    return 0;
}