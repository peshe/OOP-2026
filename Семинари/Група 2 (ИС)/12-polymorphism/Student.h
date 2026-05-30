#pragma once

#include "Person.h"

class Student : virtual public Person
{
public:
    explicit Student(const char* name = "", unsigned age = 0, const char* fn = "");
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student() override;

    void        SetFN(const char* newFn) { DynCopyStr(fn, newFn); }
    const char* GetFN() const            { return fn; }

    void Print() const override;
    Student* Clone() const override;  // Note the return type can be a child ptr and still override the method

protected:
    void Swap(Student& other);

private:
    char* fn = nullptr;
};
