#include <cstddef>
#include <stdexcept>
#include <iostream>

#include "eratosthenesBE.h"

int main()
{
    std::cout << (eratosthenes(17)?"TRUE":"FALSE") << std::endl;
}