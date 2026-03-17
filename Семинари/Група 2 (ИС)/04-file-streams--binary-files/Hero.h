#pragma once

#include "Weapon.h"

const int MAX_ACHIEVEMENTS = 32;

enum class HeroClass : char
{
    Unknown = -1,

    Mage,
    Warrior,
    Healer,

    Count,
};

inline const char* HERO_CLASS_NAMES[] = { "Mage", "Warrior", "Healer" };

struct Hero
{
    char* name = nullptr;  // 8 bytes
    short health = 0;      // 2 bytes
    HeroClass heroClass = HeroClass::Unknown;  // 1 byte

    // 5 bytes padding, because weapon has to start at
    // an address that is divisible by its size (8 bytes)

    Weapon weapon;  // 8 bytes
    bool achievements[MAX_ACHIEVEMENTS] = {};  // 32 bytes
};

void printHeroClass(HeroClass heroClass);
void printHero(const Hero& hero);
void clearHero(Hero& hero);

bool saveHeroToFile(const char* filePath, const Hero& hero);
bool loadHeroFromFile(const char* filePath, Hero& outHero);
