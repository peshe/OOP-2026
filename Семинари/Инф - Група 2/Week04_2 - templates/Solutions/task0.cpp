#include <iostream>
#include <fstream>

template <typename T>
bool writeToTextFile(const char* filename, T data)
{
    std::ofstream out(filename);

    if (!out.is_open())
    {
        return false;
    }

    out << data;

    return true;
}

template <typename T>
bool writeToBinaryFile(const char* filename, const T& data)
{
    std::ofstream out(filename, std::ios::binary);

    if (!out.is_open())
    {
        return false;
    }

    out.write(reinterpret_cast<const char*>(&data), sizeof(T));

    return true;
}

struct Point
{
    int x, y;
};

int main()
{
    Point pt {1,2};
    std::cout << writeToBinaryFile<Point>("file.bin", Point{5, 6});
}