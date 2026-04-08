#pragma once

struct Fraction
{
    int numerator;
    int denominator;

    // In class, method (member function), operators
    // Here the first argument (the left hand side) is `this`

    // Fraction + int -> Fraction
    Fraction operator+(int num) const;

    // Fraction += int -> Fraction&
    Fraction& operator+=(int num);

    // Conversion operator
    explicit operator double() const;

    // Unary `-` and `+` operators
    Fraction operator-() const;
    Fraction operator+() const;
};

