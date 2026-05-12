#pragma once
#include "Person.h"

class UniversityAggregation
{
public:
    void AddPerson(Person* person);
    void Print() const;

private:
    inline static const int MAX_PEOPLE = 20;
    Person* arr[MAX_PEOPLE]{};
    int cnt = 0;
};
