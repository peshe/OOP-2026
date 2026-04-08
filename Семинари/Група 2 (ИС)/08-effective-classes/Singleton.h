#pragma once

class Singleton
{
public:
    static Singleton& GetInstance()
    {
        // A variable created once, destroyed at program end
        static Singleton instance;
        return instance;
    }

    // Publicly declared copy ctor and copy assignment operator as deleted,
    // means that users of our class can't copy an object of this class
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;

    int GetGlobalState() const { return someGlobalState; }
    void DoSth()
    {
        someGlobalState++;
    }

private:
    // private constructor, means only code inside
    // our class can create objects of our class
    Singleton() = default;

    int someGlobalState = 42;
};

