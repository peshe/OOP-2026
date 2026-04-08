#include "Fraction.h"

Fraction Fraction::operator+(int num) const
{
    Fraction result = *this;
    result += num;  // reuse operator+= in operator+
    return result;
}

Fraction & Fraction::operator+=(int num)
{
    // here `+=` is the operator `+=` for ints, so we're just adding an in to the numerator (that's an int)
    numerator += num * denominator;
    return *this;
}

Fraction::operator double() const
{
    return static_cast<double>(numerator) / denominator;
}

Fraction Fraction::operator-() const
{
    Fraction result;
    result.numerator = -numerator;
    result.denominator = denominator;
    return result;
}

Fraction Fraction::operator+() const
{
    return *this;  // Identity operator (just copies the fraction and returns the same value)
}
