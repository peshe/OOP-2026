#include <iostream>
#include <cstring>
#include <utility>

class Character
{
public:
    Character(const char *name, unsigned health, unsigned armour, unsigned damage, float speed)
        : health(health), armour(armour), damage(damage), speed(speed)
    {
        setName(name);
    }
    Character(const Character &other)
        : health(other.health), armour(other.armour), damage(other.damage), speed(other.speed)
    {
        setName(other.name);
    }
    Character &operator=(const Character &other)
    {
        if (this != &other)
        {
            // Character copy(other);
            // this->health = copy.health;
            // this->armour = copy.armour;
            // this->damage = copy.damage;
            // this->speed = copy.speed;
            // std::swap(this->name, copy.name);
        }
        return *this;
    }
    virtual ~Character()
    {
        delete[] name;
    }

    virtual void attack(Character &target) = 0;

    void setHealth(unsigned health) { this->health = health; }
    void setArmour(unsigned armour) { this->armour = armour; }
    void setDamage(unsigned damage) { this->damage = damage; }
    void setSpeed(float speed) { this->speed = speed; }
    void setName(const char *name)
    {
        if (!name)
            return;

        char *newName = strcpy(new char[strlen(name) + 1], name);

        delete[] this->name;
        this->name = newName;
    }

    unsigned getHealth() const { return health; }
    unsigned getArmour() const { return armour; }
    unsigned getDamage() const { return damage; }
    float getSpeed() const { return speed; }
    const char *getName() const { return name; }

private:
    unsigned health, armour;
    unsigned damage;
    float speed;
    char *name = nullptr;
};

class Knight : public Character
{
public:
    Knight(const char *name, unsigned health, unsigned armour, unsigned damage, float speed)
        : Character(name, health, armour, damage, speed)
    {
    }

    void attack(Character &target) override
    {
        std::cout << this->getName() << " attacks " << target.getName() << '\n';
        target.setHealth(target.getHealth() - this->getDamage());
    }
};

class Mage : public Character
{
public:
    Mage(const char *name, unsigned health, unsigned armour, unsigned damage, float speed)
        : Character(name, health, armour, damage, speed)
    {
    }

    void attack(Character &target) override
    {
        std::cout << this->getName() << " casts a spell on " << target.getName() << '\n';

        unsigned newHealth = target.getHealth() - this->getDamage();

        target.setHealth(newHealth);

        if (this == &target)
            return;

        target.attack(target);
    }
};

void attack(Character& attacker, Character& target)
{
    attacker.attack(target);
}

int main()
{
    Knight k1("Vankata", 100, 100, 5, 10);
    Knight k2("Grome", 100, 100, 7, 10);
    Mage m1("Maggie", 200, 100, 50, 100);

    attack(m1, k1);
}
