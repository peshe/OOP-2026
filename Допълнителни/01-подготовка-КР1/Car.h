#pragma once

#include "Date.h"

class Car
{
public:
    enum class Type
    {
        UNKNOWN,
        SEDAN,
        KOMBI,
        HATCHBACK,
    };

    Car(const char* make, const Date& date, Type type, unsigned hp, unsigned seats);
    explicit Car(std::istream& in);
    Car(const Car& other);
    ~Car();

    // Can't copy `type`, because it's a constant
    Car& operator=(const Car&) = delete;

    void SetMake(const char* make);

    static unsigned long long GetTotalHp();

    // We don't have getters for our fields, so we utilize `friend`
    friend std::ostream& operator<<(std::ostream& out, const Car& car);

private:
    static Car ParseCar(std::istream& in);  // static factory method
    static Type ParseType(std::istream& in);
    static const char* TypeToString(Type type);

    char* make = nullptr;
    Date date;
    const Type type = Type::UNKNOWN;
    unsigned hp = 0;
    unsigned seats = 0;

    static unsigned long long totalHp;
};

std::ostream& operator<<(std::ostream& out, const Car& car);
