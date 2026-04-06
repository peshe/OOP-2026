#include <iostream>
#include "triangle.hpp"

int main()
{
    try
    {
        Triangle tri(0, 0, 0);

        std::cout << tri.getA() << " " << tri.getB() << " " << tri.getC();
    }
    catch (const char *message)
    {
        std::cerr << message;
    }
}