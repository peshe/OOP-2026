#include <cstring>
#include <stdexcept>

#include "Utility.h"

void DynCopyStr(char*& dest, const char* src)
{
    if (src == nullptr)
        throw std::invalid_argument("Source string cannot be nullptr");

    dest = new char[strlen(src) + 1];
    strcpy(dest, src);
}
