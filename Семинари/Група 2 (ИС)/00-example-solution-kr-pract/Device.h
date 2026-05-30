#pragma once

#include <iosfwd>

class Device
{
public:
    explicit Device(const char* name);
    Device(unsigned id, const char* name);

    Device(const Device& other);
    Device& operator=(const Device& other) = delete;
    virtual ~Device();

    void SetName(const char* newName);
    const char* GetName() const { return name; }
    unsigned GetId() const { return id; }
    virtual void Print() const;
    virtual const char* GetType() const = 0;
    virtual Device* Clone() const = 0;

    virtual void SaveToLog(std::ofstream& file) const;

private:
    static unsigned nextId;

    const unsigned id = 0;
    char* name = nullptr;
};
