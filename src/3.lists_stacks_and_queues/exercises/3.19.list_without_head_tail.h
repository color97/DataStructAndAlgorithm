#if !defined(LIST_H)
#define LIST_H

#include <algorithm>
#include <stdexcept>

template<typename Object>
class List
{
private:
    struct Node
    {
        Object  data;
        Node*   prev;
        Node*   next;

        Node( const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr)
        : data{d}, prev{p}, next{n} {}

        Node( Object&& d, Node* p = nullptr, Node* n = nullptr)
        : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    class const_iterator
    {
    public:
        const_iterator(): current{nullptr} {}

        const Object& operator* () const
        {
            return retrieve();
        }

        const_iterator& operator++ ()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++ (int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator-- ()
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator-- (int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator== (const const_iterator& rhs) const
        {
            return this->current == rhs.current;
        }

        bool operator!= (const const_iterator& rhs) const
        {
            //return !this->operator==(rhs);
            return !(*this == rhs);
        }

    protected:
        friend class List<Object>;

    protected:
        const_iterator(const List<Object>& list, Node* p): theList{&list}, current{p} {}

        Object& retrieve() const
        {
            return current->data;
        }

        void assertIsValid() const
        {
            if(theList == nullptr)
            {
                throw std::overflow_error("IteratorOutOfBoundsException");
            }
        }

    protected:
        const List<Object>* theList;
        Node* current;
    };

    class iterator: public const_iterator
    {
    public:
        iterator() {}

        Object& operator* ()
        {
            return const_iterator::retrieve();
        }

        // 是否还需要?
        const Object& operator*() const
        {
            return const_iterator::operator*();
        }

        iterator& operator++ ()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++ (int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator-- ()
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- (int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }
    
    protected:
        friend class List<Object>;

    protected:
        iterator(const List<Object>& list, Node* p): const_iterator{list, p} {}
    };

public:
    List()
    {
        init();
    }

    ~List()
    {
        clear();
    }

    List(const List& rhs)
    {
        init();
        for( auto& x : rhs )
        {
            push_back(x);
        }
    }

    List( List&& rhs)
    : theSize{rhs.theSize}, head{rhs.head}
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
    }

    List& operator= (const List& rhs)
    {
        List copy = rhs; // call copy construct
        std::swap(*this, copy); // call move assignment
        return *this;
    }

    List& operator= (List& rhs)
    {
        // call member's move assignment
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);

        return *this;
    }


    iterator begin()
    { return iterator{*this, head}; }
    const_iterator begin() const
    { return const_iterator{*this, head}; }

    iterator end()
    { 
        return iterator{*this, nullptr}; 
    }
    const_iterator end() const
    { 
        return const_iterator{*this, nullptr};
    }

    int size() const
    { return theSize; }
    bool empty() const
    { return size() == 0; }

    void clear()
    {
        while(empty())
        {
            pop_front();
        }
    }

    Object& front()
    { return *begin(); }

    const Object& front() const
    { return *begin(); }

    Object& back()
    { return getLastNode()->element; }

    const Object& back() const
    { return getLastNode()->element; }

    void push_back(const Object& d)
    { insert(end(), d); }

    void push_back(Object&& d)
    { insert(end(), std::move(d)); }

    void push_front(const Object& d)
    { insert(begin(), d); }

    void push_front(Object&& d)
    { insert(begin(), std::move(d)); }

    void pop_back()
    { erase(--end()); }

    void pop_front()
    { erase(begin()); }

    iterator insert(iterator itr, const Object& d)
    {
        itr.assertIsValid();
        if(itr.theList != this)
            throw std::runtime_error("IteratorMismatchExcetion");

        if (empty())
        {
            theSize++;
            return iterator{*this, head = new Node{d, nullptr, nullptr} };
        }
        else 
        {
            if ( itr.current == head )
            {
                theSize++;
                Node* tmpNode = new Node{d, nullptr, head};
                head = tmpNode;
                return iterator{*this, tmpNode};
            }
            else
            {
                theSize++;
                Node* p = itr.current;
                return iterator{*this, p->prev = p->prev->next = new Node{d, p->prev, p} };
            }
            
        }
    }

    iterator insert(iterator itr, Object&& d)
    {
        itr.assertIsValid();
        if(itr.theList != this)
            throw std::runtime_error("IteratorMismatchExcetion");

        if (empty())
        {
            theSize++;
            return iterator{*this, head = new Node{std::move(d), nullptr, nullptr} };
        }
        else 
        {
            if ( itr.current == head )
            {
                theSize++;
                Node* tmpNode = new Node{std::move(d), nullptr, head};
                head = tmpNode;
                return iterator{*this, tmpNode};
            }
            else
            {
                theSize++;
                Node* p = itr.current;
                return iterator{*this, p->prev = p->prev->next = new Node{std::move(d), p->prev, p} };
            }
            
        }
    }

    iterator erase(iterator itr)
    {
        itr.assertIsValid();
        if(itr.theList != this)
            throw std::runtime_error("IteratorMismatchExcetion");

        if (empty())
        {
            end();
        }
        else
        {
            if ( itr.current == head )
            {
                head = head->next;
                Node* p = itr.current;
                delete p;
                theSize--;
                return iterator{*this, head};
            }
            else
            {
                Node* p = itr.current;
                p->next->prev = p->prev;
                p->prev->next = p->next;
                iterator retItr{*this, p->next};
                delete p;
                theSize--;
                return retItr;
            }
        }
    }

    iterator erase(iterator from, iterator to)
    {
        iterator itr = from;
        while (itr != to)
        {
            itr = erase(itr);
        }
        return itr;
    }

private:
    void init()
    {
        theSize = 0;
        head = nullptr;
    }

    Node* getLastNode() const
    {
        if (head == nullptr)
        {
            return head;
        }
        else
        {
            Node* tmpNode = head;
            while (tmpNode->next != nullptr)
            {
                tmpNode = tmpNode->next;
            }
            return tmpNode;
        }
    }

    // Node* getTail() const
    // {
    //     Node* lastNode = getLastNode();
    //     return lastNode != nullptr? lastNode->next : head;
    // }

private:
    Node*   head;
    int     theSize;
};

#endif // LIST_H