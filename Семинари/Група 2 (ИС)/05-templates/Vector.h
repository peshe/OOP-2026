#pragma once

#include <cstddef>

template<typename T>
class Vector
{
public:
    // Lifecycle (Rule of 3)


    void Add(const T& val);
    //void Add(T val);

    void Resize();

private:
    T* data = nullptr;
    size_t cnt = 0;
    size_t capacity = 0;
};

template<typename T>
void Vector<T>::Add(const T& val)
{
    if (cnt + 1 > capacity)
        Resize();

    data[cnt] = val;
    cnt++;
}


class Student
{
private:
    Vector<char*> subjects;
};

template<typename T>
class Child : public Vector<T>
{

};

struct Sth
{
    Child<int> asdf;
};