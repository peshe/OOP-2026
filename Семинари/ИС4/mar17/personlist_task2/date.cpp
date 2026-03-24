#include "date.h"

#include <iostream>

void printDate(Date const & date)
{
    std::cout << date.day << "." << date.month << "." << date.year;
}