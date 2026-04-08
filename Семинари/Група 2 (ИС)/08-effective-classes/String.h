#pragma once

class String
{
public:
    // Makes sure our class has a default constructor, generated
    // with the default behaviour so we can make "empty" strings
    String() = default;

    // Lifetime
    String(const char* str);
    String(const String& other);
    String& operator=(String other);
    ~String();

    // If we have a single argument constructor that isn't obvious or expected to naturally convert
    // that argument into our class, then we can use the `explicit` keyword to enforce the user
    // to explicitly state that they are using that constructor in code, e.g.: String a = String(3);
    //   explicit String(int size);

    // Static method that constructs a String
    static String ParseInt(unsigned size);

    void Set(const char* str);
    const char* Get() const { return this->data; }

    int Length() const;

private:
    void Assign(const char* str, int len);
    void Clear();
    void Swap(String& other);

    char* data = nullptr;
    int length = 0;

    static const int MAX_INT_NUM_LEN;
};
