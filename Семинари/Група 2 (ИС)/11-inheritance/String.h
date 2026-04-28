#pragma once

class String
{
public:
    String() = default;

    String(const char* str);
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    static String ParseInt(unsigned size);

    void Set(const char* str);
    const char* Get() const { return this->data; }

    int Length() const;
    String& Append(const String& other);
    String& operator+=(const String& rhs);

    const char& operator[](unsigned index) const { return data[index]; }
    char&       operator[](unsigned index)       { return data[index]; }

    const char& At(unsigned index) const;
    char& At(unsigned index);

private:
    void Assign(const char* str, int len);
    void Clear();

    char* data = nullptr;
    int length = 0;

    static const int MAX_INT_NUM_LEN;
};

bool operator==(const String& lhs, const String& rhs);
String operator+(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& out, const String& str);
