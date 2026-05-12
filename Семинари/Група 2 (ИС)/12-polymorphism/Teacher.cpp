#include <iostream>
#include <utility>

#include "Teacher.h"

Teacher::Teacher(const char* name, unsigned age, const char* subject)
    : Person(name, age)
{
    SetSubject(subject);
}

Teacher::Teacher(const Teacher& other)
    : Teacher(other.GetName(), other.GetAge(), other.subject)
{
}

Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other)
    {
        Teacher temp(other);
        Swap(temp);
    }

    return *this;
}

Teacher::~Teacher()
{
    delete[] subject;
    subject = nullptr;
}

void Teacher::Print() const
{
    Person::Print();
    std::cout << " teaching " << subject;
}

Teacher* Teacher::Clone() const
{
    return new Teacher(*this);
}

void Teacher::Swap(Teacher& other)
{
    Person::Swap(other);
    std::swap(subject, other.subject);
}
