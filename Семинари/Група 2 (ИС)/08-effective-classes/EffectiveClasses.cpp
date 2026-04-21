#include <iostream>

#include "AdultManager.h"
#include "AggregationExample.h"
#include "Singleton.h"
#include "String.h"
#include "Hero.h"

void fun()
{
    static int sth = 0;
    sth++;
    std::cout << sth << std::endl;
}

int main()
{
    AggregationExampleDynamicMemory();

    // Singleton s;  // error - private constructor
    Singleton& ref = Singleton::GetInstance();
    ref.DoSth();
    std::cout << ref.GetGlobalState() << "\n";
    const Singleton& ref2 = Singleton::GetInstance();  // different reference, same object
    // Singleton copy = Singleton::GetInstance();  // error can't copy !

    Hero hero{"gosho", "petrov", 10};
    const String& strRef = hero.GetFirstName();
    String copy = hero.GetFirstName();
    copy.Set("changed copy");

    // int a;
    // int b;
    // int c;
    // a = b = (c = 10);
    // a.operator=(b.operator=(c.operator=(10)));

    String str1 = "fmi";
    // String str2 = 10;          // implicit conversion
    // String str3 = String(10);  // explicit conversion

    String strNum = String::ParseInt(10);  // static factory method (or also called a "named constructor")
    std::cout << strNum.Get() << std::endl;

    fun();  // prints 1
    fun();  // prints 2
    fun();  // prints 3

    // Exceptions usage example
    try
    {
        AdultManager manager;

        // Errors that we expect and know how to handle are handled inside the class's RunConsole method
        manager.RunConsole();
    }
    catch (const std::exception& ex)
    {
        // Errors that we didn't expect, or don't know how to handle can be caught in main()
        std::cerr << "An unexpected error occurred: " << ex.what() << "\n";
        std::cout << "Cannot continue, exiting the program...";
    }
    catch (...)
    {
        std::cerr << "A completely unknown error occurred!";
        std::cout << "Cannot continue, exiting the program...";
    }

    return 0;
}
