#include <iostream>
#include <new>

void printCity(int** city, int length, int width) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            // Принципно не може да ползвате to_string, но го правя само за да може да се принтира хубаво
            //                      ако нямахте право да го ползвате трябваше да измислите как да изведете, позитивно число като символен низ, което не е безкрайно сложно. :)
            std::cout << ((city[i][j]==0)?"_":std::to_string(city[i][j])) << "\t";
        }
        std::cout << std::endl;
    }
}

void populateCity(int** city, int length, int width) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            int val = rand()%200;
            // 50% da e putishta gore dolu
            city[i][j] = (val < 100)?0:val-100;
        }
    }
}
int ** createCity(int length, int width) {
    int** city = new (std::nothrow)int*[length];
    if (city == nullptr) {
        return nullptr;
    }
    for (int i = 0; i < length; ++i) {
        city[i] = new (std::nothrow)int[width];
        if (city[i] == nullptr) {
            for (int j = 0; j < i; ++j) {
                delete[] city[j];
            }
            delete[] city;
            return nullptr;
        }
    }
    return city;
}

int main() {
    int length, width;
    std::cin >> length >> width;
    int** city = createCity(length, width);
    if (city == nullptr) {
        std::cout << "Failed to create city" << std::endl;
        return 1;
    }
    populateCity(city, length, width);
    printCity(city, length, width);
    for (int i = 0; i < length; ++i) {
        delete[] city[i];
    }
    delete[] city;
    return 0;
}
