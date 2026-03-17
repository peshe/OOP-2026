#indef _PERSON_LIST_H_
#define _PERSON_LIST_H_


#include "person.h"

#include <cstding>

struct PersonList
{
    size_t size;
    Person * data;
};z


bool personListInit(PersonList & list);
bool personListDestroy(PersonList & list);
bool personListAdd(PersonList & list, Person const & p);
bool personListDelete(PersonList & list, size_t idx);

bool personListPrint(PersonList const & list);




#endif