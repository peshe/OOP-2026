#include <iostream>

int sum(int num1, int num2);
int power(int num);

void printArr(const int* arr, int size);
void powerArr(int* arr, int size);
void divArr(int* arr, int size);

void mapArr(int* arr, int size, int (*operation)(int));

using IntFunc = int(int);
void mapArr2(int* arr, int size, IntFunc* fn);

// Изброен тип
enum class CardSuite // enum struct CardSuite е еквивалентно
{
    Clubs = 10,
    Hearts,  // = 11
    Spades = 200,
    Diamonds,  // = 201
    SthElse = 11,  // и Hearts и SthElse имат числена стойност 11 (може да е ползено понякога)
};

void printSuite(CardSuite suite);


int main()
{
    ///
    /// Указатели и масиви
    ///
    int num = 5;
    int* pNum = &num;
    char ch = 'a';
    char* pCh = &ch;
    std::cout << pNum << '\n';  // 0x... - адреса на num
    std::cout << pCh << '\n';   // a...  - char* има различно поведение при принтене

    std::cout << &pNum << '\n';  // 0x... - адреса на pNum
    // Както всяка друга променлива, указателите (освен че имат стойност, която е адрес)
    // те самите също имат адрес, тъй като все пак стоят някъде в паметта.

    int arr[] = {1,2,3};  // arr всъщност е адрес сочещ към началото на масива
    int* arr2 = arr;

    // std::cout << arr2[-7] << '\n';  // Undefined behaviour!
    // std::cout << arr2[10] << '\n';  // Undefined behaviour!

    // arr2[i] е еквивалентно на *(arr2 + i)
    std::cout << *(arr + 1) << '\n';  // 2
    std::cout << arr[1] << '\n';  // 2

    ///
    /// Динамична памет
    ///

    // new int(5) -- Задели памет за едно цяло число и запиши стойността 5 на това място

    // new (std::nothrow) int[X] -- Опитай да заделиш последователна памет за X цели числа,
    //                           -- ако не успееш - върни nullptr

    // Работата с динамична памет се състои от 4 важни стъпки
    int size = 10;  // Може потребителя да избере размера, например чрез std::cin
    int* pArr = new (std::nothrow) int[size];  // Стъпка 1. Поискване на памет
    if (!pArr)  // pNum != nullptr  --  не успях да заделя памет
    {
        // Стъпка 2. Проверка дали паметта е получена ^^^
        std::cout << "Couldn't allocate memory, exiting...\n";
        return 1;  // Прекратяваме програмата с код, различен от 0
    }

    // Стъпка 3. Ползваме паметта
    for (int i = 0; i < size; i++)
        pArr[i] = i * 2;

    printArr(pArr, size);
    std::cout << '\n';

    powerArr(pArr, size);

    printArr(pArr, size);
    std::cout << '\n';

    // Стъпка 4. Изтриваме паметта  -- new int(5) => delete, new int[5] => delete[]
    delete[] pArr;

    ///
    /// Указатели към функции (Function pointers)
    ///

    // Променлива от тип "указател към функция, която приема две цели числа и връща цяло число"
    int (*foo)(int number1, int number2);
    int (*bar)(int, int);  // -- имената на параметрите не са задължителни и не променят изпълнението на кода

    // Указател към функцията sum
    int (*pSumFn)(int number1, int number2) = sum;  // &sum
    std::cout << pSumFn << '\n';  // 0x...
    std::cout << sum(2, 5) << '\n';  // 7
    std::cout << pSumFn(2, 5) << '\n';  // 7

    // Дефинира нов тип DoubleIntFn - функция която приема две цели числа и връща цяло число
    using DoubleIntFn = int(int, int);
    DoubleIntFn* pSumFn2 = &sum;  // -- указател към (функция от тип) DoubleIntFn ^^^
    std::cout << pSumFn2(2,3);

    const int size3 = 5;
    int arr3[] = {1,2,3,4,5};
    mapArr(arr3, size3, power);  // Прилага функцията power върху всеки един от елементите на arr3
    printArr(arr3, size3);
    std::cout << '\n';

    mapArr(arr3, size3, [](int num){ return num * 5; });
    printArr(arr3, size3);
    std::cout << '\n';

    //   [](int num){ return num * 5; }
    // -- Анонимна фунцкия (lambda function), която приема цяло число и връща числото умножено по 5
    // Забележка: За анонимните функции може да си говорим по-късно в курса, ако ви е интересно.

    ///
    /// Изброен тип (Enum)
    ///
    // int asdf = CardSuite::Diamonds;  -- компилационна грешка
    int asdf = static_cast<int>(CardSuite::Diamonds);
    CardSuite suite = CardSuite::Diamonds;
    CardSuite suite2 = static_cast<CardSuite>(10);
    std::cout << static_cast<int>(suite) << '\n';  // 201
    std::cout << static_cast<int>(suite2) << '\n'; // 10

    printSuite(suite);
    std::cout << '\n';
    printSuite(suite2);

    return 0;
}


void mapArr(int* arr, int size, int (*operation)(int))
{
    for (int i = 0; i < size; i++)
        arr[i] = operation(arr[i]);
}

void mapArr2(int *arr, int size, IntFunc* fn)
{
    for (int i = 0; i < size; i++)
        arr[i] = fn(arr[i]);
}

int power(int num)
{
    return num * num;
}

void printArr(const int* arr, int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ' ';
}

int sum(int num1, int num2)
{
    return num1 + num2;
}

void powerArr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = arr[i] * arr[i];
}

void divArr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = arr[i] / 2;
}

void printSuite(CardSuite suite)
{
    switch (suite)
    {
        case CardSuite::Clubs:
            std::cout << "Clubs";
            break;
        case CardSuite::Hearts:
            std::cout << "Hearts";
            break;
        case CardSuite::Spades:
            std::cout << "Spades";
            break;
        case CardSuite::Diamonds:
            std::cout << "Diamonds";
            break;
        default:
            std::cout << "Unknown suite";
            break;
    }
}
