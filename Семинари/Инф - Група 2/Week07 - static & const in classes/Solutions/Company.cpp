#include "Company.hpp"

#include <cstring>
#include <stdexcept>

#include "Employee.hpp"

Company::Company(const char *name, Employee *boss)
    : name(nullptr), boss(nullptr), employees(nullptr), employeeCount(0)
{
    if (!name || !boss)
        throw std::invalid_argument("nullptr was passed");

    this->boss = boss;
    setName(name);
}

Company::Company(const Company &other)
{
    copy(other);
}

Company &Company::operator=(const Company &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

Company::~Company()
{
    destroy();
}

void Company::setName(const char *name)
{
    // Strong exception guarantee
    if (name == nullptr)
        throw std::invalid_argument("name was nullptr");

    unsigned length  = strlen(name);
    char    *newName = new char[length + 1];
    strcpy(newName, name);

    delete[] this->name;
    this->name = newName;
}

void Company::addEmployee(Employee *employee)
{
    Employee **newEmployees = new Employee *[employeeCount + 1];

    for (unsigned i = 0; i < employeeCount; i++)
        newEmployees[i] = this->employees[i];
    newEmployees[employeeCount] = employee;
    employeeCount++;

    delete[] this->employees; // this is okay even if there are no employees (it is nullptr)
    this->employees = newEmployees;
}

void Company::removeEmployee(int id)
{
    if (employeeCount <= 0) // in case we remove everyone and then keep removing
        return;

    Employee **newEmployees = new Employee *[employeeCount - 1];

    for (unsigned i = 0, j = 0; i < employeeCount; i++)
    {
        if (employees[i]->getId() != id) // "->getId()" is why we need to #include "Employee.hpp"
            newEmployees[j++] = this->employees[i];
        else // should happen only once
            employeeCount--;
    }

    delete[] this->employees;
    this->employees = newEmployees;
}

void Company::copy(const Company &other)
{
    this->name      = strcpy(new char[strlen(other.name) + 1], other.name);
    this->employees = new Employee *[other.employeeCount];
    for (unsigned i = 0; i < other.employeeCount; i++)
        this->employees[i] = other.employees[i];
    this->employeeCount = other.employeeCount;
    this->boss          = other.boss;
}

void Company::destroy()
{
    delete[] name;
    delete[] employees; // we don't delete the actual employees
                        // just the array of pointers
}
