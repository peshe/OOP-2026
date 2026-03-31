#pragma once
#include "String.h"

class Hero
{
public:
    // Parametrized constructor
    Hero(const char* name, const char* lastName, short health);

    // Copy constructor
    Hero(const Hero& other);

    // Assignment operator
    Hero& operator=(const Hero& other);

    // Destructor
    ~Hero();

    const char* GetName() const;
    bool SetName(const char* name);

private:
    // Helper methods (helper member functions)
    void clear();
    void copy(const Hero& other);

    // Fields (member variables)
    char* name = nullptr;
    char* lastName = nullptr;
    short health = 0;
};

// Now that we have a String class, we could
// implement our Hero class, as such:
struct ComposedHero
{
    String name;      // No need of default values for the names, because
    String lastName;  // the default constructor of String is called.
    short health = 0; // Default values should be given for primitive types.
};
