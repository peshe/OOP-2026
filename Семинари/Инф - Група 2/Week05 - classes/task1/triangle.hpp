#pragma once
#include <cmath>

class Triangle
{
public:
    Triangle(double a, double b, double c)
    {
        if (!validateSides(a, b, c))
        {
            throw "Bad sides";
        }

        this->a = a;
        this->b = b;
        this->c = c;
    }

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }

    void setA(double value)
    {
        if (validateSides(value, b, c))
            a = value;
    }

    void setB(double value)
    {
        if (validateSides(a, value, c))
            b = value;
    }

    void setC(double value)
    {
        if (validateSides(a, b, value))
            c = value;
    }

    double calculatePerimeter() const
    {
        return a + b + c;
    }

    double calculateInscribedRadius() const
    {
        double s = calculatePerimeter() / 2.0;

        return (a * b * c) / (4 * sqrt(s * (s - a) * (s - b) * (s - c)));
    }

    double calculateCircumscribedRadius() const
    {
        double s = calculatePerimeter() / 2.0;

        return sqrt(s * (s - a) * (s - b) * (s - c)) / s;
    }

private:
    static bool validateSides(double a, double b, double c)
    {
        return a > 0 &&
               b > 0 &&
               c > 0 &&
               a + b > c &&
               b + c > a &&
               a + c > b;
    }

    double a, b, c;
};