#include <cstring>
#include <algorithm>
#include <iostream>

template<typename Object>
class Collection
{
public:
    Collection(unsigned int pSize = 0): size(pSize), capacity(pSize)
    {
        calculate_capacity();
        _collection = new Object[capacity];
    }

    ~Collection()
    {
        delete []_collection;
    }

    Collection(const Collection& pOther): size(pOther.size), capacity(pOther.capacity)
    {
        _collection = new Object[capacity];
        std::memcpy(_collection, pOther._collection, size * sizeof(Object));
    }

    Collection(Collection&& pOther): size(pOther.size), capacity(pOther.capacity), _collection(pOther._collection)
    {
        pOther._collection = nullptr;
    }

    Collection& operator= (const Collection& pOther)
    {
        if(this != &pOther)
        {
            size = pOther.size;
            capacity = pOther.capacity;
            delete []_collection;
            _collection = new Object[capacity];
            std::memcpy(_collection, pOther._collection, size * sizeof(Object));
        }
        return *this;
    }

    Collection& operator= (Collection&& pOther)
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
        _collection = new Object[capacity];
    }

    void insert(unsigned int pIndex, const Object& pValue)
    {
        if(pIndex > size) return;

        unsigned int oldSize = size;
        size += 1;
        if(size > capacity)
        {
            calculate_capacity();
            Object* tmpCollection = _collection;
            _collection = new Object[capacity];
            std::memcpy(_collection, tmpCollection, oldSize * sizeof(Object));
            delete []tmpCollection;
        }
        

        for (unsigned int i = size - 1; i > pIndex; i--)
        {
            _collection[i] = _collection[i - 1];
        }
        _collection[pIndex] = pValue;
    }

    void remove(unsigned int pIndex)
    {
        if(pIndex >= size) return;

        for (unsigned int i = pIndex; i < size - 1; i++)
        {
            _collection[i] = _collection[i + 1];
        }
        size--;
    }

    bool contains(const Object& pValue)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            if(_collection[i] == pValue)
            {
                return true;
            }
        }
        return false;
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
    Object* _collection = nullptr;
};

int main()
{
    Collection<int> collection;

    collection.insert(0, 0);
    collection.insert(0, 1);
    collection.insert(0, 1);
    collection.insert(0, 2);
    collection.insert(0, 3);

    std::cout << collection.contains(0) << std::endl;

    collection.remove(4);

    std::cout << collection.contains(0) << std::endl;

    return 0;
}