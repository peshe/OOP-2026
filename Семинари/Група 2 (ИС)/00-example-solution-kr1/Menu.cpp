#include <stdexcept>
#include <cstring>

#include "Menu.h"

Menu::Menu(unsigned maxKCal) : maxCalories(maxKCal)
{
}

Menu& Menu::operator+=(const Meal& meal)
{
    if (meal.GetCalories() + currCalories > maxCalories)
        throw std::runtime_error("Can't add more calories to the menu");

    if (firstFreeIndex >= MAX_NUM_MEALS)
        throw std::runtime_error("No more space in the menu");

    meals[firstFreeIndex++] = meal;
    currCalories += meal.GetCalories();
    return *this;
}

Menu& Menu::operator-=(const Meal& meal)
{
    for (unsigned i = 0; i < firstFreeIndex; ++i)
    {
        if (meals[i] == meal)
        {
            Remove(i);
            currCalories -= meal.GetCalories();
            i--;
        }
    }
    return *this;
}

unsigned Menu::operator()(const char* ingredient) const
{
    unsigned minIdx = FindMealWithIngredient(ingredient);

    for (unsigned i = minIdx + 1; i < firstFreeIndex; ++i)
    {
        if (meals[i].GetCalories() < meals[minIdx].GetCalories()
            && meals[i].ContainsIngredient(ingredient))
        {
            minIdx = i;
        }
    }

    return minIdx;
}

void Menu::MealProxy::SetCalories(unsigned newCalories)
{
    unsigned oldMealCalories = meal->GetCalories();
    if (menu->TotalCalories() - oldMealCalories + newCalories > menu->maxCalories)
        throw std::runtime_error("The menu will have too much calories");

    menu->currCalories -= oldMealCalories;
    meal->SetCalories(newCalories);
    menu->currCalories += newCalories;
}

void Menu::Remove(unsigned idx)
{
    for (unsigned i = idx; i < firstFreeIndex - 1; ++i)
        meals[i] = meals[i+1];
    firstFreeIndex--;
}

unsigned Menu::FindMealWithIngredient(const char* ingredient) const
{
    for (unsigned i = 0; i < firstFreeIndex; ++i)
        if (meals[i].ContainsIngredient(ingredient))
            return i;

    throw std::runtime_error("No meal with this ingredient");
}
