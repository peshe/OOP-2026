#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first;
    U second;
};

int main()
{
    Pair<int, float> pair1 {1, 5.f};   
}