#pragma once
#include <iosfwd>
#include "Device.h"

class DesktopDevice : public Device
{
public:
    DesktopDevice(const char* name, const char* url);
    DesktopDevice(unsigned id, const char* name, const char* url);
    static DesktopDevice* FromLogFile(std::ifstream& logFile);

    DesktopDevice(const DesktopDevice& other);
    ~DesktopDevice() override;

    void SetUrl(const char* newUrl);
    const char* GetUrl() const { return url; }

    void Print() const override;
    void SaveToLog(std::ofstream& file) const override;
    const char* GetType() const override;
    DesktopDevice* Clone() const override;

    static const char* Identifier() { return "desktop"; }

private:
    char* url = nullptr;
};
