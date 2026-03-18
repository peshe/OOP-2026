#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <iostream>

// Simple item structures
struct Sword {
    const char* name = "Excalibur";
    int power = 50;
};

struct Spell {
    const char* name = "Fireball";
    int power = 85;
};

// The "recipe" for an inventory slot
template <typename T>
struct EquipmentSlot {
    T item;
    int durability;

    // Method to equip a new item into the slot
    void equip(T newItem, int condition) {
        item = newItem;

        durability = condition;
    }

    // Method to display current slot status
    void status() {
        std::cout << "Item: " << item.name
            << " | Power: " << item.power
            << " | Condition: " << durability << "%\n";
    }
};

#endif