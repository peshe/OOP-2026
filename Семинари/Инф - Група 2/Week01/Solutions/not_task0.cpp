#include <iostream>

void timesN(int &x, int n)
{
    x *= n;
}

void plusN(int &x, int n)
{
    x += n;
}

void print(int& x)
{
    std::cout << x << ' ';
}

void map(int* arr, int size, void (*mappingFunction)(int&))
{
    for (int i = 0; i < size; i++)
    {
        mappingFunction(arr[i]);
    }
}

void map(int* arr, int size, void (*mappingFunction)(int&, int), int n)
{
    for (int i = 0; i < size; i++)
    {
        mappingFunction(arr[i], n);
    }
}

int main()
{
    int arr[5] {1,2,3,4,5};

    map(arr, 5, timesN, 10);
    map(arr, 5, plusN, 1


    map(arr, 5, [](int& x){ x *= 10; });

    map(arr, 5, print);

    return 0;
}