#include <iostream>
#include <cstring>

#include "AdultManager.h"

void AdultManager::RunConsole()
{
    PrintHelp();

    const int MAX_CMD_LEN = 64;
    char command[MAX_CMD_LEN] = {};

    while (strcmp(command, "exit") != 0)
    {
        try
        {
            std::cin >> command;

            if (strcmp(command, "add") == 0)
            {
                int age = 0;
                std::cin >> age;
                arr[count++] = Adult(age);
            }
            // There could be other commands here ...
            else
            {
                std::cout << "Unknown command.\n";
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            // We catch the specific error, print its message and continue with our loop
        }
    }

    PrintState();
}

void AdultManager::PrintHelp()
{
    std::cout << " Usage:\n";
    std::cout << "  add <number>  - Adds an adult with the specified age, must be at least 18\n";
    std::cout << "  exit          - Exits the program and prints all the adult ages\n";
}

void AdultManager::PrintState() const
{
    std::cout << count << " adult ages added:\n ";
    for (int i = 0; i < count; i++)
        std::cout << arr[i].GetAge() << " ";
    std::cout << "\nBye!\n";
}
