#pragma once

#include <iosfwd>
#include "Device.h"

class MobileDevice : public Device
{
public:
    MobileDevice(const char* name, unsigned short batteryLevel);
    MobileDevice(unsigned id, const char* name, unsigned short batteryLevel);
    static MobileDevice* FromLogFile(std::ifstream& logFile);

    void Print() const override;
    void SaveToLog(std::ofstream& file) const override;
    const char* GetType() const override;
    MobileDevice* Clone() const override;

    void SetBatteryLevel(unsigned short newLevel);

    static const char* Identifier() { return "mobile"; }

private:
    unsigned short batteryLevel = 0;
};
