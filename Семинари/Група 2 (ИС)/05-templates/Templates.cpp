#include <iostream>
#include "Utility.h"

int main()
{
    std::cout << min(4, 5) << "\n";
    std::cout << min(4.3f, 4.1f) << "\n";
    std::cout << min("gosho", "abcd");  // Сравнява указатели?!

    return 0;
}
