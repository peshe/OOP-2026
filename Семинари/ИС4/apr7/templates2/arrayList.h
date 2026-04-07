


#include <new>
#include <iostream>


template<typename E>
struct ArrayList
{
    size_t capacity = 0;
    size_t size = 0;
    E* data = nullptr;
};

// ArrayList<int>

template<typename E>
bool arrayListReserve(ArrayList<E> & list, size_t required)
{
    //std::cout << "Reserving memory for " << required << " elements" << std::endl;

    if (required < list.capacity)
    {
        return true;
    }

    E* newData = new(std::nothrow) E[required];
    if (newData == nullptr)
        return false;

    for (size_t k = 0; k < list.size; ++k)
        newData[k] = list.data[k];

    delete[] list.data;
    list.data = newData;
    list.capacity = required;
    return true;

}

template<typename E>
bool arrayListAdd(ArrayList<E>& list, E const & p)
{
    if (list.size + 1 >= list.capacity)
    {
        if (!arrayListReserve(list, list.size*2 + 1))
            return false;
    }

    list.data[list.size] = p;
    list.size++;

    return true;

}

template<typename E>
bool arrayListDelete(ArrayList<E> & list, size_t idx)
{
    if(idx + 1 > list.size)
        return false;

    for(size_t k = idx; k + 1 < list.size; ++k)
    {
        list.data[k] = list.data[k+1];
    }

    list.size--;

    return true;
}


template<typename E>
bool arrayListDestroy(ArrayList<E> & list)
{
    delete[] list.data;
    list.size = 0;
    list.data = nullptr;
    
    return true;
}

template<typename E>
bool arrayListPrint(ArrayList<E> const & list)
{
    for(size_t k = 0; k < list.size; ++k)
    {
        E const & p = list.data[k];
        std::cout << k+1 << "." << p << std::endl;
    }
    return std::cout.good();
}