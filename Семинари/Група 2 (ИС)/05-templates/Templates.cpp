#include <iostream>
#include "Utility.h"
#include "MoreAboutTemplates.h"

template<typename T>
T* filter(const T* arr, int size, bool (*pred)(const T&), int& outNewSize);

// Декларация на нов шаблонен тип - Predicate, който репрезентира
// функция, която приема const референция към шаблонен тип и връща bool
template<typename T>
using Predicate = bool(const T&);

template<typename T>
T* filter2(const T* arr, int size, Predicate<T>* pred, int& outNewSize);

// Шаблонна структура
// Забележка: Типовете Test<int>, Test<char>, и т.н. са напълно РАЗЛИЧНИ типове, РАЗЛИЧНИ структури
template<typename T>
struct Test
{
    T var;
};

// Тук `= int` и `= DataType` са стойности по подразбиране за двата шаблонни типа
// т.е. ако не подадем DataType и DataType2, то ще се опита да използва int и int
template<typename DataType = int, typename DataType2 = DataType>
struct Coord
{
    DataType x = 0;
    DataType2 y = 0;
};

int main()
{
    std::cout << min(4, 5) << "\n";
    std::cout << min(4.3f, 4.1f) << "\n";
    std::cout << min("gosho", "abcd");  // Сравнява указатели?!

    // Oще за шаблоните...
    std::cout << fact(5) << "\n";
    std::cout << factorial<5>() << "\n";

    const int size = 10;
    Array<int, size> obj = {1,2,3};
    std::cout << obj.arr[2] << "\n";

    Coord<int, double> coord = { 2, 3.2 };
    std::cout << coord.x << ", " << coord.y << "\n";

    Coord<int, int> coord2 = {3, 5};
    Coord<> coord3 = {4, 6};  // Използва стойностите по подразбиране от по-горе (DataType = int, ...)

    // Грешка! Различни типове структури, не можем да ги присвоим една на друга!
    // Coord<double, int> coord3 = coord2;

    return 0;
}
