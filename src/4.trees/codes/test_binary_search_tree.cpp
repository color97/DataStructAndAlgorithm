#include "4.3.binary_search_tree.h"

int main()
{
    BinarySearchTree<int> bst1;
    bst1.insert(3);
    bst1.insert(2);
    bst1.insert(1);

    bst1.printTree();

    BinarySearchTree<int> bst2 = bst1;
    bst2.insert(6);
    bst2.insert(7);
    bst2.insert(8);
    bst2.remove(6);

    bst2.printTree();

    return 0;
}