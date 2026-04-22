#include <utility>  // for std::swap
#include <exception>

#include "Dealership.h"

Dealership::Dealership(unsigned count)
{
    this->slots = new Slot[count]{};
    this->count = count;
}

Dealership::Dealership(const Dealership& other)
    : Dealership(other.count)
{
    for (int i = 0; i < count; ++i)
        this->slots[i] = other.slots[i];

    // If we own the cars (we don't use aggregation),
    // then we need to instead copy the cars
    // for (int i = 0; i < count; ++i)
    // {
    //     if (other.slots[i].car)
    //     {
    //         this->slots[i].car = new Car(*other.slots[i].car);
    //         this->slots[i].price = other.slots[i].price;
    //     }
    // }

    this->soldCarsCount = other.soldCarsCount;
    this->totalRevenue = other.totalRevenue;
}

// Copy and Swap idiom - Strong Exception Safety Guarantee
Dealership& Dealership::operator=(const Dealership& other)
{
    if (this != &other)
    {
        Dealership temp(other);  // copy constructor
        std::swap(this->slots, temp.slots);
        std::swap(this->count, temp.count);
        std::swap(this->soldCarsCount, temp.soldCarsCount);
        std::swap(this->totalRevenue, temp.totalRevenue);
    }  // temp's destructor is executed here

    return *this;
}

Dealership::~Dealership()
{
    // If we own the cars (we don't use aggregation),
    // then we also need to delete each car
    // for (unsigned i = 0; i < count; i++)
    // {
    //     delete slots[i].car;
    //     slots[i].car = nullptr;
    // }

    delete[] slots;
    slots = nullptr;
}

void Dealership::Add(Car* car, float price)
{
    if (price < 0)
        throw std::invalid_argument("Price can't be negative");

    unsigned freeSpace = FindFreeSpace();
    slots[freeSpace].car = car;
    slots[freeSpace].price = price;
}

// bool Dealership::Add(const Car& car, float price)
// {
//     if (price < 0)
//         return false;
//
//     try
//     {
//         unsigned freeSpace = FindFreeSpace();
//         Car* newCar = new (std::nothrow) Car(car);
//         if (!newCar)
//             return false;
//
//         slots[freeSpace].car = newCar;
//         slots[freeSpace].price = price;
//     }
//     catch (const std::runtime_error& ex)
//     {
//         return false;
//     }
//
//     return true;
// }

void Dealership::Sell(unsigned index)
{
    if (index >= count)
        throw std::invalid_argument("No such car");

    if (slots[index].car == nullptr)
        throw std::invalid_argument("No such car");

    soldCarsCount++;
    totalRevenue += slots[index].price;

    // If we own the cars (we don't use aggregation),
    // then we need to also delete the car
    // delete slots[index].car;
    slots[index].car = nullptr;
    slots[index].price = 0.0f;
}

void Dealership::PrintStats() const
{
    std::cout << "Dealership sold " << soldCarsCount << " cars for $" << totalRevenue;
}

void Dealership::PrintCars() const
{
    // TODO:
}

unsigned Dealership::FindFreeSpace() const
{
    for (unsigned i = 0; i < count; i++)
        if (slots[i].car == nullptr)
            return i;

    throw std::runtime_error("No more space in the dealership");
}
