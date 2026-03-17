

#include "personList.h"


bool personListInit(PersonList & list)
{
    list.size = 0;
    list.data = nullptr;
}


bool personListAdd(PersonList & list, Person const & p)
{
    Person * newData = new(std::nothrow) Person[p.size + 1];
    if(newData == nullptr)
        return false;

    for(size_t k = 0; k < <list.size; ++k)
        newData[k] = list.data[k];

    newData[size] = p;

    delete[] list.data;

    list.size++;
    list.data = newData;


    return true;

}


bool personListDelete(PersonList & list, size_t idx)
{
    if(idx + 1 > list.size)
        return false;

    for(size_t k = idx; k + 1 < list.size; ++k)
    {
        list.data[k] = list.data[k+1]
    }

    list.size--;

    return true;
}



bool personListDestroy(PersonList & list)
{
    delete[] list.data;
    list.size = 0;
}



bool personListPrint(PersonList const & list)
{
    for(size_t k = 0; k < list.size; ++k)
    {
        Person const & p = list.data[k];
        std::cout << p.name << " " << p.family << " " << p.birthDate.year << " " 
                  << p.birthDate.month << " " << p.birthDate.day  << std::endl;
    }
    return std::cout.good();
}