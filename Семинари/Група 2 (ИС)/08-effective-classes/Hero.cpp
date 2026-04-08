#include "Hero.h"

#include <stdexcept>

Hero::Hero(const String& firstName, const String& lastName, int health)
    : firstName(firstName)
    , lastName(lastName)
{
    SetHealth(health);
}

void Hero::SetHealth(int hp)
{
    if (hp <= 0)
        throw std::invalid_argument("Hero health must be positive");

    this->health = hp;
}
