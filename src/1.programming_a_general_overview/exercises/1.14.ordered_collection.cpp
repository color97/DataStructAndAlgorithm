#include <cstring>
#include <algorithm>
#include <iostream>

template<typename Comparable>
class OrderedCollection
{
public:
    OrderedCollection(unsigned int pSize = 0): size(pSize), capacity(pSize)
    {
        calculate_capacity();
        _collection = new Comparable[capacity];
    }

    ~OrderedCollection()
    {
        delete []_collection;
    }

    OrderedCollection(const OrderedCollection& pOther): size(pOther.size), capacity(pOther.capacity)
    {
        _collection = new Comparable[capacity];
        std::memcpy(_collection, pOther._collection, size * sizeof(Comparable));
    }

    OrderedCollection(OrderedCollection&& pOther): size(pOther.size), capacity(pOther.capacity), _collection(pOther._collection)
    {
        pOther._collection = nullptr;
    }

    OrderedCollection& operator= (const OrderedCollection& pOther)
    {
        if(this != &pOther)
        {
            size = pOther.size;
            capacity = pOther.capacity;
            delete []_collection;
            _collection = new Comparable[capacity];
            std::memcpy(_collection, pOther._collection, size * sizeof(Comparable));
        }
        return *this;
    }

    OrderedCollection& operator= (OrderedCollection&& pOther)
    {
        std::swap(size, pOther.size);
        std::swap(capacity, pOther.capacity);
        std::swap(_collection, pOther._collection);
        return *this;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void makeEmpty()
    {
        delete []_collection;

        size = 0;
        calculate_capacity();
        _collection = new Comparable[capacity];
    }

    void insert(const Comparable& pValue)
    {
        unsigned int oldSize = size;
        size += 1;
        if(size > capacity)
        {
            calculate_capacity();
            Comparable* OrderedtmpCollection = _collection;
            _collection = new Comparable[capacity];
            std::memcpy(_collection, OrderedtmpCollection, oldSize * sizeof(Comparable));
            delete []OrderedtmpCollection;
        }
        
        unsigned int index = oldSize;

        for (unsigned int i = 0; i < oldSize; i++)
        {
            if(_collection[i] >= pValue)
            {
                index = i;
                break;
            }
        }

        for (unsigned int i = oldSize; i > index; i--)
        {
           _collection[i] = _collection[i - 1];
        }
        
        _collection[index] = pValue;
    }

    void remove(const Comparable& pValue)
    {
        unsigned int index = size;
        for (unsigned int i = 0; i < size; i++)
        {
            if(_collection[i] == pValue)
            {
                index = i;
                break;
            }
        }


        if(index >= size) return;

        for (unsigned int i = index; i < size - 1; i++)
        {
            _collection[i] = _collection[i + 1];
        }
        size--;
    }

    Comparable& findMin()
    {
        return *_collection;
    }

    Comparable& findMax()
    {
        return *(_collection + size - 1);
    }


private:
    void calculate_capacity()
    {
        unsigned int increaseNum = 4;
        if(size > increaseNum)
        {
            increaseNum = 3 * size / 8 + 16;
        }
        capacity = increaseNum + size;
    }
    
private:
    unsigned int size = 0;
    unsigned int capacity = 0;
    Comparable* _collection = nullptr;
};

int main()
{
    OrderedCollection<int> collection;

    collection.insert(1);
    collection.insert(1);
    collection.insert(2);
    collection.insert(3);
    collection.insert(5);
    collection.insert(8);

    collection.remove(1);

    
    std::cout << collection.findMin() << std::endl;
    std::cout << collection.findMax() << std::endl;

    return 0;
}