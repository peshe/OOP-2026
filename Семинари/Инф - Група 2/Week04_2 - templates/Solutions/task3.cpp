#include <iostream>

template<typename T>
void Swap(T& first, T& second)
{
    T temp = first;
    first = second;
    second = temp;
}

int main()
{
    int a = 10, b = 20;

    Swap(a, b);

    std::cout << a << " " << b;
}