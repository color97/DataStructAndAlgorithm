#include "src/4.trees/exercises/4.16.lazy_deletion_binary_search_tree.h"
#include <iostream>

using namespace std;
int main()
{
    BinarySearchTree<int> bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);
    bst.printTree();

    bst.remove(1);
    bst.printTree();

    bst.remove(2);
    bst.printTree();

    bst.remove(3);
    bst.printTree();
    
    return 0;
}