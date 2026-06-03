#include <fstream>

#include "MobileDevice.h"
#include "DesktopDevice.h"

#include "DeviceFactory.h"

Device* DeviceFactory::CreateFromLog(std::ifstream& in)
{
    const unsigned TYPE_MAX_LEN = 32;
    char deviceType[TYPE_MAX_LEN]{};
    in >> deviceType;

    if (strcmp(deviceType, MobileDevice::Identifier()) == 0)
        return MobileDevice::FromLogFile(in);

    if (strcmp(deviceType, DesktopDevice::Identifier()) == 0)
        return DesktopDevice::FromLogFile(in);

    return nullptr;
}
