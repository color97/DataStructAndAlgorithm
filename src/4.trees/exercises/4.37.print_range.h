#include "src/4.trees/codes/4.3.binary_search_tree.h" 
#include <iostream>

using namespace std;

template <typename Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(const Comparable& x, BinaryNode* lt, BinaryNode* rt)
    : element(x), left(lt), right(rt)
    {}
    BinaryNode(Comparable&& x, BinaryNode* lt, BinaryNode* rt)
    : element(std::move(x)), left(lt), right(rt)
    {}
};

template <typename T>
void printRange(const BinaryNode<T>* t, const T& k1, const T& k2)
{
    if (t == nullptr)
    {
        return;
    }
    else if ( t->element < k1)
    {
        printRange(t->right, k1, k2);
    }
    else if ( k1 <= t->element && t->element <= k2)
    {
        printRange(t->left, k1, k2);
        cout<<t->element<<endl;
        printRange(t->right, k1, k2);
    }
    else
    {
        printRange(t->left, k1, k2);
    }
    
}

