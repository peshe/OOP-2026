#include <iostream>
#include <stdexcept>

#include "Person.h"

Person::Person(const char* name, unsigned age)
    : age(age)
{
    SetName(name);
}

Person::Person(const Person& other)
    : Person(other.name, other.age)
{
}

Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        Person temp(other);
        Swap(temp);
    }

    return *this;
}

Person::~Person()
{
    delete[] name;
    name = nullptr;
}

void Person::Print() const
{
    std::cout << name << " " << age;
}

Person* Person::Clone() const
{
    return new Person(*this);
}

void Person::Swap(Person& other)
{
    std::swap(this->name, other.name);
    std::swap(this->age, other.age);
}
