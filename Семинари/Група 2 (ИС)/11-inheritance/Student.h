#pragma once

#include "String.h"
#include "Person.h"

// struct Base{};
// struct Derived : Base {};  // by default public inheritance

class Student : public Person  // public inheritance, means an "is-a" relation
{
public:
    Student(const String& name, unsigned age, const String& fn)
        : Person(name, age)
        , facNum(fn)
    {
        std::cout << "Entered Student(" << name << ", " << age << ", " << fn << ")\n";
    }

    // Can convert a person to a student by supplying a fn, or defaulting to "1MI0000"
    Student(const Person& person, const String& fn = "1MI0000")
        : Person(person)
        , facNum(fn)
    {
        std::cout << "Entered Student(Person{";
        person.Print();
        std::cout << "}, " << fn << ")\n";
    }

    ~Student()
    {
        std::cout << "Entered ~Student() for " << GetName() << std::endl;
        // delete[] sth;
        // Will call Person's destructor, we do NOT call it manually
    }

    Student(const Test& test, const String& fn);

    // Student(const String& name, unsigned age)
    //     : Person(name, age)
    // {}
    //
    // or
    //
    // using Person::Person;

    void Print() const
    {
        // Person::Print();
        // std::cout << name;
        std::cout << GetName();
        std::cout << ", FN: " << facNum;
    }

    void SomeUtilityMethod() const { Person::SomeUtilityMethod(); }

private:
    String facNum;
};
