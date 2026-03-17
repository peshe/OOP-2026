#include <iostream>
#include "Weapon.h"

void printWeapon(const Weapon &weapon)
{
    std::cout << "Weapon{ dmg: " << weapon.dmg << ", spd: " << weapon.attSpeed << " }";
}

// Passing ofstream as a reference as we do NOT want to copy the stream, but we'll be changing it!
void saveWeaponToFile(std::ofstream& out, const Weapon &weapon)
{
    out.write(reinterpret_cast<const char*>(&weapon.dmg), sizeof(weapon.dmg));
    out.write(reinterpret_cast<const char*>(&weapon.attSpeed), sizeof(weapon.attSpeed));

    // Since out struct consists only of primitive types we could write the whole struct into the file.
    // But this would mean that we'll also write the 4 bytes of padding in the file.
    // out.write(reinterpret_cast<const char*>(&weapon), sizeof(weapon));
}

// Passing ifstream as a reference as we do NOT want to copy the stream, but we'll be changing it!
void loadWeaponFromFile(std::ifstream& in, Weapon& outWeapon)
{
    in.read(reinterpret_cast<char*>(&outWeapon.dmg), sizeof(outWeapon.dmg));
    in.read(reinterpret_cast<char*>(&outWeapon.attSpeed), sizeof(outWeapon.attSpeed));

    // If we wrote the whole struct into the file, we could read it back as such:
    // in.read(reinterpret_cast<char*>(&outWeapon), sizeof(outWeapon));
}
