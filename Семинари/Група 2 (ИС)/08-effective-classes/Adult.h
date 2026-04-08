#pragma once

#include <stdexcept>

class Adult
{
public:
    Adult() = default;

    explicit Adult(int age)
    {
        SetAge(age);
    }

    void SetAge(int newAge)
    {
        if (newAge < Adult::MIN_AGE)
            throw std::invalid_argument("Must be at least 18");

        this->age = newAge;
    }

    int GetAge() const { return age; }

private:
    static const int MIN_AGE = 18;
    int age = MIN_AGE;
};

