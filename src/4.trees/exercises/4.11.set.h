#ifndef SET_H
#define SET_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename Comparable>
class Set
{
private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode* parent;

        BinaryNode(const Comparable& x, BinaryNode* lt, BinaryNode* rt, BinaryNode* prt)
        : element(x), left(lt), right(rt), parent(prt)
        {}
        BinaryNode(Comparable&& x, BinaryNode* lt, BinaryNode* rt, BinaryNode* prt)
        : element(std::move(x)), left(lt), right(rt), parent(prt)
        {}
    };
public:
    class const_iterator
    {
    public:
        const_iterator(): current{nullptr} {}

        const Comparable& operator* () const
        {
            return retrieve();
        }

        const_iterator& operator++ ()
        {
            BinaryNode* t = nullptr;
            if (current->right != nullptr)
            {
                t = current->right;
                // 右子树中的最小值为下一个位置
                while(t->left != nullptr)
                {
                    t = t->left;
                }
                current = t;
            }
            else
            {
                t = current->parent;
                while( t != nullptr && t->element > current->element)
                {
                    t = t->parent;
                }
                current = t;
            }
            
            return *this;
        }

        const_iterator operator++ (int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator-- ()
        {
            BinaryNode* t = nullptr;
            if (current->left != nullptr)
            {
                t = current->left;
                // 左子树中的最大值为下一个位置
                while(t->right != nullptr)
                {
                    t = t->right;
                }
                current = t;
            }
            else
            {
                t = current->parent;
                while( t != nullptr && t->element < current->element)
                {
                    t = t->parent;
                }
                current = t;
            }
            return *this;
        }

        const_iterator operator-- (int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator== (const const_iterator& rhs) const
        {
            return this->current == rhs.current;
        }

        bool operator!= (const const_iterator& rhs) const
        {
            //return !this->operator==(rhs);
            return !(*this == rhs);
        }

    protected:
        friend class Set;

    protected:
        const_iterator(BinaryNode* p): current{p} {}

        Comparable& retrieve() const
        {
            return current->element;
        }

    protected:
        BinaryNode* current;
    };

    class iterator: public const_iterator
    {
    public:
        iterator(): const_iterator{} {}

        Comparable& operator*()
        {
            return const_iterator::retrieve();
        }

        iterator& operator++()
        {
            BinaryNode* t = nullptr;
            if (this->current->right != nullptr)
            {
                t = this->current->right;
                // 右子树中的最小值为下一个位置
                while(t->left != nullptr)
                {
                    t = t->left;
                }
                this->current = t;
            }
            else
            {
                t = this->current->parent;
                // 父节点中大于当前节点值的节点
                while( t != nullptr && t->element < this->current->element)
                {
                    t = t->parent;
                }
                this->current = t;
            }
            
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator-- ()
        {
            BinaryNode* t = nullptr;
            if (this->current->left != nullptr)
            {
                t = this->current->left;
                // 左子树中的最大值为下一个位置
                while(t->right != nullptr)
                {
                    t = t->right;
                }
                this->current = t;
            }
            else
            {
                t = this->current->parent;
                while( t != nullptr && t->element > this->current->element)
                {
                    t = t->parent;
                }
                this->current = t;
            }
            return *this;
        }

        iterator operator-- (int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }
    protected:
        friend class Set;
        iterator(BinaryNode* p) : const_iterator{p} {}
    };

public:
    Set(): root(nullptr) {}
    ~Set()
    {
        makeEmpty();
    }
    // Set(const Set& rhs): root{nullptr}
    // {
    //     //root = clone(rhs.root, nullptr);
    // }
    Set(Set&& rhs): root{rhs.root}
    {
        rhs.root = nullptr;
    }

    Set& operator=(const Set& rhs)
    {
        Set copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    Set& operator=(Set& rhs)
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
        return size == 0;
    }
    void printTree(ostream& out = cout) const
    {
        printTree(root, cout);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }
    iterator insert(const Comparable& x)
    {
        return insert(x, root, nullptr);
    }
    iterator insert(Comparable&& x)
    {
        return insert(std::move(x), root, nullptr);
    }
    size_t remove(const Comparable& x)
    {
        return remove(x, root);
    }

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
            
            size--;
            delete t;
            t = nullptr;    
        }
    }
    iterator insert(const Comparable& x, BinaryNode*& t, BinaryNode* parent)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{x, nullptr, nullptr, parent};
            size++;
            return iterator{t};
        }
        else if (x < t->elements)
        {
            return insert(x, t->left, t);
        }
        else if ( x > t->element)
        {
            return insert(x, t->rightt);
        }
        // 元素已存在，返回迭代器
        else
        {
            return iterator{t};
        }
          
    }
    iterator insert(Comparable&& x, BinaryNode*& t, BinaryNode* prt)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{std::move(x), nullptr, nullptr, prt};
            size++;
            return iterator{t};
        }
        else if (x < t->element)
        {
            return insert(std::move(x), t->left, t);
        }
        else if ( x > t->element)
        {
            return insert(std::move(x), t->right, t);
        }
        else
        {
            return iterator{t};
        }
    }
    size_t remove(const Comparable& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            return 0;
        }
        else if (x < t->element)
        {
            return remove(x, t->left);
        }
        else if ( x > t->element)
        {
            return remove(x, t->right);
        }    
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element; 
            return remove(t->element, t->right);
        }
        else
        {
            BinaryNode* old = t;
            t = t->left != nullptr ? t->left : t->right;
            t->parent = old->parent;
            delete old;
            size--;
            return 1;
        }
    }

    // BinaryNode* clone(BinaryNode* t, BinaryNode* parent) const
    // {
    //     if(t == nullptr)
    //     {
    //         return nullptr;
    //     }
    //     return new BinaryNode{t->element, clone(t->left, ), clone(t->right), parent};
    // }

protected:
    BinaryNode* root;
    int         size;
};
#endif //SET_H