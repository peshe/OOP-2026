#include <iostream>
#include <fstream>
#include <stdexcept>

#include "MobileDevice.h"

MobileDevice::MobileDevice(const char* name, unsigned short batteryLevel)
    : Device(name)
{
    SetBatteryLevel(batteryLevel);
}

MobileDevice::MobileDevice(unsigned id, const char* name, unsigned short batteryLevel)
    : Device(id, name)
{
    SetBatteryLevel(batteryLevel);
}

MobileDevice* MobileDevice::FromLogFile(std::ifstream& logFile)
{
    const unsigned MAX_STR_SIZE = 1024;
    unsigned id;
    char name[MAX_STR_SIZE]{};
    unsigned short battery;
    logFile >> id >> name >> battery;
    if (logFile)
        return new MobileDevice(id, name, battery);

    return nullptr;
}

void MobileDevice::Print() const
{
    Device::Print();
    std::cout << " " << batteryLevel;
}

const char* MobileDevice::GetType() const
{
    return MobileDevice::Identifier();
}

MobileDevice* MobileDevice::Clone() const
{
    return new MobileDevice(*this);
}

void MobileDevice::SetBatteryLevel(unsigned short newLevel)
{
    if (newLevel > 100)
        throw std::invalid_argument("Battery level must be in the range [0-100].");

    batteryLevel = newLevel;
}

void MobileDevice::SaveToLog(std::ofstream& file) const
{
    Device::SaveToLog(file);
    file << " " << batteryLevel;
}
