#pragma once

#include <algorithm>

template < typename T>
struct Node
{
    bool isLeftThreaded;
    bool isRightThreaded;
    T   data;
    Node*   left;
    Node*   right;

    Node(const T& x, bool pIsLeftThreaded = true, Node* pLeft = nullptr, bool pIsRightThreaded = true, Node* pRight = nullptr)
    : data(x), isLeftThreaded(pIsLeftThreaded), left(pLeft), isRightThreaded(pIsRightThreaded), right(pRight)
    {}
};

template <typename T>
void insert(Node<T>*& t, const T& x)
{
    // 仅在为空树时触发
    if (t == nullptr)
    {
        t = new Node(x);
        //size++;
    }
    else if (x < t->data)
    {
        if (!t->isLeftThreaded)
        {
            insert(t->left, x);
        }
        else
        {
            Node<T>* newNode = new Node(x, true, t->left, true, t);
            t->left = newNode;
            t->isLeftThreaded = false;
            //size++;
        }
    }
    else if ( t->data < x )
    {
        if (!t->isRightThreaded)
        {
            insert(t->right, x)
        }
        else
        {
            t->right = new Node(x, true, t, true, t->right);
            t->isRightThreaded = false;
            //size++;
        }
    }
    // x == t->data
    else
    {
        return;
    }
}


template < typename T>
size_t remove(Node<T>*& t, const T& x)
{
    // 树的最大值节点没有右线索树
    if (t == nullptr)
    {
        return 0;
    }
    else if (x < t->data)
    {
        return t->isLeftThreaded ? 0 : remove(x, t->left);
    }
    else if ( x > t->data)
    {
        return t->isRightThreaded ? 0 : remove(x, t->right);
    }    
    else if ( !(t->isLeftThreaded || t->isLeftThreaded) )
    {
        Node<T>* tmpNode = findMin(t->right);
        t->data = tmpNode->data; 
        return remove(t->right, t->data);
    }
    else
    {
        Node<T>* old = t;
        // 没有孩子的节点，不会被线索链接到
        if (t->isLeftThreaded && t->isRightThreaded)
        {
            Node<T>* prevNode = t->left;
            Node<T>* nextNode = t->right;
            // 没有子节点，则父节点必是前驱节点或后驱节点
            if (nextNode->left == t)
            {
                nextNode->left = prevNode;
                nextNode->isLeftThreaded = true;
            }
            else if(nextNode->right == t)
            {
                nextNode->right = nextNode;
                nextNode->isRightThreaded = true;
            }
        }
        // 有一个右孩子的节点，必然有一个指向当前节点的 left 线索链，并且是右孩子中的最小节点
        else if (t->isLeftThreaded)
        {
            // 右子树的最小节点，没有左子树。其左子树为线索树指向当前节点 t
            Node<T>* tmpNode = findMin(t->right);
            tmpNode->left = t->left;
        }
        // 有一个左孩子的节点，必然有一个指向当前节点的 right 线索链，并且是左孩子的最大节点
        else
        {
            Node<T>* tmpNode = findMax(t->left);
            tmpNode->right = t->right;
        }        
        
        delete old;
        //theSize--;
        return 1;
    }
}