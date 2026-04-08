#include <cstring>  // for strncpy and strlen
#include <cmath>    // for log10
#include <utility>  // for std::swap

#include "String.h"

const int String::MAX_INT_NUM_LEN = 32;

String::String(const char* str)
{
    Set(str);
}

String String::ParseInt(unsigned size)
{
    // log10 is slow do NOT do this!!!
    const int length = log10(size) + 1;
    char str[MAX_INT_NUM_LEN] = {'\0'};
    for (int i = length - 1; size > 0; size /= 10, i--)
        str[i] = (size % 10) + '0';

    // str is char*, but we return String from this function, here
    // the program uses our implicit constructor String(const char* str)
    // to create the String value for the result
    return str;
}

String::String(const String& other)
{
    Assign(other.data, other.length);
}

// Passing by value (String other), means we're copying the passed object with the copy constructor.
// The copy constructor can throw a bad_alloc (not enough memory) exception, and that is fine.
//
// Here we have Strong Exception Safety Guarantee, because even
// if the copy throws, our original object (this) is unchanged.
String& String::operator=(String other)
{
    Swap(other);  // noexcept (doesn't throw exceptions)
    return *this; // noexcept (doesn't throw exceptions)
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

    // Copy existing data if it exists
    if (data)
        strcpy(newData, data);

    // Concatenate the rest
    strcat(newData + length, other.data);

    // Clean up old memory
    Clear();

    // Update members
    data = newData;
    length = newLength;

    return *this;
}

String& String::operator+=(const String& rhs)
{
    return Append(rhs);
}

String String::operator+(const String& rhs) const
{
    // `this` is the left hand side operand
    String res = *this;  // Copy `this`
    return res += rhs;   // Append rhs to the result
    // Note: This is not an efficient way to write this operator
}

void String::Assign(const char* str, int len)
{
    length = len;

    if (str == nullptr)
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

void String::Swap(String& other)
{
    // To use std::swap we need the <utility> header
    std::swap(data, other.data);
    std::swap(length, other.length);
}
