#include <iostream>
#include <stdexcept>
#include "Company.hpp"
#include "Employee.hpp"

int main()
{
    try
    {
        Employee boss("Boss", "Man", 99999, nullptr, nullptr);
        Company  gooble("Gooble", &boss);
        boss.setCompany(&gooble);

        Employee e1("John", "Employee", 1000, &boss, &gooble);
        Employee e2("Lizard", "Man", 1200, &boss, &gooble);
        Employee e3("Johnson", "Shocking", 2600, &boss, &gooble);

        gooble.addEmployee(&e1);
        gooble.addEmployee(&e2);
        gooble.addEmployee(&e3);
    }
    catch (const std::invalid_argument &err)
    {
        std::cerr << err.what();
    }
    catch (...)
    {
        std::cerr << "Uh oh...";
    }
    return 0;
}
