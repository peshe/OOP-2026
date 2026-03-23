#include <iostream>

template <typename T>
void printArray(const T* array, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
        std::cout << array[i] << ", ";
    
    std::cout << array[size - 1] << '\n';
}

template <>
void printArray(const char* array, size_t size)
{
    std::cout << '"';

    for (size_t i = 0; i < size - 1; i++)
        std::cout << array[i];
    
    std::cout << array[size - 1] << "\"\n";
}

int main()
{
    int arr[5] {1,2,3,4,5};

    char str[6] = "Hello";

    printArray(str, 5);
    printArray(arr, 5);
}