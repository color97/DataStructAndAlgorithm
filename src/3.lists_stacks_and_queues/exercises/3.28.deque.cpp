#include "src/3.lists_stacks_and_queues/codes/3.5_list.h"

template<typename T>
class deque
{
public:
    deque(): lst{} 
    {}

    void push(const T& x)
    {
        lst.push_back(x);
    }

    T pop()
    {
        T front = lst.front();
        lst.pop_back();
        return front;
    }

    void inject(const T& x)
    {
        lst.push_front(x);
    }

    T eject()
    {
        T endObject = lst.back();
        lst.pop_front();
        return endObject;
    }
private:
    List<T> lst;
};