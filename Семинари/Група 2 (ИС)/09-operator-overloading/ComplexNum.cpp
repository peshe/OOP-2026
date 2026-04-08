#include "ComplexNum.h"

ComplexNum operator-(const ComplexNum& num)
{
    ComplexNum result;
    result.real = -num.real;
    result.imag = num.imag;
    return result;
}

ComplexNum operator+(const ComplexNum& lhs, const ComplexNum& rhs)
{
    ComplexNum result;
    result.real = lhs.real + rhs.real;
    result.imag = lhs.imag + rhs.imag;
    return result;
}
