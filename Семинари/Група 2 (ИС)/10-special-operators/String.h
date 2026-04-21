#pragma once

class String
{
public:
    String() = default;

    // Lifetime
    String(const char* str);
    String(const String& other);
    String& operator=(String other);
    ~String();

    // Static factory method
    static String ParseInt(unsigned size);

    void Set(const char* str);
    const char* Get() const { return this->data; }

    int Length() const;
    String& Append(const String& other);

    // Append one string to another
    String& operator+=(const String& rhs);

    // const char& operator[](unsigned index) const;
    const char& operator[](unsigned index) const { return data[index]; }
    char&       operator[](unsigned index)       { return data[index]; }

    const char& At(unsigned index) const;
    char& At(unsigned index);


    // char operator()(unsigned index);

private:
    void Assign(const char* str, int len);
    void Clear();
    void Swap(String& other);

    char* data = nullptr;
    int length = 0;

    static const int MAX_INT_NUM_LEN;
};

String operator+(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& out, const String& str);

bool operator==(const String& lhs, const String& rhs);
