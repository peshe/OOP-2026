#include <iostream>
#include <stdexcept>

#include "Date.h"
#include "Utils.h"

const uint16_t Date::DAY_BITS = 5;
const uint16_t Date::MONTH_BITS = 4;
const uint16_t Date::YEAR_BITS = 6;

const uint16_t Date::DAY_OFFSET = 0;
const uint16_t Date::MONTH_OFFSET = DAY_OFFSET + DAY_BITS;
const uint16_t Date::YEAR_OFFSET = MONTH_OFFSET + MONTH_BITS;

const uint16_t Date::DAY_MASK = ((1 << DAY_BITS) - 1) << DAY_OFFSET;
const uint16_t Date::MONTH_MASK = ((1 << MONTH_BITS) - 1) << MONTH_OFFSET;
const uint16_t Date::YEAR_MASK = ((1 << YEAR_BITS) - 1) << YEAR_OFFSET;

const uint16_t Date::MIN_YEAR = 1970;
const uint16_t Date::MAX_YEAR_DATA = YEAR_MASK >> YEAR_OFFSET;
const uint16_t Date::MAX_YEAR = MIN_YEAR + MAX_YEAR_DATA;

Date::Date(uint16_t day, uint16_t month, uint16_t year)
{
    Set(day, month, year);
}

Date::Date(const char* date)
{
    if (!date)
        throw std::invalid_argument("Date must be a valid string");

    uint16_t day = ParseInt(date);
    uint16_t month = ParseInt(date + 3);
    uint16_t year = ParseInt(date + 6);

    Set(day, month, year);
}

void Date::Set(uint16_t day, uint16_t month, uint16_t year)
{
    Validate(day, month, year);

    SetDay(day);
    SetMonth(month);
    SetYear(year);
}
uint16_t Date::GetDay() const
{
    return (data & DAY_MASK) >> DAY_OFFSET;
}

uint16_t Date::GetMonth() const
{
    return (data & MONTH_MASK) >> MONTH_OFFSET;
}

uint16_t Date::GetYear() const
{
    return MIN_YEAR + ((data & YEAR_MASK) >> YEAR_OFFSET);
}

void Date::SetDay(uint16_t day)
{
    SetData(day, DAY_OFFSET, DAY_MASK);
}

void Date::SetMonth(uint16_t month)
{
    SetData(month, MONTH_OFFSET, MONTH_MASK);
}

void Date::SetYear(uint16_t year)
{
    SetData(year - MIN_YEAR, YEAR_OFFSET, YEAR_MASK);
}

void Date::SetData(uint16_t value, uint16_t offset, uint16_t mask)
{
    data &= ~mask;
    data |= (value << offset) & mask;
}

void Date::Print(std::ostream& out) const
{
    out << GetDay() << "/" << GetMonth() << "/" << GetYear();
}

void Date::Validate(uint16_t day, uint16_t month, uint16_t year)
{
    if (year < MIN_YEAR || year > MAX_YEAR)
        throw std::invalid_argument("Year out of range");

    if (day == 0 || day > DaysInMonth(month, year))
        throw std::invalid_argument("Day out of range");
}

int Date::ParseInt(const char* num)
{
    int result = 0;
    while (num != nullptr && *num != '\0' && *num != '/')
    {
        result *= 10;
        result += *num - '0';
        num++;
    }
    return result;
}
