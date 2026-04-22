#include <cstring>
#include <exception>

#include "Car.h"

unsigned long long Car::totalHp = 0;

Car::Car(const char* make, const Date& date, Type type, unsigned hp, unsigned seats)
    : date(date)
    , type(type)
    , hp(hp)
    , seats(seats)
{
    SetMake(make);

    totalHp += hp;
}

Car::Car(std::istream& in) : Car(ParseCar(in))
{
}

Car::Car(const Car& other)
    : date(other.date)
    , type(other.type)
    , hp(other.hp)
    , seats(other.seats)
{
    SetMake(other.make);

    totalHp += hp;

    // If we had code that can throw exceptions,
    // we must wrap it in a try catch block:
    //
    // try
    // {
    //     // code that can throw exceptions
    // }
    // catch (...)
    // {
    //     delete[] make;
    //     throw;  // Rethrow the same exception
    // }
}

Car::~Car()
{
    delete[] make;
    make = nullptr;

    totalHp -= hp;
}

unsigned long long Car::GetTotalHp()
{
    return totalHp;
}

// VW 01/01/2000 Sedan 100 5
Car Car::ParseCar(std::istream& in)
{
    if (!in)
        throw std::invalid_argument("Bad istream");

    const int BUFFER_SIZE = 1024;
    char makeBuffer[BUFFER_SIZE] = {};
    // TODO: Handle makes larger than 1023 characters

    in >> makeBuffer;

    const int DATE_SIZE = 16;
    char dateBuffer[DATE_SIZE] = {};
    in >> dateBuffer;

    Type type = ParseType(in);

    unsigned hp = 0;
    in >> hp;

    unsigned seats = 0;
    in >> seats;

    return Car(makeBuffer, dateBuffer, type, hp, seats);
}

Car::Type Car::ParseType(std::istream& in)
{
    const int TYPE_SIZE = 16;
    char typeBuffer[TYPE_SIZE] = {};
    in >> typeBuffer;

    if (strcasecmp(typeBuffer, "Sedan") == 0)
        return Type::SEDAN;
    if (strcasecmp(typeBuffer, "Hatchback") == 0)
        return Type::HATCHBACK;
    if (strcasecmp(typeBuffer, "Kombi") == 0)
        return Type::KOMBI;

    throw std::invalid_argument("Invalid car type");
}

const char* Car::TypeToString(Type type)
{
    switch (type)
    {
        case Type::SEDAN:
            return "Sedan";
        case Type::KOMBI:
            return "Kombi";
        case Type::HATCHBACK:
            return "Hatchback";
        default:
            return "Unknown";
    }
}

void Car::SetMake(const char* make)
{
    if (make == nullptr)
        throw std::invalid_argument("Must provide make");

    char* newMake = new char[strlen(make) + 1];
    strcpy(newMake, make);

    delete[] this->make;
    this->make = newMake;
}

std::ostream& operator<<(std::ostream& out, const Car& car)
{
    out << car.make << ", ";
    car.date.Print(out);
    out << ", ";
    out << Car::TypeToString(car.type) << ", ";
    out << car.hp << "hp, ";
    out << car.seats << " seats";
    return out;
}
