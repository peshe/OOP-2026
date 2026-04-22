#include <stdexcept>
#include "Utils.h"

int DaysInMonth(int month, int year)
{
    const bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        case 2:
            return isLeapYear ? 29 : 28;

        default:
            throw std::invalid_argument("Month is out of range");
    }
}
