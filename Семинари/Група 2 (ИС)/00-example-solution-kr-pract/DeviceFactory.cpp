#include <fstream>

#include "MobileDevice.h"
#include "DesktopDevice.h"

#include "DeviceFactory.h"

Device* DeviceFactory::CreateFromLog(std::ifstream& in)
{
    const unsigned TYPE_MAX_LEN = 32;
    char deviceType[TYPE_MAX_LEN]{};
    in >> deviceType;
    if (strcmp(deviceType, "mobile") == 0)
        return MobileDevice::FromLogFile(in);

    if (strcmp(deviceType, "desktop") == 0)
        return DesktopDevice::FromLogFile(in);

    return nullptr;
}
