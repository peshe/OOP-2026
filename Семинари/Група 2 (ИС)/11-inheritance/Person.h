#pragma once

#include <iostream>

#include "String.h"

class Person
{
public:
    Person(const String& name, unsigned age)
        : name(name)
        , age(age)
    {
        std::cout << "Entered Person(" << name << ", " << age << ")\n";
    }

    ~Person()
    {
        std::cout << "Entered ~Person() for " << name << std::endl;
    }

    void Print() const
    {
        std::cout << name << ", age: " << age;
    }

    const String& GetName() const
    {
        return name;
    }

protected:
    void SomeUtilityMethod() const { std::cout << "Person::SomeUtilityMethod()\n"; }

// protected:
private:
    String name;
    unsigned age = 0;
};

class Test
{
    Test(const String& sth, unsigned sthElse);
};