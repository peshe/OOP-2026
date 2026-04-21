#pragma once

#include "Car.h"

class Dealership
{
public:
    explicit Dealership(unsigned count);
    Dealership(const Dealership& other);             // We can `= delete` if we're not going to copy Dealerships
    Dealership& operator=(const Dealership& other);  // We can `= delete` if we're not going to copy Dealerships
    ~Dealership();

    // Variant: Aggregation + no exception handling at method level
    void Add(Car* car, float price);

    // Variant: Owning cars + handling exceptions inside the method
    // bool Add(const Car& car, float price);

    void Sell(unsigned index);

    void PrintStats() const;
    void PrintCars() const;

private:
    unsigned FindFreeSpace() const;

    struct Slot
    {
        Car* car = nullptr;
        float price = 0.0f;
    };

    Slot* slots = nullptr;
    unsigned count = 0;
    unsigned soldCarsCount = 0;
    float totalRevenue = 0.0f;
};
