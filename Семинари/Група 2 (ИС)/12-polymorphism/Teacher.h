#pragma once
#include "Person.h"

class Teacher : public Person
{
public:
    explicit Teacher(const char* name = "", unsigned age = 0, const char* subject = "");
    Teacher(const Teacher& other);
    Teacher& operator=(const Teacher& other);
    ~Teacher() override;

    void        SetSubject(const char* newSubject) { DynCopyStr(subject, newSubject); }
    const char* GetSubject() const                 { return subject; }

    void Print() const override;
    Teacher* Clone() const override;  // Note the return type can be a child ptr and still override the method

protected:
    void Swap(Teacher& other);

private:
    char* subject = nullptr;
};
