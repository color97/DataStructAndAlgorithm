#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class queue
{
public:
    queue():currentSize(0)
    {
        tail = new Node;
        tail->next = tail;
    }
    
    ~queue()
    {
        while (theSize > 0)
        {
            dequeue();
        }
    }

    void enqueue(const T& x)
    {
        Node* head = tail->next;
        tail->next = new Node{x, head};
        currentSize++;
        tail = tail->next;
    }

    T dequeue()
    {
        Node* p = *tail->next;
        T tmpData = p->element;
        tail->next = p->next;
        delete p;
        return tmpData;        
    }
private:
    struct Node
    {
        T element;
        Node* next;

        Node(const T& x = T{}, Node* n = nullptr)
            : element{x}, next{n} {}
    };
private:
    Node* tail;
    int currentSize;

};