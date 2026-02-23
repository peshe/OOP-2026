## Задача 1.
```cpp
// Решение:
#include <iostream>

// Функция за събиране
int add(int a, int b)
{
    return a + b;
}

// Функция за умножение
int multiply(int a, int b)
{
    return a * b;
}

int main()
{
    // Деклариране на указател към функция
    int (*func_ptr)(int, int);

    int x = 5, y = 3;

    // Насочване към функцията за събиране и извикване
    func_ptr = add;
    std::cout << "Събиране: " << func_ptr(x, y) << std::endl;

    // Насочване към функцията за умножение и извикване
    func_ptr = multiply;
    std::cout << "Умножение: " << func_ptr(x, y) << std::endl;

    return 0;
}
```

## Задача 2.
```cpp
// Решение:
#include <iostream>

// Функция за намиране на сумата на елементите
int sum(int arr[], int n)
{
    int s = 0;
    for(int i = 0; i < n; ++i)
    {
        s += arr[i];
    }
    return s;
}

// Функция за намиране на средното аритметично
double average(int arr[], int n)
{
    if (n == 0)
    {
        return 0;
    }

    return (double)sum(arr, n) / n;
}

// Функция за намиране на максималния елемент
int max(int arr[], int n)
{
    if (n == 0)
    {
        return 0;
    }

    int m = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > m)
        {
            m = arr[i];
        }
    }

    return m;
}

// Функция, която приема указател към функция, връщаща int
int processInt(int arr[], int n, int (*func)(int[], int))
{
    return func(arr, n);
}

// Функция, която приема указател към функция, връщаща double
double processDouble(int arr[], int n, double (*func)(int[], int))
{
    return func(arr, n);
}

int main()
{
    int arr[] = {2, 7, 4, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Използване на processInt и processDouble с различни функции
    std::cout << "Сума: " << processInt(arr, n, sum) << std::endl;
    std::cout << "Средно: " << processDouble(arr, n, average) << std::endl;
    std::cout << "Максимум: " << processInt(arr, n, max) << std::endl;

    return 0;
}
```

## Задача 3.
```cpp
#include <iostream>

// Функция за проверка дали числото е четно
bool isEven(int x)
{
    return x % 2 == 0;
}

// Функция за проверка дали числото е нечетно
bool isOdd(int x)
{
    return x % 2 != 0;
}

// Глобална променлива за прага
int threshold;

// Функция за проверка дали числото е по-голямо от threshold
bool isGreaterThan(int x)
{
    return x > threshold;
}

// Функция за филтриране и отпечатване
void printFiltered(int arr[], int n, bool (*cond)(int))
{
    for (int i = 0; i < n; ++i)
    {
        if (cond(arr[i]))
        {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main()
{
    int arr[100], n, choice;
    std::cout << "Въведете брой елементи: ";
    std::cin >> n;
    std::cout << "Въведете елементите: ";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    std::cout << "Изберете условие:\n";
    std::cout << "1. Само четни числа\n";
    std::cout << "2. Само нечетни числа\n";
    std::cout << "3. Числа, по-големи от дадена стойност\n";
    std::cin >> choice;

    bool (*cond)(int) = nullptr;

    if (choice == 1)
    {
        cond = is_even;
    }
    else if (choice == 2)
    {
        cond = is_odd;
    }
    else if (choice == 3)
    {
        std::cout << "Въведете праговата стойност: ";
        std::cin >> threshold;
        cond = is_greater_than;
    }
    else
    {
        std::cout << "Невалиден избор!" << std::endl;
        return 1;
    }

    std::cout << "Резултат: ";
    printFiltered(arr, n, cond);

    return 0;
}
```

## Задача 4.
```cpp
#include <iostream>

enum Season { Spring = 1, Summer, Autumn, Winter };

int main()
{
    int choice;
    std::cout << "Въведете число от 1 до 4 (1=Пролет, 2=Лято, 3=Есен, 4=Зима): ";
    std::cin >> choice;

    Season season = static_cast<Season>(choice);

    switch (season)
    {
        case Spring:
            std::cout << "Пролет: Време е за разходки сред природата!" << std::endl;
            break;
        case Summer:
            std::cout << "Лято: Време е за плаж!" << std::endl;
            break;
        case Autumn:
            std::cout << "Есен: Листата падат от дърветата." << std::endl;
            break;
        case Winter:
            std::cout << "Зима: Идеално време за ски!" << std::endl;
            break;
        default:
            std::cout << "Невалиден избор!" << std::endl;
    }

    return 0;
}
```

## Задача 5.
```cpp
#include <iostream>

enum class TicketType { Standard = 1, Student, Senior, VIP };

// Функция за връщане на цената според типа билет
double getTicketPrice(TicketType type)
{
    switch (type)
    {
        case TicketType::Standard: return 20.0;
        case TicketType::Student:  return 10.0;
        case TicketType::Senior:   return 12.0;
        case TicketType::VIP:      return 50.0;
        default:                   return 0.0;
    }
}

// Функция за изчисляване на крайната сума
double calculateTotal(TicketType type, int count)
{
    return getTicketPrice(type) * count;
}

int main()
{
    int choice, count;
    std::cout << "Видове билети:\n";
    std::cout << "1. Стандартен\n";
    std::cout << "2. Студентски\n";
    std::cout << "3. Пенсионерски\n";
    std::cout << "4. VIP\n";
    std::cout << "Изберете тип билет (1-4): ";
    std::cin >> choice;

    if (choice < 1 || choice > 4)
    {
        std::cout << "Невалиден избор!" << std::endl;
        return 1;
    }

    std::cout << "Въведете брой билети: ";
    std::cin >> count;

    if (count <= 0)
    {
        std::cout << "Броят билети трябва да е положително число!" << std::endl;
        return 1;
    }

    TicketType type = static_cast<TicketType>(choice);
    double total = calculateTotal(type, count);

    std::cout << "Крайна сума: " << total << " лв." << std::endl;

    return 0;
}
```
