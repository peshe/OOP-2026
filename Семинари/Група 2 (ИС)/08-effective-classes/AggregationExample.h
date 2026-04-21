#pragma once

#include <iostream>
#include <vector>

#include "String.h"

// 1. Forward Declaration:
// Tells the compiler "Student exists, I'll define it later."
class Student;

class Teacher {
public:
    String name;
    // Aggregation: Teacher points to a Student, but doesn't own them.
    std::vector<Student*> studentList;

    Teacher(const String& n) : name(n) {}

    void addStudent(Student* s) {
        studentList.push_back(s);
    }
};

class Teacher;

class Student {
public:
    String name;
    // Aggregation: Student points back to a Teacher.
    Teacher* primaryTeacher;

    Student(const String& n) : name(n), primaryTeacher(nullptr) {}

    void setTeacher(Teacher* t) {
        primaryTeacher = t;
    }
};

inline void AggregationExampleDynamicMemory()
{
    // Both objects are created independently (Aggregation)
    Teacher* mrSmith = new Teacher("Mr. Smith");
    Student* alice = new Student("Alice");

    // Establishing the circular relationship
    mrSmith->addStudent(alice);
    alice->setTeacher(mrSmith);

    std::cout << alice->name.Get() << " is taught by " << alice->primaryTeacher->name.Get() << std::endl;
    std::cout << mrSmith->name.Get() << " has " << mrSmith->studentList[0]->name.Get() << " in class." << std::endl;

    // Because it's aggregation, deleting the teacher doesn't destroy the student.
    delete mrSmith;
    std::cout << "Teacher deleted, but " << alice->name.Get() << " still exists." << std::endl;

    delete alice;
}

inline void AggregationExampleAutomaticMemory()
{
    // Both objects are created independently (Aggregation)
    Teacher mrSmith("Mr. Smith");

    {
        Student alice("Alice");

        // Establishing the circular relationship
        mrSmith.addStudent(&alice);
        alice.setTeacher(&mrSmith);

        std::cout << alice.name.Get() << " is taught by " << alice.primaryTeacher->name.Get() << std::endl;
    }  // The student object `alice` dies here

    // Problem - teacher outlives student!
    std::cout << mrSmith.name.Get() << " has " << mrSmith.studentList[0]->name.Get() << " in class." << std::endl;
}

