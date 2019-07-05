#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class queue
{
public:
    queue(int max):array(max), currentSize(0), front(0), back(0)
    {}

    void enqueue(const T& x)
    {
        if(currentSize < array.size())
        {
            array[back] = x;
            if (++back >= array.size())
            {
                back = 0;
            }
            currentSize++;   
        }  
    }

    T dequeue()
    {
        if(currentSize == 0)
        {
            cout<<"out of bounds\n";
            return T{};
        }

        T x = array[front];
        if (++front >= array.size())
        {
            front = 0;
        }
        currentSize--;
        return x;
    }
private:
    vector<T> array;
    int currentSize;
    int front;
    int back;
};