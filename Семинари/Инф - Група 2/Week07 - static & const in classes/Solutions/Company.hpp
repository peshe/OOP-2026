#pragma once

class Employee; // forward declaration

class Company
{
public:
    Company(const char *name, Employee *boss);
    Company(const Company &other);
    Company &operator=(const Company &other);
    ~Company();

    void setName(const char *name);

    void addEmployee(Employee *employee);
    void removeEmployee(int id);

private:
    void copy(const Company &other);
    void destroy();


    char      *name;
    Employee  *boss;
    Employee **employees;
    unsigned   employeeCount;
};
