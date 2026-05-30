#include <iostream>

#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "TeachingAssistant.h"
#include "UniversityOwning.h"
#include "UniversityAggregation.h"

void fun(const Person& person)
{
    person.Print();  // Can call a child class's method if it's virtual (polymorphism with references)
}

void Print(const IPrintable** arr, unsigned size)
{
    for (int i = 0; i < size; ++i)
        arr[i]->Print();  // Polymorphism with pointers
}

int main()
{
    TeachingAssistant ta;
    ta.SetAge(25);
    ta.Print();
    std::cout << ta.GetAge();

    //std::cout << "Size of Person: " << sizeof(Person) << std::endl;
    //
    //std::cout << "Hello Polymorphism!\n";
    //
    //Person person("Gosho", 17);
    //Student student("Tosho", 21, "0MI0701337");
    //Teacher teacher("Pesho", 23, "Maths");
    //
    //person.Print(); std::cout << std::endl;
    //student.Print(); std::cout << std::endl;
    //Person* p = &student;
    //p->Print(); std::cout << std::endl;
    //
    //// teacher.Print(); std::cout << std::endl;
    //
    //// const Person& ref = &student;  // Can't do that by default
    //std::cout << "fun(student): ";
    //fun(student);  // References as arguments also act polymorphically
    //std::cout << std::endl;
    //
    //UniversityAggregation uni;
    //uni.AddPerson(&person);
    //uni.AddPerson(&student);
    //uni.AddPerson(&teacher);
    //uni.Print();
    //
    //UniversityOwning uniOwning;
    //uniOwning.AddPerson(new Student("Tosho", 26, "0MI0300000"));
    //uniOwning.AddPerson(new Teacher(teacher));
    //uniOwning.Print();

    return 0;
}
