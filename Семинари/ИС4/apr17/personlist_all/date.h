#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>

struct Date
{
    int year;
    int month;
    int day;


    bool write(std::ostream & os) const
    {

    }

    bool read(std::istream & is)
    {

    }

};

inline
std::ostream & operator << (std::ostream & os, Date const & date)
{
    return os;
}

inline
std::istream & operator >> (std::istream & is, Date & date)
{
    return is;
}

#endif