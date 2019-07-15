#if !defined(BINOMIAL_QUEUE_H)
#define BINOMIAL_QUEUE_H

#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class BinomialQueue
{
public:
    BinomialQueue() : theTrees(DEFAULT_TREES), currentSize(0)
    {
        for (auto& tree : theTrees)
        {
            tree = nullptr;
        }
    }

    BinomialQueue( const T & item ) : theTrees( 1 ), currentSize{ 1 }
      { theTrees[ 0 ] = new BinomialNode{ item, nullptr, nullptr }; }
    
    ~BinomialQueue()
    {
        makeEmpty();
    }
    BinomialQueue( const BinomialQueue & rhs )
      : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
    { 
        for( int i = 0; i < rhs.theTrees.size( ); ++i )
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
    }

    BinomialQueue( BinomialQueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    { 
    }
    
    /**
     * Deep copy.
     */
    BinomialQueue & operator=( const BinomialQueue & rhs )
    {
        BinomialQueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    BinomialQueue & operator=( BinomialQueue && rhs )
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
        
        return *this;
    }

    bool isEmpty() const
    {
        return 0 == currentSize;
    }
    const T& findMin() const
    {
        if (isEmpty())
        {
            throw underflow_error("BinomialQueue under flow");
        }
        
        return theTrees[findMinIndex()]->element;
    }

    void insert(const T& x)
    {
        BinomialQueue newBQ(x);
        merge(newBQ);
    }
    void deleteMin()
    {
        T x;
        deleteMin(x);
    }
    void deleteMin(T& x)
    {
        if (isEmpty())
        {
            throw underflow_error("BinomialQueue under flow");
        }

        const int minIndex = findMinIndex();
        x = theTrees[minIndex]->element;

        // 构建 H''
        BinomialQueue deletedQueue;
        // 书上是 deletedQueue.theTrees.resize( minIndex + 1 );，但我认为不准确
        deletedQueue.theTrees.resize( minIndex );
        deletedQueue.currentSize = (1 << minIndex) - 1;

        BinomialNode* deletedTree = theTrees[minIndex]->leftChild;
        for (size_t i = deletedQueue.theTrees.size() - 1; i >= 0; i--)
        {
            deletedQueue.theTrees[i] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[i]->nextSibling = nullptr;
        }
        
        // 构建 H'
        delete theTrees[minIndex]; // 释放最小项
        theTrees[minIndex] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge(deletedQueue);
    }

    void merge(BinomialQueue& rhs)
    {
        if (&rhs == this)
        {
            return;
        }

        currentSize += rhs.currentSize;

        if (currentSize > capacity())
        {
            const size_t oldTreeNum = theTrees.size();
            const size_t newTreeNum = max(theTrees.size(), rhs.theTrees.size()) + 1;
            theTrees.resize(newTreeNum);
            for (size_t i = oldTreeNum; i < newTreeNum; i++)
            {
                theTrees[i] = nullptr;
            }
        }
        
        BinomialNode* carry = nullptr;
        for( int i = 0, j = 1; j <= currentSize; i++, j *= 2)
        {
            BinomialNode* t1 = theTrees[i];
            BinomialNode* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;

            switch (whichCase)
            {
            case 0:
                // use case 1;
                //break;
            case 1:
                // 原本就是 t1
                //theTrees[i] = t1;
                break;
            case 2:
                theTrees[i] = t2;
                break;
            case 3:
                carry = combineTrees(t1, t2);
                theTrees[i] = nullptr;
                break;
            case 4:
                theTrees[i] = carry;
                carry = nullptr;
                break;
            case 5:
                carry = combineTrees(t1, carry);
                theTrees[i] = nullptr;
                break;
            case 6:
                carry = combineTrees(t2, carry);
                theTrees[i] = nullptr;
                break;
            case 7:
                theTrees[i] = carry;
                carry = combineTrees(t1, t2);
                break;
            }
        }

        rhs.theTrees.clear();
        rhs.currentSize = 0;
    }
    void makeEmpty()
    {
        for (auto& tree : theTrees)
        {
            makeEmpty(tree);
        }
    }
private:
    struct BinomialNode
    {
        T element;
        BinomialNode* leftChild;
        BinomialNode* nextSibling;

        BinomialNode(const T& x, BinomialNode* lt = nullptr, BinomialNode* nt = nullptr)
        : element(x), leftChild(lt), nextSibling(nt)
        {}
    };

private:
    int findMinIndex() const
    {
        int i;
        int minIndex;

        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        for( minIndex = i; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr &&
                theTrees[ i ]->element < theTrees[ minIndex ]->element )
                minIndex = i;

        return minIndex;
    }
    int capacity() const
    {
       return (1 << theTrees.size()) - 1;
    }

    BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2) const
    {
        if (t2->element < t1->element)
        {
            return combineTrees(t2, t1);
        }
        else
        {
            t2->nextSibling = t1->leftChild;
            t1->leftChild = t2;
            return t1;
        }
    }

    void makeEmpty(BinomialNode*& t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->leftChild);
            makeEmpty(t->nextSibling);
            delete t;
            t = nullptr;
        } 
    }

    BinomialNode* clone(BinomialNode* t) const
    {
        if( t == nullptr )
            return nullptr;

        return new BinomialNode(t->element, clone(t->leftChild), clone(t->nextSibling));
    }

private:
    const static int DEFAULT_TREES = 1;

    vector<BinomialNode*> theTrees;
    int currentSize;
};


#endif // BINOMIAL_QUEUE_H
