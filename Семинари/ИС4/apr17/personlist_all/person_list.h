#ifndef _PERSON_LIST_H_
#define _PERSON_LIST_H_

#include <cstddef>
#include "person.h"

class PersonList
{
    Person * data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

public:
    PersonList(...)
    {

    }

    // ...

    ~PersonList()
    {

    }

    bool append(Person const & person)
    {

    }

    bool erase(size_t idx)
    {

    }

    void read(std::istream & is)
    {

    }

    void write(std::istream & os)
    {

    }
};

std::ostream & operator<<(std::ostream & os, PersonList const & list)
{
    return os;
}

std::istream & operator<<(std::istream & is, PersonList & list)
{
    return is;
}


#endif