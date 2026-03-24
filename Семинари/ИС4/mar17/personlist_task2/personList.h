#ifndef _PERSON_LIST_H_
#define _PERSON_LIST_H_


#include "person.h"

#include <cstddef>


// data сочи към динамично заделен масив с размер capacity
// или е nullptr, ако capacity == 0
struct PersonList
{
    size_t size;
    size_t capacity;
    Person * data;
};


// функциите връщат true при успех и false при грешка
bool personListInit(PersonList & list);
bool personListDestroy(PersonList & list);
bool personListAdd(PersonList & list, Person const & p);
bool personListDelete(PersonList & list, size_t idx);


bool personListPrint(PersonList const & list);




#endif