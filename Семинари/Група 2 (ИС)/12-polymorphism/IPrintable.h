#pragma once

class IPrintable
{
public:
    virtual ~IPrintable() = default;  // Note: Always create a virtual destructor when working with polymorphism!
    virtual void Print() const = 0;
};