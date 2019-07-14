#if !defined(LEFTIST_HEAP_H)
#define LEFTIST_HEAP_H

#include <stdexcept>
#include <algorithm>

using namespace std;

template <typename T>
class LeftistHeap
{
public:
    LeftistHeap(): root(nullptr) {}

    LeftistHeap( const LeftistHeap & rhs ) : root{ nullptr }
    {   
        root = clone( rhs.root );
    }

    ~LeftistHeap( )
    {
        makeEmpty( ); 
    }

    LeftistHeap & operator=( const LeftistHeap & rhs )
    {
        LeftistHeap copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    LeftistHeap & operator=( LeftistHeap && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }

    bool isEmpty() const
    {
        return nullptr == root;
    }
    const T& findMin() const
    {
        if (isEmpty())
        {
            throw underflow_error("LeftistHeap UnderFlow");
        }

        return root->element;
    }

    void insert(const T& x)
    {
        root = merge(new LeftistNode(x), root);
    }
    void deleteMin()
    {
        if (isEmpty())
        {
            throw underflow_error("LeftistHeap UnderFlow");
        }
        
        LeftistNode* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }
    void deleteMin(T& minItem)
    {
        minItem = findMin();
        deleteMin();
    }
    void makeEmpty()
    {
        reclainmMemory(root);
        root = nullptr;
    }
    void merge(LeftistHeap& rhs)
    {
        // 根据地址判断是否是别名
        if (this == &rhs)
        {
            return;
        }
        
        merge(root, rhs.root);
        rhs.root = nullptr;
    }

private:
    struct LeftistNode
    {
        T   element;
        LeftistNode*    left;
        LeftistNode*    right;
        // null path length
        int             npl;

        LeftistNode(const T& x, LeftistNode* lt = nullptr, LeftistNode* rt = nullptr, int nl = 0)
        : element(x), left(lt), right(rt), npl(nl)
        {}

        LeftistNode(T&& x,  LeftistNode* lt = nullptr, LeftistNode* rt = nullptr, int nl = 0)
        : element(std::move(x)), left(lt), right(rt), npl(nl)
        {}
    };

private:
    LeftistNode* merge(LeftistNode* h1, LeftistNode* h2)
    {
        if (h1 == nullptr)
        {
            return h2;
        }
        if (h2 == nullptr)
        {
            return h1;
        }
        if (h1->npl < h2->npl)
        {
            return merge1(h1, h2);
        }
        else
        {
            return merge1(h2, h1);
        }
        
    }
    LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2)
    {
        if (h1->left == nullptr)
        {
            h1->left = h2;
        }
        else
        {
            h1->right = merge(h1->right, h2);
            if (h1->left->npl < h1->right->npl)
            {
                swapChildren(h1);
            }
            h1->npl = h1->right->npl + 1;
        }

        return h1;  
    }

    void swapChildren(LeftistNode* t)
    {
        std::swap(t->left, t->right);
    }
    LeftistNode* clone(LeftistNode* t) const
    {
        return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
    }
    void reclainmMemory(LeftistNode* t)
    {
        if (nullptr != t)
        {
            reclainmMemory(t->left);
            reclainmMemory(t->right);
            delete t;
        }
    }

private:
    LeftistNode* root;
};

#endif // LEFTIST_HEAP_H
