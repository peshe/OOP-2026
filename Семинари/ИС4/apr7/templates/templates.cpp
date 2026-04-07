// templates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Date
{
    int year;
    int month;
    int day;
};

struct Person
{
    char name[30];
    char family[30];
    Date birthDate;
};

std::ostream& operator << (std::ostream& os, Person p)
{
    os << p.name << std::endl << p.family << std::endl << p.birthDate << std::endl;
    return os;
}

Person somePeople[] =
{
    {"Ivan", "Petrov", {1990, 5, 12}},
    {"Maria", "Ivanova", {1985, 11, 3}},
    {"Georgi", "Dimitrov", {1978, 2, 25}},
    {"Elena", "Nikolova", {1992, 7, 19}},
    {"Petar", "Georgiev", {1988, 9, 30}},
    {"Desislava", "Koleva", {1995, 1, 14}},
    {"Nikolay", "Stoyanov", {1983, 6, 8}},
    {"Teodora", "Petkova", {1991, 4, 27}},
    {"Hristo", "Todorov", {1975, 12, 5}},
    {"Simona", "Angelova", {2000, 3, 21}},
    {"Julius", "Ceaser", {-100, 7, 13}},
    {"Daniel", "Vasilev", {1987, 8, 16}},
    {"Kristina", "Ilieva", {1993, 10, 9}},
    {"Boris", "Zaharieev", {1981, 7, 2}},
    {"Radostina", "Yordanova", {1996, 5, 28}},
    {"Kaloyan", "Pavlov", {1989, 11, 11}},
    {"Antonia", "Stefanova", {1994, 2, 6}},
    {"Rosen", "Krastev", {1977, 9, 13}},
    {"Viktoria", "Hristova", {2001, 6, 17}},
    {"Jack", "Daniels", {1966, 12, 9}},
    {"Gergana", "Ruseva", {1997, 12, 22}},
    {"Plamen", "Marinov", {1986, 1, 29}},
    {"Yoana", "Dobreva", {1999, 8, 7}},
    {"Atanas", "Kirov", {1979, 4, 18}},
    {"Silvia", "Bozhilova", {1992, 10, 1}},
    {"Emil", "Ganchev", {1982, 7, 24}},
    {"Milena", "Taneva", {1995, 11, 15}},
    {"Kamen", "Radev", {1980, 2, 10}},
    {"Iveta", "Nenova", {1998, 5, 5}},
    {"Lyubomir", "Spasov", {1987, 9, 20}},
    {"Denitsa", "Velikova", {2002, 3, 12}},
    {"Duncan", "MacLeod", {1592, 1, 11}}
};

size_t somePeopleCount = sizeof(somePeople) / sizeof(somePeople[0]);

//struct Rational
//{
//    int numer;
//    int denom;
//};
//
//int min(int a, int b)
//{
//    if (a < b)
//        return a;
//    else
//        return b;
//}
//
//double min(double a, double b)
//{
//    if (a < b)
//        return a;
//    else
//        return b;
//}
//
//
//Rational min(Rational  a, Rational b)
//{
//    if (a < b)
//        return a;
//    else
//        return b;
//}


// Шаблон на функция (не е Шаблонна функция)
template <typename T> T min(T a, T b)
{
    std::cout << "min sizeof(T)==" << sizeof(T) << std::endl;

    if (a < b)
        return a;
    else
        return b;
}


template<typename T>
void printArray(std::ostream& os, T a[], size_t size)
{
    for (size_t k = 0; k < size; ++k)
    {
        std::cout << a[k];
        if (k + 1 < size) std::cout << ',';
    }
    std::cout << std::endl;
}


int a[] = { 4,5,6 };

//
int main()
{
    std::cout << min<int>(2, 3) << std::endl;  // явна специализация
    std::cout << min(5, 6) << std::endl;       // неявна специализация

    std::cout << min(5.1, 5.2) << std::endl;

    std::cout << min<double>(2, 3.14) << std::endl;

    printArray(std::cout, a, 3);
    printArray(std::cout, somePeople, somePeopleCount);
    
    return 0;
}

