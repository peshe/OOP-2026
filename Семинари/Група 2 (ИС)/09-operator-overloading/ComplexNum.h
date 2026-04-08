#pragma once

struct ComplexNum
{
    float real = 0.0f;
    float imag = 0.0f;
};

// Operators as free (normal) functions
ComplexNum operator-(const ComplexNum& num);  // Unary `-` operator
ComplexNum operator+(const ComplexNum& lhs, const ComplexNum& rhs);  // Binary `+` operator

// template <typename T>
// ComplexNum operator+(const ComplexNum& lhs, const T& rhs)
// {
//     // Yes we can make template operators :)
// }
