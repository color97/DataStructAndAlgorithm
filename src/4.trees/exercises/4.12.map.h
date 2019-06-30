#ifndef MAP_H
#define MAP_H

#include "src/4.trees/exercises/4.11.set.h"

template <typename KeyType,typename ValueType>
class Map
{
public:
    struct Pair
    {
        KeyType first;
        ValueType second;

        Pair(const KeyType& key = KeyType{}, const ValueType& value = ValueType{} )
            : first{ key }, second{ value } {}

        bool operator<( const Pair& others) const
        {
            return first < others.first;
        }

        bool operator>( const Pair& others) const
        {
            return first > others.first;
        }
    };

    typedef typename Set<Pair>::iterator iterator;
    typedef typename Set<Pair>::const_iterator const_iterator;
public:
    Map() {}

    ValueType& operator[](const KeyType& key)
    {
        iterator itr = theSet.find(Pair{key, ValueType{} });
        if (itr == theSet.end())
        {
            itr = theSet.insert(Pair{key, ValueType{} });
        }
        
        return (*itr).second;
    }

    iterator insert(const Pair& x)
    {
        return theSet.insert(x);
    }

    size_t erase(const KeyType& key)
    {
        return theSet.remove(Pair{key, ValueType{}});
    }
    
    size_t size() const
    {
        return theSet.size();
    }

    const_iterator begin() const
    {
        return theSet.begin();
    }
    iterator begin()
    {
        return theSet.begin();
    }
    const_iterator end() const
    {
        return theSet.end();
    }
    iterator end()
    {
        return theSet.end();
    }

private:
    Set<Pair> theSet;
};

#endif //MAP_H