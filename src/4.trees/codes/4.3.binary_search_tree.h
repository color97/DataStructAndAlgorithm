#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree(): root(nullptr) {}
    ~BinarySearchTree()
    {
        makeEmpty();
    }
    BinarySearchTree(const BinarySearchTree& rhs): root{nullptr}
    {
        root = clone(rhs.root);
    }
    BinarySearchTree(BinarySearchTree&& rhs): root{rhs.root}
    {
        rhs.root = nullptr;
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    BinarySearchTree& operator=(BinarySearchTree& rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

    const Comparable& findMin() const
    {
        if(isEmpty())
        {
            throw std::underflow_error("underflow exception");
        }
        return findMin(root)->element;
    }
    const Comparable& findMax() const
    {
        if(isEmpty())
        {
            throw std::underflow_error("underflow exception");
        }
        return findMax(root)->element;
    }
    bool contains(const Comparable& x) const
    {
        return contains(x, root);
    }
    bool isEmpty() const
    {
        return root == nullptr;
    }
    void printTree(ostream& out = cout) const
    {
        printTree(root, cout);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }
    void insert(const Comparable& x)
    {
        insert(x, root);
    }
    void insert(Comparable&& x)
    {
        insert(std::move(x), root);
    }
    void remove(const Comparable& x)
    {
        remove(x, root);
    }

private:
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

private:
    bool contains(const Comparable& x, BinaryNode* t) const
    {
        if (t == nullptr)
        {
            return false;
        }
        else if (x < t->element)
        {
            return contains(x, t->left);
        }
        else if ( x > t->element)
        {
            return contains(x, t->right);
        }
        else
        {
            return true;
        }     
    }
    void printTree(BinaryNode* t, ostream& out) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }
    BinaryNode* findMin(BinaryNode* t) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        else if (t->left == nullptr)
        {
            return t;
        }
        else
        {
            return findMin(t->left);
        }        
    }
    BinaryNode* findMax(BinaryNode* t) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        else if (t->right == nullptr)
        {
            return t;
        }
        else
        {
            return findMin(t->right);
        }  
    }

    void makeEmpty(BinaryNode*& t)
    {
        if (t == nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            
            delete t;
            t = nullptr;    
        }
    }
    void insert(const Comparable& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{x, nullptr, nullptr};
        }
        else if (x < t->element)
        {
            return insert(x, t->left);
        }
        else if ( x > t->element)
        {
            return insert(x, t->right);
        }    
    }
    void insert(Comparable&& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        }
        else if (x < t->element)
        {
            return insert(std::move(x), t->left);
        }
        else if ( x > t->element)
        {
            return insert(std::move(x), t->right);
        }    
    }
    void remove(const Comparable& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            return;
        }
        else if (x < t->element)
        {
            remove(x, t->left);
        }
        else if ( x > t->element)
        {
            remove(x, t->right);
        }    
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode* old = t;
            t = t->left != nullptr ? t->left : t->right;
            delete old;
        }
    }

    BinaryNode* clone(BinaryNode* t) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

private:
    BinaryNode* root;
};

#endif //BINARY_SEARCH_TREE_H