#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename Comparable>
class AvlTree
{
public:
    AvlTree(): root(nullptr) {}
    ~AvlTree()
    {
        makeEmpty();
    }
    AvlTree(const AvlTree& rhs): root{nullptr}
    {
        root = clone(rhs.root);
    }
    AvlTree(AvlTree&& rhs): root{rhs.root}
    {
        rhs.root = nullptr;
    }

    AvlTree& operator=(const AvlTree& rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    AvlTree& operator=(AvlTree& rhs)
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
    struct AvlNode
    {
        Comparable  element;
        AvlNode*    left;
        AvlNode*    right;
        int         height;

        AvlNode(const Comparable& x, AvlNode* lt, AvlNode* rt, int h = 0)
        : element(x), left(lt), right(rt), height(h)
        {}
        AvlNode(Comparable&& x, AvlNode* lt, AvlNode* rt, int h = 0)
        : element(std::move(x)), left(lt), right(rt), height(h)
        {}
    };

private:
    bool contains(const Comparable& x, AvlNode* t) const
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
    void printTree(AvlNode* t, ostream& out) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out <<"element: " << t->element << ", height: " << t->height << endl;
            printTree( t->right, out );
        }
    }
    AvlNode* findMin(AvlNode* t) const
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
    AvlNode* findMax(AvlNode* t) const
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
    int height(AvlNode* t) const
    {
        return (t == nullptr) ? -1 : t->height;
    }

    void makeEmpty(AvlNode*& t)
    {
        if (t == nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            
            delete t;
            t = nullptr;    
        }
    }
    void insert(const Comparable& x, AvlNode*& t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr};
        }
        else if (x < t->element)
        {
            insert(x, t->left);
        }
        else if ( x > t->element)
        {
            insert(x, t->right);
        }
        balance(t);
    }
    void insert(Comparable&& x, AvlNode*& t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{std::move(x), nullptr, nullptr};
        }
        else if (x < t->element)
        {
            insert(std::move(x), t->left);
        }
        else if ( x > t->element)
        {
            insert(std::move(x), t->right);
        }   
        balance(t); 
    }
    void remove(const Comparable& x, AvlNode*& t)
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
            AvlNode* old = t;
            t = t->left != nullptr ? t->left : t->right;
            delete old;
        }
        balance(t);
    }

    AvlNode* clone(AvlNode* t) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    void balance(AvlNode*& t)
    {
        if(nullptr == t)
        {
            return;
        }
        else if (height(t->left) - height(t->right) > ALLOWED_BALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
            {
                rotateWithLeftChild(t);
            }
            else
            {
                doubleWithLeftChild(t);
            }
        }
        else if (height(t->right) - height(t->left) > ALLOWED_BALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
            {
                rotateWithRightChild(t);
            }
            else
            {
                doubleWithRightChild(t);
            }  
        }
        
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void rotateWithLeftChild(AvlNode*& k2)
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1; //set root ptr to new root
    }

    void rotateWithRightChild(AvlNode*& k1)
    {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(k1->height, height(k2->right)) + 1;
        k1 = k2; //set root ptr to new root
    }

    void doubleWithLeftChild(AvlNode*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode*& k3)
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

private:
    AvlNode* root;
    static const int ALLOWED_BALANCE = 1;
};

#endif //AVL_TREE_H