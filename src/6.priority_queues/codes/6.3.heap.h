#if !defined(HEAP_H)
#define HEAP_H

#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class BinaryHeap
{
public:
    explicit BinaryHeap(const vector<T>& items)
    : array(items.size() + 10), currentSize(items.size())
    {
        for (size_t i = 0; i < items.size(); i++)
        {
            array[i + 1] = items[i];
        }
        buildHeap();
    }

    void insert(const T& x)
    {
        if (currentSize + 1 == array.size())
        {
            array.resize(array.size());
        }

        array[0] = x;
        size_t hole = ++currentSize;
        for(; x < array[hole/2]; hole /= 2)
        {
            array[hole] = std::move(array[hole/2]);         
        }
        array[hole] = std::move(array[0]);
    }

    void deleteMin()
    {
        array[1] = std::move(array[currentSize--]);

        percolateDown(1);
    }

    void deleteMin(const T& minItem)
    {
        minItem = std::move(array[1]);

        array[1] = std::move(array[currentSize--]);

        percolateDown(1);
    }
private:
    void percolateDown(size_t hole)
    {
        size_t child;
        T tmp = std::move(array[hole]);

        for(; 2 * hole <= currentSize; hole = child)
        {
            child = 2 * hole;
            if (child != currentSize && array[child + 1] < array[child])
            {
                child++;
            }

            if (array[child] < tmp)
            {
                array[hole] = std::move(array[child]);
            }
            else
            {
                break;
            }
        }

        array[hole] = std::move(tmp);
    }

    void buildHeap()
    {
        for (size_t i = currentSize / 2; i >= 1; i--)
        {
            percolateDown(i);
        }
    }
private:
    size_t      currentSize;
    vector<T>   array;
};


#endif // HEAP_H
