#include <complex>
#include <iostream>

#include "ComplexNum.h"
#include "Fraction.h"
#include "String.h"

int main()
{
    ComplexNum complexNum{2, 3};
    ComplexNum complexNum2 = -complexNum;
    std::cout << complexNum2.real << std::endl;

    ComplexNum complexNum3 = complexNum + complexNum2;
    std::cout << complexNum3.real << std::endl;

    Fraction fraction{2, 3};  // 2/3 == 0.6666
    // double val = fraction;  // Error: Fraction to double conversion is explicit
    std::cout << static_cast<double>(fraction) << std::endl;

    int a = +-+-+-5;

    String str1 = "abc";
    String res = str1.operator+("def");
    String sum = String("abc") + String("def");
    String sum2 = String("abc") + "def";  // Here "def" is converted to String, because of the implicit ctor
    std::cout << sum.Get() << "\n";
    std::cout << sum2.Get() << "\n";

    return 0;
}
