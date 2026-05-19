#pragma once
#include "Meal.h"

class Menu
{
public:
    class MealProxy;

public:
    explicit Menu(unsigned maxKCal);

    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

    Menu& operator+=(const Meal& meal);
    Menu& operator-=(const Meal& meal);
    MealProxy operator[](unsigned idx) { return MealProxy(&meals[idx], this); }
    const Meal& operator[](unsigned idx) const { return meals[idx]; }

    unsigned TotalCalories() const { return currCalories; }

    unsigned operator()(const char* ingredient) const;

public:
    class MealProxy
    {
    public:
        MealProxy(Meal* meal, Menu* menu) : meal(meal), menu(menu) {}
        void SetCalories(unsigned newCalories);
        void Print() const { meal->Print(); }

        operator Meal&() { return *meal; }

    private:
        Meal* meal;
        Menu* menu;
    };

private:
    void Remove(unsigned idx);
    unsigned FindMealWithIngredient(const char* ingredient) const;

    inline static const unsigned MAX_NUM_MEALS = 100;

private:
    Meal meals[MAX_NUM_MEALS];
    unsigned firstFreeIndex = 0;
    unsigned currCalories = 0;
    const unsigned maxCalories = 0;
};
