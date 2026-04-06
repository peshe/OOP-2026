#pragma once
#include <iostream>

class Circle
{
public:
    Circle()
        : Circle(0, 0, 1)
    {
    }

    Circle(double x, double y, double radius)
        : x(x), y(y), radius(radius)
    {
        if (radius <= 0)
            throw "Negative radius";
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getRadius() const { return radius; }

    void setX(double value) { x = value; }
    void setY(double value) { y = value; }

    bool isPointInside(double x, double y) const
    {
        double a = this->x - x;
        double b = this->y - y;

        return a * a + b * b - radius * radius <= 1e-9;
    }

private:
    double x, y;
    const double radius;
};