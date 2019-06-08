template<typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x)
{
    for(Iterator itr = start; itr != end; ++itr)
    {
        if (x == *itr)
        {
            return itr;
        }
    }
    return end;
}