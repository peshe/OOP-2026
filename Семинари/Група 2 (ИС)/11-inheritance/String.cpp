#include <iostream>   // for std::ostream
#include <cstring>    // for strncpy and strlen
#include <cmath>      // for log10
#include <utility>    // for std::swap
#include <stdexcept>  // for std::out_of_range

#include "String.h"

const int String::MAX_INT_NUM_LEN = 32;

String::String(const char* str)
{
    Set(str);
}

String String::ParseInt(unsigned size)
{
    // log10 is slow do NOT do this!!! This is just an example
    const int length = log10(size) + 1;
    char str[MAX_INT_NUM_LEN] = {'\0'};
    for (int i = length - 1; size > 0; size /= 10, i--)
        str[i] = (size % 10) + '0';

    return str;
}

String::String(const String& other)
{
    Assign(other.data, other.length);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        String temp(other);
        std::swap(data, temp.data);
        std::swap(length, temp.length);
    }
    return *this;
}

String::~String()
{
    Clear();
}

void String::Set(const char* str)
{
    Clear();
    const int len = str ? strlen(str) : 0;
    Assign(str, len);
}

int String::Length() const
{
    return length;
}

String& String::Append(const String& other)
{
    if (other.length == 0)
        return *this;

    const int newLength = length + other.length;
    char* newData = new char[newLength + 1];

    if (data)
        strcpy(newData, data);
    strcat(newData + length, other.data);

    Clear();
    data = newData;
    length = newLength;

    return *this;
}

String& String::operator+=(const String& rhs)
{
    return Append(rhs);
}

const char& String::At(unsigned index) const {
    if (index >= length)
        throw std::out_of_range("index out of range");
    return (*this)[index];
}

char& String::At(unsigned index) {
    const char& res = static_cast<const String*>(this)->At(index);
    return const_cast<char&>(res);
}

void String::Assign(const char* str, int len)
{
    length = len;

    if (str == nullptr || len == 0)
    {
        data = nullptr;
        return;
    }

    data = new char[length + 1];
    strncpy(data, str, length);
    data[length + 1] = '\0';
}

void String::Clear()
{
    delete[] data;
    data = nullptr;
}

String operator+(const String& lhs, const String& rhs)
{
    String res(lhs);
    res += rhs;
    return res;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
    if (str.Get())
        return out << str.Get();
    return out;
}

bool operator==(const String& lhs, const String& rhs)
{
    if (lhs.Length() != rhs.Length())
        return false;

    return strncmp(lhs.Get(), rhs.Get(), lhs.Length()) == 0;
}
