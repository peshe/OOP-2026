#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

#include "DesktopDevice.h"


DesktopDevice::DesktopDevice(const char* name, const char* url)
    : Device(name)
{
    SetUrl(url);
}

DesktopDevice::DesktopDevice(unsigned id, const char* name, const char* url)
    : Device(id, name)
{
    SetUrl(url);
}

DesktopDevice* DesktopDevice::FromLogFile(std::ifstream& logFile)
{
    const unsigned MAX_STR_SIZE = 1024;
    unsigned id;
    char name[MAX_STR_SIZE]{};
    char url[MAX_STR_SIZE]{};
    logFile >> id >> name >> url;
    if (logFile)
        return new DesktopDevice(id, name, url);

    return nullptr;
}

DesktopDevice::DesktopDevice(const DesktopDevice& other)
    : DesktopDevice(other.GetName(), other.url)
{
}

DesktopDevice::~DesktopDevice()
{
    delete[] url;
    url = nullptr;
}

void DesktopDevice::SetUrl(const char* newUrl)
{
    if (newUrl == nullptr || newUrl[0] == '\0')
        throw std::invalid_argument("URL must not be empty.");

    this->url = new char[strlen(newUrl) + 1];
    strcpy(this->url, newUrl);
}

void DesktopDevice::Print() const
{
    Device::Print();
    std::cout << " " << url;
}

void DesktopDevice::SaveToLog(std::ofstream& file) const
{
    Device::SaveToLog(file);
    file << " " << url;
}

const char* DesktopDevice::GetType() const
{
    return DesktopDevice::Identifier();
}

DesktopDevice* DesktopDevice::Clone() const
{
    return new DesktopDevice(*this);
}
