#include <stdexcept>

Object& operator[] (int index) 
{ 
    if (index < 0 || index >= theSize)
    {
        throw std::overflow_error("IteratorOutOfBoundsException");
    }
    
    return objects[index];
}

const Object& operator[] (int index) const 
{
    if (index < 0 || index >= theSize)
    {
        throw std::overflow_error("IteratorOutOfBoundsException");
    }
    
    return objects[index];
}