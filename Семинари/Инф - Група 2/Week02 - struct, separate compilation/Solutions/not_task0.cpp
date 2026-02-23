#include <iostream>

struct Point
{
    int x;
    int y;
};

void printPoint(Point pt)
{
    std::cout << "x: " << pt.x << " | y: " << pt.y << '\n';
}

int main()
{
    Point a;
    a.x = 10;
    a.y = 12;

    Point b {1, 2};    

    printPoint(a);
    printPoint(b);
}