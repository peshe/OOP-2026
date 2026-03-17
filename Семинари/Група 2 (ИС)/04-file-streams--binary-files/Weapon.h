#pragma once

#include <fstream>

struct Weapon
{
    short dmg = 0;
    float attSpeed = 0.0f;
};

void printWeapon(const Weapon& weapon);
void saveWeaponToFile(std::ofstream& out, const Weapon& weapon);
void loadWeaponFromFile(std::ifstream& in, Weapon& outWeapon);
