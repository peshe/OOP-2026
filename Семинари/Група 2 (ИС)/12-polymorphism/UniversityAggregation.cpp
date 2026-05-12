#include <iostream>

#include "UniversityAggregation.h"

void UniversityAggregation::AddPerson(Person* person)
{
    arr[cnt++] = person;
}

void UniversityAggregation::Print() const
{
    for (int i = 0; i < cnt; ++i)
    {
        arr[i]->Print();
        std::cout << std::endl;
    }
}
