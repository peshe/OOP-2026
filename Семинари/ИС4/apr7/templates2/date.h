#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>

struct Date
{
    int year;
    int month;
    int day;
};

bool writeDateText(std::ostream & os, Date const & date);
bool readDateText(std::istream & is, Date & date);

bool writeDateBinary(std::ostream & os, Date const & date);
bool readDateBinary(std::istream & is, Date & date);

#endif