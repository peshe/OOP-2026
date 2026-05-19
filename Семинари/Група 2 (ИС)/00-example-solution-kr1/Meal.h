#pragma once

class Meal
{
public:
    Meal(const char* name = "", const char* recipe = "", unsigned calories = 0);
    Meal(const Meal& other);
    Meal& operator=(const Meal& other);
    ~Meal() noexcept;

    void SetName(const char* name);
    void SetRecipe(const char* recipe);
    void SetCalories(unsigned calories) { this->calories = calories; }

    const char* GetName() const { return name; }
    const char* GetRecipe() const { return recipe; }
    unsigned GetCalories() const { return calories; }

    bool ContainsIngredient(const char* ingredient) const;
    void Print() const;

private:
    void Clear() noexcept;

    static char* AllocString(const char* src);

    char* name = nullptr;
    char* recipe = nullptr;
    unsigned calories = 0;
};

bool operator==(const Meal& lhs, const Meal& rhs);
bool operator!=(const Meal& lhs, const Meal& rhs);
bool operator<(const Meal& lhs, const Meal& rhs);
bool operator>=(const Meal& lhs, const Meal& rhs);
bool operator>(const Meal& lhs, const Meal& rhs);
bool operator<=(const Meal& lhs, const Meal& rhs);

