#include "String.h"

#include <cstring>

String::String(const char* str)
{
    copy(str);
}

String::String(const String& other)
{
    copy(other.data);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        clear();
        copy(other.data);
    }

    return *this;
}

String::~String()
{
    clear();
}

int String::Length() const
{
    return strlen(data);
}

void String::copy(const char* str)
{
    data = new char[strlen(str) + 1];
    strcpy(data, str);
}

void String::clear()
{
    delete[] data;
    data = nullptr;
}
