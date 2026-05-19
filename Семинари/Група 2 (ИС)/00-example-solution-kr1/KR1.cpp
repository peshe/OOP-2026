#include <iostream>

#include "Meal.h"
#include "Menu.h"

int main()
{
    try
    {
        Meal meal1("musaka", "some recipe 1", 400);
        Meal meal2("chushki", "recipe 2", 300);
        Meal meal3("qica na ochi", "great recipe for eggs 3", 500);
        Meal meal4("tikvichki", "not that great of a recipe for tikvichki with eggs", 450);

        meal1.Print();
        std::cout << std::endl;
        meal2.Print();
        std::cout << std::endl;
        meal3.Print();
        std::cout << std::endl;
        meal4.Print();
        std::cout << std::endl;

        Menu menu(4000);
        menu += meal1;
        menu += meal2;
        menu += meal3;
        menu += meal4;
        unsigned idx = menu("egg");

        std::cout << "\nFound egg dish with least amount of calories at index " << idx << ":\n";
        menu[idx].Print();
        std::cout << std::endl;

        menu -= menu[idx];
        std::cout << "Removed it.\n";

        unsigned newIdx = menu("egg");
        std::cout << "\nFound egg dish with least amount of calories at index " << newIdx << ":\n";
        menu[newIdx].Print();
        std::cout << std::endl;

        std::cout << "\nMenu calories: " << menu.TotalCalories() << std::endl;
        menu[newIdx].SetCalories(100);
        menu[newIdx].Print();
        std::cout << "\nMenu calories after changing the egg dish to 100 kcal: " << menu.TotalCalories() << std::endl;

        menu[newIdx].SetCalories(3900);  // Expect to throw
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
