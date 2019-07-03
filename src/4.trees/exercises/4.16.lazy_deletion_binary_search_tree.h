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
    BinarySearchTree(): root(nullptr), theSize(0), deletedSize(0) {}
    ~BinarySearchTree()
    {
        makeEmpty();
    }
    BinarySearchTree(const BinarySearchTree& rhs): root{nullptr}, deletedSize{rhs.deletedSize}, theSize{rhs.theSize}
    {
        root = clone(rhs.root);
    }
    BinarySearchTree(BinarySearchTree&& rhs): root{rhs.root}, deletedSize{rhs.deletedSize}, theSize{rhs.theSize}
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
        std::swap(deletedSize, rhs.deletedSize);
        std::swap(theSize, rhs.theSize);

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
        //remove(x, root);
        lazyDelete(x, root);
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;
        bool       isDeleted;

        BinaryNode(const Comparable& x, BinaryNode* lt, BinaryNode* rt)
        : element(x), left(lt), right(rt), isDeleted(false)
        {}
        BinaryNode(Comparable&& x, BinaryNode* lt, BinaryNode* rt)
        : element(std::move(x)), left(lt), right(rt), isDeleted(false)
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
        else if (!t->isDeleted)
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
            
            if (t->isDeleted)
            {
                deletedSize--;
            }
            else
            {
                theSize--;
            }
            
            delete t;
            t = nullptr;    
        }
    }
    void insert(const Comparable& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            theSize++;
            t = new BinaryNode{x, nullptr, nullptr};
        }
        else if (x < t->element)
        {
            insert(x, t->left);
        }
        else if ( x > t->element)
        {
            insert(x, t->right);
        }
        else if (t->isDeleted)
        {
            theSize++;
            t->isDeleted = false;
        }
          
    }
    void insert(Comparable&& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            theSize++;
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        }
        else if (x < t->element)
        {
            insert(std::move(x), t->left);
        }
        else if ( x > t->element)
        {
            insert(std::move(x), t->right);
        }
        else if (t->isDeleted)
        {
            theSize++;
            t->isDeleted = false;
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

    void lazyDelete(const Comparable& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            return;
        }
        else if (x < t->element)
        {
            lazyDelete(x, t->left);
        }
        else if ( x > t->element)
        {
            lazyDelete(x, t->right);
        }
        else
        {
            theSize--;
            deletedSize++;
            // lazy deletion
            t->isDeleted = true;

            // when unDelete node's number equals to deleted node's number
            // clean all deleted nodes
            if (theSize <= deletedSize)
            {
                cleanLazyDeleted(root);
            }
            
        }  
    }

    void cleanLazyDeleted(BinaryNode*& t)
    {
        if (t == nullptr)
        {
            return;
        }
        else 
        {
            cleanLazyDeleted(t->left);
            cleanLazyDeleted(t->right);

            if (t->isDeleted)
            {
                deletedSize--;
                remove(t->element, t);
            }   
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
    // 标记删除的节点数
    size_t  deletedSize;
    // 未标记删除的节点数
    size_t  theSize;
};

#endif //BINARY_SEARCH_TREE_H