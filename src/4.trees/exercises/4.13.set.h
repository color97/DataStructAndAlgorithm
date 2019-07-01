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
        // 类似双向链表，维护了一个从小到大的链
        // nextSmaller means next largest that is smaller than this node
        BinaryNode* nextSmaller;
        // nextLarger means next smallest that is larger than this node
        BinaryNode* nextLarger;

        BinaryNode(const Comparable& x = Comparable{}, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr, BinaryNode* ns = nullptr, BinaryNode* nl = nullptr)
        : element(x), left(lt), right(rt), nextSmaller(ns), nextLarger(nl)
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
            current = current->nextLarger;
            
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
            current = current->nextSmaller;
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
            this->current = this->current->nextLarger;
            
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
            this->current = this->current->nextSmaller;
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
    Set(): root(nullptr)
    {
        init();
    }
    ~Set()
    {
        makeEmpty();
        delete head;
        delete tail;
    }
    // Set(const Set& rhs): root{nullptr}
    // {
    //     //root = clone(rhs.root, nullptr);
    // }
    Set(Set&& rhs): root{rhs.root}
    {
        rhs.root = nullptr;
    }

    // Set& operator=(const Set& rhs)
    // {
    //     Set copy = rhs;
    //     std::swap(*this, copy);
    //     return *this;
    // }
    // Set& operator=(Set& rhs)
    // {
    //     std::swap(root, rhs.root);
    //     return *this;
    // }

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
        return theSize == 0;
    }
    size_t size() const
    {
        return theSize;
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
    size_t remove(const Comparable& x)
    {
        return remove(x, root);
    }

    iterator find(const Comparable& x)
    {
        return find(x, root);
    }

    const_iterator begin() const
    {
        return const_iterator{ head };
    }
    iterator begin()
    {
        return iterator{ head };
    }

    iterator end()
    {
        return iterator{ tail };
    }
    const_iterator end() const
    {
        return const_iterator{ tail };
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
            
            theSize--;
            delete t;
            t = nullptr;    
        }
    }
    iterator insert(const Comparable& x, BinaryNode*& t, BinaryNode* parent)
    {
        if (t == nullptr)
        {
            theSize++;
            t = new BinaryNode{x, nullptr, nullptr};

            // 父节点为空，该节点为根节点，链接head，tail
            if (parent == nullptr)
            {
                head->nextLarger = t;
                t->nextSmaller = head;
                t->nextLarger = tail;
                tail->nextSmaller = t;
            }
            // 父节点不为空
            else
            {
                // t 为父节点的左儿子，则 t 大小在父节点及父节点的 smaller 节点之间
                if (t->element < parent->element)
                {
                    t->nextLarger = parent;
                    t->nextSmaller = parent->nextSmaller;
                    //if (parent->nextSmaller != nullptr)
                    {
                        parent->nextSmaller->nextLarger = t;
                    }
                    parent->nextSmaller = t;     
                }
                // t 为父节点的右儿子，则 t 大小在父节点及父节点的 larger  节点之间
                else
                {
                    t->nextSmaller = parent;
                    t->nextLarger = parent->nextLarger;
                    // if (parent->nextLarger != nullptr)
                    {
                        parent->nextLarger->nextSmaller = t;
                    }
                    parent->nextLarger = t;
                }  
            }
            
            return iterator{t};
        }
        else if (x < t->element)
        {
            return insert(x, t->left, t);
        }
        else if ( x > t->element)
        {
            return insert(x, t->right, t);
        }
        // 元素已存在，返回迭代器
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
            // 其实右子树的最小值 tmpNode == t->nextSmaller
            // 故并不会影响 smaller 和 larger 的指向
            BinaryNode* tmpNode = findMin(t->right);
            t->element = tmpNode->element; 
            return remove(t->element, t->right);
        }
        else
        {
            BinaryNode* old = t;
            t = t->left != nullptr ? t->left : t->right;

            // 类似双向链表，重新链接被删除节点的前后节点
            old->nextSmaller->nextLarger = old->nextLarger;
            old->nextLarger->nextSmaller = old->nextSmaller;
            
            delete old;
            theSize--;
            return 1;
        }
    }

    iterator find(const Comparable& x, BinaryNode* t)
    {
        if (t == nullptr)
        {
            return end();
        }
        else if (x < t->element)
        {
            return find(x, t->left);
        }
        else if ( x > t->element)
        {
            return find(x, t->right);
        }
        else
        {
            return iterator{t};
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

    void init()
    {
        theSize = 0;
        head = new BinaryNode;
        tail = new BinaryNode;
        head->nextSmaller = tail;
        tail->nextLarger = head;
    }

protected:
    int         theSize;
    BinaryNode* root;
    BinaryNode* head;
    BinaryNode* tail;
};
#endif //SET_H