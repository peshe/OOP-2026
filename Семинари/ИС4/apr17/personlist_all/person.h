#ifndef _PERSON_H_
#define _PERSON_H_

#include "date.h"

#include <cstddef>


struct Person
{
    char name[30];
    char family[30];
    Date birthDate;
};




#endif