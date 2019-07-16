void insert(const T& x)
{
    if (currentSize + 1 == array.size())
    {
        array.resize(array.size());
    }

    array[0] = x;
    size_t hole = ++currentSize;
    for(; x < array[hole/2]; hole /= 2)
    {
        array[hole] = std::move(array[hole/2]);         
    }
    array[hole] = std::move(array[0]);
}