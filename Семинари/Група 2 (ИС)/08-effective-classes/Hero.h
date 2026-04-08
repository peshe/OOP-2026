#pragma once

#include <iostream>

#include "String.h"

// struct Hero
// {
//     String firstName;
//     String lastName;
//     int health = 0;
// };

class Hero
{
public:
    Hero(const String& firstName, const String& lastName, int health);

    void SetHealth(int hp);
    int GetHealth() const { return health; }
    const String& GetFirstName() const { return firstName; }
    const String& GetLastName() const { return lastName; }

    friend void PrintHero(const Hero& hero);

private:
    String firstName;
    String lastName;
    int health = 0;
};

inline void PrintHero(const Hero& hero)
{
    std::cout << hero.health << std::endl;
}
