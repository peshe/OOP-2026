#pragma once

#include <cstdint>  // for uint16_t
#include <iostream>

class Date
{
public:
    Date(uint16_t day, uint16_t month, uint16_t year);
    Date(const char* date);

    void Set(uint16_t day, uint16_t month, uint16_t year);

    uint16_t GetDay() const;
    uint16_t GetMonth() const;
    uint16_t GetYear() const;

    void Print(std::ostream& out = std::cout) const;

private:
    static void Validate(uint16_t day, uint16_t month, uint16_t year);
    static int ParseInt(const char* num);

    void SetDay(uint16_t day);
    void SetMonth(uint16_t month);
    void SetYear(uint16_t year);

    void SetData(uint16_t value, uint16_t offset, uint16_t mask);

    static const uint16_t DAY_BITS;
    static const uint16_t MONTH_BITS;
    static const uint16_t YEAR_BITS;

    static const uint16_t DAY_OFFSET;
    static const uint16_t MONTH_OFFSET;
    static const uint16_t YEAR_OFFSET;

    static const uint16_t DAY_MASK;
    static const uint16_t MONTH_MASK;
    static const uint16_t YEAR_MASK;

    static const uint16_t MIN_YEAR;
    static const uint16_t MAX_YEAR_DATA;
    static const uint16_t MAX_YEAR;

private:
    uint16_t data = 0;
};
