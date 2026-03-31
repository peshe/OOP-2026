#include <iostream>
#include <cstring>

#include "Hero.h"

Hero::Hero(const char* name, const char* lastName, short health)
{
    std::cout << "Called Ctor Hero - " << name << "\n";

    int len = strlen(name);
    this->name = new char[len + 1];
    strcpy(this->name, name);

    try
    {
        int lenLast = strlen(lastName);
        this->lastName = new char[lenLast + 1];
        strcpy(this->lastName, lastName);
    }
    catch (std::bad_alloc& exc)
    {
        clear();  // Clears all previously allocated memory!
        throw;
    }

    this->health = health;
}

Hero& Hero::operator=(const Hero& other)
{
    if (this == &other)
        return *this;

    clear();
    copy(other);
    return *this;
}

Hero::Hero(const Hero& other)
{
    copy(other);
}

Hero::~Hero()
{
    clear();
}

const char* Hero::GetName() const
{
    return name;
}

bool Hero::SetName(const char* name)
{
    int len = strlen(name) + 1;
    char* newName = new (std::nothrow) char [len];
    if (!newName)
        return false;

    delete[] this->name;
    this->name = newName;
    strcpy(this->name, name);
    return true;
}

void Hero::clear()
{
    delete[] name;
    name = nullptr;
    delete[] lastName;
    lastName = nullptr;
}

void Hero::copy(const Hero& other)
{
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);

    // TODO: Exception problem!
    // If this memory allocation fails - we leak our this->name!
    this->lastName = new char[strlen(other.lastName) + 1];
    strcpy(this->lastName, other.lastName);

    this->health = other.health;
}
