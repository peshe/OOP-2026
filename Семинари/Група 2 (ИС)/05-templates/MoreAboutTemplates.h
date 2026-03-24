#pragma once

// Смята факториел
unsigned fact(unsigned n)
{
    if (n == 0)
        return 1;

    return n * fact(n - 1);
}

// Нетипов шаблон - ще говорим повече за тях в края на курса
// Смята факториел по време на компилация!
template<unsigned N>
unsigned factorial()
{
    return N * factorial<N - 1>();
}

// Дъното на компилационната рекурсията задаваме чрез
// специализация на шаблона за стойност 0 на N
template<>
unsigned factorial<0>()
{
    return 1;
}

// Нетиповият шаблон Size е компилационна константа!
template<typename Type, unsigned Size>
struct Array
{
    Type arr[Size];
};
