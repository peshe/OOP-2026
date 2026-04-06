#pragma once

class Company; // forward declaration

class Employee
{
public:
    Employee(const char *firstName,
             const char *lastName,
             double      salary,
             Employee   *boss,
             Company    *company);
    Employee(const Employee &other);
    Employee &operator=(const Employee &other);
    ~Employee();

    int             getId() const;
    const char     *getFirstName() const;
    const char     *getLastName() const;
    double          getSalary() const;
    const Employee *getBoss() const;
    const Company  *getCompany() const;

    void setFirstName(const char *name);
    void setLastName(const char *name);
    void setSalary(double salary);
    void setBoss(Employee *boss);
    void setCompany(Company *company);

private:
    void copy(const Employee &other);
    void destroy();

    int    id;
    char  *firstName, *lastName;
    double salary;

    Employee *boss;
    Company  *company;

    static int counter;
};
