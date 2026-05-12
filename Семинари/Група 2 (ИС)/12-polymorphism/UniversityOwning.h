#pragma once
#include "Person.h"

class UniversityOwning
{
public:
    UniversityOwning() = default;
    UniversityOwning(const UniversityOwning& other);
    UniversityOwning& operator=(const UniversityOwning& other);
    ~UniversityOwning();

    void AddPerson(Person* person);
    void Print() const;

private:
    void Clear();

    Person** arr = nullptr;
    unsigned cnt = 0;
};
