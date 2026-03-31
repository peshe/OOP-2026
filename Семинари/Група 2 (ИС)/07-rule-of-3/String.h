#pragma once

class String
{
public:
    // Makes sure our class has a default constructor,
    // generated with the default behaviour
    String() = default;

    // Parametrized constructor (conversion constructor)
    String(const char* str);

    // Copy constructor
    String(const String& other);

    // Assignment operator
    String& operator=(const String& other);

    // Destructor
    ~String();

    int Length() const;

private:
    void copy(const char* str);
    void clear();

    char* data = nullptr;
};
