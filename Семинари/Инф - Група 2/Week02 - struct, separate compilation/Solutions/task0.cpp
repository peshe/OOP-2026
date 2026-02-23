#include <iostream>

struct Item
{
    float price;
    unsigned quantity;
};

float sum(const Item* items, int size)
{
    float result = 0.0f;
    for (int i = 0; i < size; i++)
    {
        result += items[i].price * items[i].quantity;
    }
    return result;
}

Item& mostExpensive(Item* items, int size)
{
    Item* maxItem = &items[0];
    
    for (int i = 1; i < size; i++)
    {
        if (items[i].price > maxItem->price)
        {
            maxItem = &items[i];
        }
    }

    return *maxItem;
}

int main()
{
    Item items[] {
        {1.f, 100},
        {5.04f, 10},
        {2.04f, 6},
    };

    std::cout << sum(items, 3) << '\n';

    Item& mE = mostExpensive(items, 3);
    mE.price /= 2;

    std::cout << mostExpensive(items, 3).price;
}