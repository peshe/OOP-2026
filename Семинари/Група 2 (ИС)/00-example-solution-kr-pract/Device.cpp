#include <iostream>
#include <fstream>
#include <cstring>

#include "Device.h"

unsigned Device::nextId = 0;

Device::Device(const char* name)
    : Device(nextId, name)
{
}

Device::Device(unsigned id, const char* name)
    : id(id)
{
    if (nextId <= id)
        nextId = id + 1;

    SetName(name);
}

Device::Device(const Device& other)
    : Device(other.name)
{
}

Device::~Device()
{
    delete[] this->name;
    this->name = nullptr;
}

void Device::SetName(const char* newName)
{
    delete[] this->name;

    if (!newName)
    {
        this->name = nullptr;
        return;
    }

    this->name = new char[strlen(newName) + 1];
    strcpy(this->name, newName);
}

void Device::Print() const
{
    std::cout << id << " " << name;
}

void Device::SaveToLog(std::ofstream& file) const
{
    file << GetType() << " " << id << " " << name;
}
