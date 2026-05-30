#pragma once

#include <iosfwd>
#include "Device.h"

class DeviceFactory
{
public:
    static Device* CreateFromLog(std::ifstream& in);
};
