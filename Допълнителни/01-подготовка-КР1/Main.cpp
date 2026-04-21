#include <iostream>

#include "Car.h"
#include "Date.h"
#include "Dealership.h"

int main()
{
    // Testing our classes

    try
    {
        Date date = "04/17/2006";
        std::cout << date.GetDay() << " " << date.GetMonth() << " " << date.GetYear() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Err for date: " << ex.what() << std::endl;
    }

    // Example input: VW 02/04/2000 sedan 75 5
    std::cout << "Enter car make (single word), date dd/mm/yyyy, type (sedan, kombi, hatchback), hp, seats:\n";
    std::cout << "You can use the example input: VW 02/04/2000 sedan 75 5\n";
    try
    {
        Car car(std::cin);
        std::cout << car << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Err: " << ex.what() << std::endl;
    }

    try
    {
        Car noGoodDate("Lada", "50/03/2009", Car::Type::SEDAN, 60, 5);
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << "Err for Lada: " << ex.what() << std::endl;
    }

    std::cout << "Total cars HP: " << Car::GetTotalHp() << std::endl;

    Dealership dealership(3);
    Car c1("VW", "02/10/1996", Car::Type::HATCHBACK, 75, 5);
    Car c2("Audi", "13/05/2000", Car::Type::SEDAN, 105, 5);
    Car c3("BMW", "31/07/2005", Car::Type::KOMBI, 300, 5);
    Car c4("Smart", "20/03/2016", Car::Type::HATCHBACK, 130, 2);
    dealership.Add(&c1, 999);
    dealership.Add(&c2, 1250);
    dealership.Add(&c3, 4000);

    dealership.PrintStats();
    std::cout << std::endl;
    try
    {
        dealership.Add(&c4, 3000);
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << "Err: " << ex.what() << std::endl;
    }

    std::cout << c1 << "\n" << c2 << "\n" << c3 << "\n" << c4 << "\n";
    std::cout << "Total HP: " << Car::GetTotalHp() << std::endl;
    std::cout << std::endl;
    dealership.Sell(1);
    dealership.Add(&c4, 3000);
    dealership.Sell(2);
    dealership.PrintStats();

    return 0;
}
