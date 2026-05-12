#include <iostream>

#include "UniversityOwning.h"

UniversityOwning::UniversityOwning(const UniversityOwning& other)
{
    arr = new Person*[other.cnt]{};
    try
    {
        for (int i = 0; i < cnt; ++i)
            arr[i] = other.arr[i]->Clone();
    }
    catch (...)
    {
        Clear();
        throw;  // Rethrow!!!
    }
}

UniversityOwning& UniversityOwning::operator=(const UniversityOwning& other)
{
    if (this != &other)
    {
        UniversityOwning temp(other);
        std::swap(arr, temp.arr);
        std::swap(cnt, temp.cnt);
    }
    return *this;
}

UniversityOwning::~UniversityOwning()
{
    Clear();
}

void UniversityOwning::AddPerson(Person* person)
{
    Person** newArr = new Person*[cnt + 1];
    for (int i = 0; i < cnt; ++i)
        newArr[i] = arr[i];  // Just moving pointers
    newArr[cnt] = person;

    delete[] arr;
    arr = newArr;
    cnt++;
}

void UniversityOwning::Print() const
{
    for (int i = 0; i < cnt; ++i)
    {
        arr[i]->Print();
        std::cout << std::endl;
    }
}

void UniversityOwning::Clear()
{
    for (int i = 0; i < cnt; ++i)
        delete arr[i];
    delete[] arr;
    arr = nullptr;
}
