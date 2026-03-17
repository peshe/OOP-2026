#include <iostream>

#include "Hero.h"

int main()
{
    const char* someName = "Gosho";
    const char* filePath = "SomeHeroData.bin";

    Hero hero;
    hero.name = new (std::nothrow) char[strlen(someName) + 1];
    strcpy(hero.name, someName);
    hero.heroClass = HeroClass::Mage;
    hero.health = 20;
    hero.weapon.dmg = 5;
    hero.weapon.attSpeed = 1.2f;
    hero.achievements[5] = true;

    /// --- Writing the hero to a binary file ---

    std::cout << "Our hero:\n";
    printHero(hero);
    std::cout << "\n";

    saveHeroToFile(filePath, hero);

    clearHero(hero);  // Don't forget to delete your memory!

    /// --- Loading the hero from a binary file ---

    Hero loadedHero;
    loadHeroFromFile(filePath, loadedHero);

    std::cout << "\nThe hero we loaded from the file:\n";
    printHero(loadedHero);
    std::cout << "\n";

    clearHero(loadedHero);  // Don't forget to delete your memory!

    return 0;
}
