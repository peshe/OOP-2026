#include "date.h"

#include <iostream>

void printDate(Date const & date)
{
    std::cout << date.day << "." << date.month << "." << date.year;
}

bool writeDateText(std::ostream & os, Date const & date)
{
    os << date.day << "." << date.month << "." << date.year;
    return !os.fail();
};

static
void check(std::istream & is, char c)
{
    if(is.peek() == c)
        is.get();
    else
        is.setstate(std::ios::failbit);

}

static
bool isLeap(int year)
{
    if(year % 400 == 0)
        return true;
    if(year % 100 == 0)
        return false;
    if(year % 4  == 0)
        return true;
    return false;
}

bool checkDate(Date const & d)
{
    if(d.month <= 0 || d.month > 12) 
        return false;

    if(d.year == 0)
        return false;

    if(d.day <= 0 || d.day > 31 )
        return false;

    switch(d.month)
    {
        case 4:
        case 6:
        case 9:
        case 11:
            if(d.day > 30)
                return false;
        break;

        case 2:
            if(d.day > 28 + isLeap(d.year))
                return false;
    }

    return true;
}


bool readDateText(std::istream & is, Date & date)
{
    is >> date.day;
    check(is,'.');
    is >> date.month;
    check(is,'.');
    is >> date.year;

    if(!checkDate(date))
        is.setstate(std::ios::failbit);

    return !is.fail();
}



bool writeDateBinary(std::ostream & os, Date const & d)
{
    os.write((char*)&d, sizeof(d));
    return !os.fail();
};

bool readDateBinary(std::istream & is, Date & d)
{
    is.read((char*)&d, sizeof(d));
    return !is.fail();
}