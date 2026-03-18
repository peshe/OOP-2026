#include "equipment.hpp"

int main() {
    // Instantiate a slot specifically for Sword objects
    EquipmentSlot<Sword> weaponSlot;
    weaponSlot.equip(Sword{}, 75);
    weaponSlot.status();

    // Instantiate a second (separate) version of the slot for Spell objects
    EquipmentSlot<Spell> magicSlot;
    magicSlot.equip(Spell{}, 100);
    magicSlot.status();

    return 0;
}