#include <iostream>

using namespace std;

template<typename T>
class SingleLinkedList
{
public:
    SingleLinkedList() : head(nullptr), theSize(0) 
    {
        head = new Node;
        head->next = nullptr;
    }

    size_t size() const
    {
        return theSize;
    }

    void print(ostream& os = cout) const
    {
        Node* lk = head->next;
        while (lk != nullptr)
        {
            os<<lk->element<<endl;
            lk = lk->next;
        }
    }

    bool contains(const T& x) const
    {
        Node* lk = head->next;
        while (lk != nullptr)
        {
            if (lk->element == x)
            {
                return true;
            }
            
            lk = lk->next;
        }
        return false;
    }

    bool add(const T& x)
    {
        if (! contains(x))
        {
            // 在头结点处插入
            Node* l = head->next;
            head->next = new Node{x, l};
            ++theSize;

            return true;
        }
        return false;
    }

    bool remove(const T& x)
    {
        Node* lk = head->next;
        while (lk != nullptr)
        {
            if (lk->element == x)
            {
                Node* l = lk->next;
                // 删除下一个节点
                if (nullptr != l)
                {
                    lk->element = l->element;
                    lk->next = l->next;
                    delete l;
                }
                else
                {
                    delete lk;
                    lk = nullptr;
                }
                theSize--;

                return true;
            }
            
            lk = lk->next;
        }

        return false;
    }
private:
    struct Node
    {
        T element;
        Node* next;

        Node(const T& x = T{}, Node* nt = nullptr) 
            : element{x}, next{nt} {}
    };

private:
    Node*   head;
    size_t  theSize;
};