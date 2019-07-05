
template< typename T>
class SingleLinkedStack
{
public:
    SingleLinkedStack() : head{nullptr}, theSize(0) {}

    size_t size()const
    {
        return theSize;
    }

    T top() const
    {
        return head->element;
    }

    void push(const T& x)
    {
        head = new Node{x, head};
        theSize++;
    }

    void pop()
    {
        if (head != nullptr)
        {
            Node* old = head;  
            head = old->next;
            delete old;
            theSize--;
        }
        
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
    Node* head;
    size_t theSize;
};