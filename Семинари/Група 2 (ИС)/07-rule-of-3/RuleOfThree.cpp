#include <iostream>
#include <string>

#include "Hero.h"
#include "String.h"

int main()
{
    try
    {
        Hero hero("gosho", "petrov", 20);
        Hero hero2("pesho", "georgiev", 10);

        Hero copy = hero;  // Calls copy ctor
        Hero copy2(hero);  // Calls copy ctor
        Hero copy3{hero};  // Calls copy ctor
        copy.SetName("Tosho");
        std::cout << "Copy name:" << copy.GetName() << "\n";
        std::cout << "Original name:" << hero.GetName() << "\n";

        copy2 = hero2;           // Calls operator=
        copy2.operator=(hero2);  // Calls operator=
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what();
        std::cout << "Can't continue, exiting...";
    }

    // `new` also calls the constructor of Hero
    Hero* pHero = new (std::nothrow) Hero("gosho", "petrov", 20);

    // `delete` calls the destructor of Hero
    delete pHero;


    std::string str = "gosho";  // Parametrized ctor
    std::string sthElse = str;  // Copy ctor
    sthElse = str;              // operator= (assignment operator)

    String str2 = "gosho";   // Parametrized ctor
    String otherStr = str2;  // Copy ctor!
    otherStr = str2;         // operator= (assignment operator)

    std::string emptyStr;
    String emptyStr2;
    std::cout << "Our string is " << str2.Length() << " characters long\n";
    std::cout << "Str string is " << str.length() << " characters long\n";


    return 0;
}
