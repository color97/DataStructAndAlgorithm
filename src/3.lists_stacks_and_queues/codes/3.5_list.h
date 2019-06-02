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

        const_iterator& operator++ (int)
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

        const_iterator& operator-- (int)
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
            if(theList == nullptr || current == nullptr || current == theList->head)
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

        iterator& operator++ (int)
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

        iterator& operator-- (int)
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
        delete head;
        delete tail;
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
    : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
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
        std::swap(tail, rhs.tail);

        return *this;
    }


    iterator begin()
    { return iterator{*this, head->next}; }
    const_iterator begin() const
    { return const_iterator{*this, head->next}; }

    iterator end()
    { return iterator{*this, tail}; }
    const_iterator end() const
    { return const_iterator{*this, tail}; }

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
    { return *--end(); }

    const Object& back() const
    { return *--end(); }

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

        Node* p = itr.current;
        theSize++;
        return iterator{*this, p->prev = p->prev->next = new Node{d, p->prev, p} };
    }

    iterator insert(iterator itr, Object&& d)
    {
        itr.assertIsValid();
        if(itr.theList != this)
            throw std::runtime_error("IteratorMismatchExcetion");

        Node* p = itr.current;
        theSize++;
        return iterator{*this, p->prev = p->prev->next = new Node{std::move(d), p->prev, p} };
    }

    iterator erase(iterator itr)
    {
        itr.assertIsValid();
        if(itr.theList != this)
            throw std::runtime_error("IteratorMismatchExcetion");

        Node* p = itr.current;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        iterator retItr{*this, p->next};
        delete p;
        theSize--;
        return retItr;
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
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
private:
    Node*   head;
    Node*   tail;
    int     theSize;
};

#endif // LIST_H