#include <iostream>
#include <utility>

#include "Student.h"

Student::Student(const char* name, unsigned age, const char* fn)
    : Person(name, age)
{
    SetFN(fn);
}

Student::Student(const Student& other)
    : Student(other.GetName(), other.GetAge(), other.fn)
{
}

Student& Student::operator=(const Student& other)
{
    if (this != &other)
    {
        Student temp(other);
        Swap(temp);
    }

    return *this;
}

Student::~Student()
{
    delete[] fn;
    fn = nullptr;
}

void Student::Print() const
{
    Person::Print();
    std::cout << " " << fn;
}

Student* Student::Clone() const
{
    return new Student(*this);
}

void Student::Swap(Student& other)
{
    Person::Swap(other);
    std::swap(fn, other.fn);
}
