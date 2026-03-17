#ifndef _PERSON_H_
#define _PERSON_H_

#include "Date.h"

struct Person
{
    char name[30];
    char family[30];
    Date birthDate;
};


#endif