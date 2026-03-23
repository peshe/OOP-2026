#include <iostream>

template<typename T>
struct Point
{
    T x,y;
};


template <typename T>
void printArray(const T* array, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
        std::cout << array[i] << ", ";
    
    std::cout << array[size - 1] << '\n';
}

template <>
void printArray<char>(const char* array, size_t size)
{
    std::cout << '"';

    for (size_t i = 0; i < size - 1; i++)
        std::cout << array[i];
    
    std::cout << array[size - 1] << "\"\n";
}

// Not specialization - this is an overload on "printArray"
template <typename T>
void printArray(const Point<T>* points, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
        std::cout << points[i].x << ";" << points[i].y << ", ";
    
    std::cout << points[size - 1].x << ";" << points[size - 1].y << '\n';
}

int main()
{
    Point<int> pts[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    printArray(pts, 3);
}