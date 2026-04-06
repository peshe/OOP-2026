#include "Employee.hpp"

#include <cstring>
#include <stdexcept>

int Employee::counter = 0;

Employee::Employee(const char *firstName,
                   const char *lastName,
                   double      salary,
                   Employee   *boss,
                   Company    *company)
    : id(counter++), firstName(nullptr), lastName(nullptr), salary(salary), boss(boss), company(company)
{
    if (!firstName || !lastName)
        throw std::invalid_argument("nullptr was passed");

    if (boss == nullptr) // we planned for that
        boss = this;

    setFirstName(firstName); // can throw
    setLastName(lastName);   // can throw -> will cause memory leak from firstName
}

Employee::Employee(const Employee &other)
{
    copy(other);
}

Employee &Employee::operator=(const Employee &other)
{
    // Basic exception guarantee
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

Employee::~Employee()
{
    destroy();
}

void Employee::setFirstName(const char *name)
{
    // Strong exception safety
    if (name == nullptr)
        throw std::invalid_argument("name was nullptr");

    unsigned length  = strlen(name);
    char    *newName = new char[length + 1];
    strcpy(newName, name);

    delete[] this->firstName;
    this->firstName = newName;
}

const char *Employee::getFirstName() const
{
    return firstName;
}

void Employee::setLastName(const char *name)
{
    if (name == nullptr)
        throw std::invalid_argument("name was nullptr");

    unsigned length  = strlen(name);
    char    *newName = new char[length + 1];
    strcpy(newName, name);

    delete[] this->lastName;
    this->lastName = newName;
}

const char *Employee::getLastName() const
{
    return lastName;
}

int Employee::getId() const
{
    return id;
}

double Employee::getSalary() const
{
    return salary;
}

void Employee::setSalary(double salary)
{
    this->salary = salary;
}

const Employee *Employee::getBoss() const
{
    return boss;
}

void Employee::setBoss(Employee *boss)
{
    if (boss != nullptr)
        this->boss = boss;
}

const Company *Employee::getCompany() const
{
    return company;
}

void Employee::setCompany(Company *company)
{
    if (company)
        this->company = company;
}

void Employee::copy(const Employee &other)
{
    this->id        = counter++;
    this->firstName = strcpy(new char[strlen(other.firstName) + 1], other.firstName);
    this->lastName  = strcpy(new char[strlen(other.lastName) + 1], other.lastName);
    this->salary    = other.salary;
    this->boss      = other.boss;
    this->company   = other.company;
}

void Employee::destroy()
{
    delete[] firstName;
    delete[] lastName;
}
