#include <iostream>
#include <fstream>

#include "Hero.h"

void printHeroClass(HeroClass heroClass)
{
    if (heroClass > HeroClass::Unknown && heroClass < HeroClass::Count)
        std::cout << HERO_CLASS_NAMES[static_cast<int>(heroClass)];
    else
        std::cout << "Unknown class";
}

void printHero(const Hero& hero)
{
    std::cout << (hero.name ? hero.name : "") << ", ";
    std::cout << "hp: " << hero.health << ", ";
    printHeroClass(hero.heroClass);
    std::cout << ", ";
    printWeapon(hero.weapon);

    // TODO: achievements
}

void clearHero(Hero& hero)
{
    delete[] hero.name;
    hero.name = nullptr;

    // We could also zero-out the other fields here
}

bool saveHeroToFile(const char* filePath, const Hero& hero)
{
    std::ofstream out(filePath, std::ios::binary);
    if (!out)
    {
        std::cout << "Failed to open file for writing: " << filePath;
        return false;
    }

    const size_t len = strlen(hero.name);
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(hero.name, len);

    out.write(reinterpret_cast<const char*>(&hero.health), sizeof(hero.health));
    out.write(reinterpret_cast<const char*>(&hero.heroClass), sizeof(hero.heroClass));

    saveWeaponToFile(out, hero.weapon);

    // TODO: achievements

    out.close();
    return true;
}

bool loadHeroFromFile(const char* filePath, Hero& outHero)
{
    std::ifstream in(filePath, std::ios::binary);
    if (!in)
    {
        std::cout << "Failed to open file for reading: " << filePath << "\n";
        return false;
    }

    // Make sure the previous name is deleted!
    clearHero(outHero);

    /// Make sure the order and sizes of all read data is EXACTLY the same as the written data!

    // We read the length of the name
    size_t len = 0;  // Make sure this is the same type used in the save method!
    in.read(reinterpret_cast<char*>(&len), sizeof(len));

    // We try to allocate enough memory for the name
    outHero.name = new (std::nothrow) char[len + 1];
    if (!outHero.name)
    {
        std::cout << "Couldn't allocate enough memory for the hero's name!\n";
        return false;
    }

    // We read the name from the file, and we write it inside the newly allocated space
    in.read(outHero.name, len);
    outHero.name[len + 1] = '\n';  // Don't forget to write the terminating zero!

    in.read(reinterpret_cast<char*>(&outHero.health), sizeof(outHero.health));
    in.read(reinterpret_cast<char*>(&outHero.heroClass), sizeof(outHero.heroClass));

    loadWeaponFromFile(in, outHero.weapon);

    // TODO: achievements

    in.close();
    return true;
}
