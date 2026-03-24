

#include "personList.h"

#include <new>
#include <iostream>

bool personListInit(PersonList & list)
{
    list.size = 0;
    list.capacity = 10;
    list.data = new (std::nothrow) Person[10];
    if(nullptr == list.data)
    {
        list.size = list.capacity = 0;
        return false;
    }
    else 
    {
        return true;
    }
}


bool personListReserve(PersonList & list, size_t reqCapacity)
{
    if(reqCapacity <= list.capacity)
        return true;

    size_t newCapacity = std::max(list.capacity * 2, reqCapacity);
    Person * newData = new(std::nothrow) Person[newCapacity];
    if(newData == nullptr)
        return false;

    for(size_t k = 0; k < list.size; ++k)
        newData[k] = list.data[k];

    delete[] list.data;
    list.data = newData;
    list.capacity = newCapacity;

    return true;
}


bool personListAdd(PersonList & list, Person const & p)
{
    
    personListReserve(list, list.size + 1);

    list.data[list.size] = p;
    list.size++;

    return true;

}


bool personListDelete(PersonList & list, size_t idx)
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



bool personListDestroy(PersonList & list)
{
    delete[] list.data;
    list.data = nullptr;
    list.size = 0;
    list.capacity = 0;
    
    return true;
}



bool personListPrint(PersonList const & list)
{
    for(size_t k = 0; k < list.size; ++k)
    {
        Person const & p = list.data[k];
        std::cout << k+1 << "." << p.name << " " << p.family << " "
                  << p.birthDate.day << "." << p.birthDate.month << "." << p.birthDate.year
                  << std::endl;
    }
    return std::cout.good();
}