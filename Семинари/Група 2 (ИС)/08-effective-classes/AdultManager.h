#pragma once

#include "Adult.h"

class AdultManager
{
public:
    void RunConsole();

private:
    void PrintState() const;

    static void PrintHelp();

    static const int MAX_ADULTS = 64;
    Adult arr[MAX_ADULTS];
    int count = 0;
};
