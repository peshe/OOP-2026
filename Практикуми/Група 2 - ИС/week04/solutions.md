# Решения

### Задача 1
Преди да запишем числата, записваме броя им, за да може когато трябва да ги прочетем да знаем колко са и да заделим толкова памет, колкото ни трябва.
```cpp
#include <iostream>
#include <fstream>


int main() {
    int n;

    std::ofstream ofs("numbers.dat", std::ios::binary);

    if (!ofs.good()) {
        std::cout << "Cant open file!\n";
        return -1;
    }

    std::cin >> n;
    int* arr = new (std::nothrow) int[n];
    if (!arr) {
        std::cout << "bad alloc!\n";
        return -1;
    }

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    ofs.write((const char*)&n, sizeof(n));
    ofs.write((const char*)arr, n * sizeof(int));

    delete[] arr;
    ofs.close();
}
```
### Задача 2
Прочитаме n, заделяме памет, прочитаме числата. Стандартно :)
```cpp
#include <iostream>
#include <fstream>


int main() {
    std::ifstream ifs("numbers.dat", std::ios::binary);

    if (!ifs.good()) {
        std::cout << "Cant open file!\n";
        return -1;
    }

    int size;
    ifs.read((char*)&size, sizeof(size));

    int* arr = new (std::nothrow) int[size];
    if (!arr) {
        std::cout << "bad alloc!\n";
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        ifs.read((char*)&arr[i], sizeof(int));
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }

    delete[] arr;
    ifs.close();
}
```
### Задача 3
Тук отново първо записваме колко студента има, после записваме самите тях. При четене първо четем размера, заделяме памет и после прочитаме и студентите. Просто е, защото структурата ни е с фиксиран размер (нямаме динамично заделена памет).
```cpp
#include <iostream>
#include <fstream>


struct Student
{
    char name[32];
    unsigned year;
    float grade;
};

void readStudent(Student& st)
{
    std::cin >> st.name >> st.year >> st.grade;
}

void printStudent(const Student& st)
{
    std::cout << st.name << ' ' << st.year << ' ' << st.grade << '\n';
}

int main() {
    {
        int n;

        std::cin >> n;
        std::ofstream ofs("students.dat", std::ios::binary);
        if (!ofs)
        {
            std::cout << "cant open file";
            return -1;
        }
        Student* students = new Student[n];
        if (!students)
        {
            std::cout << "bad alloc";
            return -1;
        }
        for (int i = 0; i < n; i++)
        {
            readStudent(students[i]);
        }
        ofs.write((const char*)&n, sizeof(n));
        for (int i = 0; i < n; i++)
        {
            ofs.write((const char*)&students[i], sizeof(Student));
        }
        //ofs.write((const char*)students, n * sizeof(Student));    //or write everything at once


        delete[] students;
        ofs.close();
    }

    //-----------------------------------------------------//
    
    {
        int n;
        std::ifstream ifs("students.dat", std::ios::binary);
        if (!ifs)
        {
            std::cout << "cant open file";
            return -1;
        }
        ifs.read((char*)&n, sizeof(n));
        Student* loadedStudents = new Student[n];
        if (!loadedStudents)
        {
            std::cout << "bad alloc";
            return -1;
        }
        for (int i = 0; i < n; i++)
        {
            ifs.read((char*)&loadedStudents[i], sizeof(Student));
        }
        //ifs.read((char*)loadedStudents, n * sizeof(Student));     //or read everything at once
        for (int i = 0; i < n; i++)
        {
            printStudent(loadedStudents[i]);
        }

        delete[] loadedStudents;
        ifs.close();
    }
}
```
### Задача 4
4.1 Фокусът тук е на `getFileSize()` и `getNumCount()`.
```cpp
#include <iostream>
#include <fstream>

int getFileSize(std::ifstream& ifs)
{
    int currPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    int size = ifs.tellg();
    ifs.seekg(currPos);
    return size;
}

int getNumCount(std::ifstream& ifs)
{
    return getFileSize(ifs) / sizeof(int);
}

int main() {
    std::ifstream ifs("file.dat", std::ios::binary);

    if (!ifs.good()) {
        std::cout << "Cant open file!\n";
        return -1;
    }

    int size = getNumCount(ifs);

    int* arr = new (std::nothrow) int[size];
    if (!arr) {
        std::cout << "bad alloc!\n";
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        ifs.read((char*)&arr[i], sizeof(int));
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }

    delete[] arr;
    ifs.close();
}
```
4.2
```cpp
int getSum(int i, int j) {
    std::ifstream ifs("file.dat", std::ios::binary);

    if (!ifs.good()) {
        std::cout << "Cant open file!\n";
        return -1;
    }

    int size = getNumCount(ifs);

    if (i >= size || j >= size) {
        std::cout << "Out of bounds!\n";
        return -1;
    }

    int num1;
    int num2;

    //read at index i
    ifs.seekg(sizeof(int) * i);
    ifs.read((char*)&num1, sizeof(int));

    //read at index j
    ifs.seekg(sizeof(int) * j);
    ifs.read((char*)&num2, sizeof(int));

    ifs.close();

    return num1 + num2;
}
```
### Задача 5
По-голямата част от решението може да видите [тук](https://github.com/peshe/OOP-2026/tree/main/Семинари/Група%202%20(ИС)/04-file-streams--binary-files). Кодът е от семинара.