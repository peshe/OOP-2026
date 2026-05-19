#include <iostream>
#include <cstring>
#include <utility>
#include <stdexcept>
#include "Meal.h"


Meal::Meal(const char* name, const char* recipe, unsigned calories) : calories(calories)
{
    SetName(name);
    try
    {
        SetRecipe(recipe);
    }
    catch (...)
    {
        Clear();
        throw;  // Rethrow!
    }
}

Meal::Meal(const Meal& other)
    : Meal(other.name, other.recipe, other.calories)
{
}

Meal& Meal::operator=(const Meal& other)
{
    if (this == &other)
        return *this;

    Meal temp(other);
    std::swap(name, temp.name);
    std::swap(recipe, temp.recipe);
    std::swap(calories, temp.calories);

    return *this;
}

Meal::~Meal() noexcept
{
    Clear();
}

void Meal::SetName(const char* name)
{
    this->name = AllocString(name);
}

void Meal::SetRecipe(const char* recipe)
{
    this->recipe = AllocString(recipe);
}

char* Meal::AllocString(const char* src)
{
    if (src == nullptr)
        throw std::invalid_argument("String must not be nullptr");

    char* res = new char[strlen(src) + 1];
    strcpy(res, src);
    return res;
}

bool Meal::ContainsIngredient(const char* ingredient) const
{
    return strstr(recipe, ingredient) != nullptr;
}

void Meal::Print() const
{
    std::cout << "Meal \"" << GetName() << "\", `" << GetRecipe() << "`, " << GetCalories() << " calories";
}

void Meal::Clear() noexcept
{
    delete[] name;
    delete[] recipe;
    name = nullptr;
    recipe = nullptr;
    calories = 0;
}

bool operator==(const Meal& lhs, const Meal& rhs)
{
    return lhs.GetCalories() == rhs.GetCalories()
        && strcmp(lhs.GetName(), rhs.GetName()) == 0
        && strcmp(lhs.GetRecipe(), rhs.GetRecipe()) == 0;
}

bool operator!=(const Meal& lhs, const Meal& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Meal& lhs, const Meal& rhs)
{
    if (lhs.GetCalories() < rhs.GetCalories())
        return true;

    if (lhs.GetCalories() > rhs.GetCalories())
        return false;

    int nameCmp = strcmp(lhs.GetName(), rhs.GetName());
    if (nameCmp < 0)
        return true;

    if (nameCmp > 0)
        return false;

    if (strcmp(lhs.GetRecipe(), rhs.GetRecipe()) < 0)
        return true;

    return false;
}

bool operator>=(const Meal& lhs, const Meal& rhs)
{
    return !(lhs < rhs);
}

bool operator>(const Meal& lhs, const Meal& rhs)
{
    return rhs < lhs;
}

bool operator<=(const Meal& lhs, const Meal& rhs)
{
    return !(rhs < lhs);
}

