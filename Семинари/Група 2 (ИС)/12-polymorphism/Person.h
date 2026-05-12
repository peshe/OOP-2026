#pragma once
#include "IPrintable.h"
#include "Utility.h"

class Person : public IPrintable
{
public:
    explicit Person(const char* name = "", unsigned age = 0);
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person() override;

    void        SetName(const char* newName) { DynCopyStr(name, newName); }
    const char* GetName() const              { return name; }

    void        SetAge(unsigned newAge) { age = newAge; }
    unsigned    GetAge() const          { return age; }

    void Print() const override;

    virtual Person* Clone() const;

protected:
    void Swap(Person& other);

private:
    char* name = nullptr;
    unsigned age = 0;
};
