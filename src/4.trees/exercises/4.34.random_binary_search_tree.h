#include "src/4.trees/codes/4.3.binary_search_tree.h"

template <typename T>
struct BinaryNode
{
    T element;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(const T& x, BinaryNode* lt, BinaryNode* rt)
    : element(x), left(lt), right(rt)
    {}
    BinaryNode(T&& x, BinaryNode* lt, BinaryNode* rt)
    : element(std::move(x)), left(lt), right(rt)
    {}
};

// O(N)
BinaryNode<int>* randomNBST( int n)
{
    return randomBST(1, n);
}

BinaryNode<int>* randomBST( int lower, int upper)
{
    BinaryNode<int>* t = nullptr;
    if (lower <= upper)
    {
        int randomElement = randInt(lower, upper);
        t = new BinaryNode<int>{randomElement, randomBST(lower, randomElement - 1), randomBST(randomElement + 1, upper)};
    }
    
    return t;
}