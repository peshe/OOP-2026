#include <iostream>
#include "Person.h"

// const Person& реферира директно оригиналната променлива,
// т.е. не правим копие, и освен това не ни позволява да я променяме
// В 99% от случаите ще подаваме структури по този начин.
void printPerson(const Person& person)
{
    std::cout << "Age: " << person.age << "\n";
    std::cout << "Name: " << person.name << "\n";
}

void readPerson(Person& outPerson)
{
    std::cout << "Enter age: ";
    std::cin >> outPerson.age;
    std::cout << "Enter name: ";
    std::cin >> outPerson.name;
}

void fun(Person personCopy)
{
    // ...
}
