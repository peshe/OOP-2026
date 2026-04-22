#pragma once

#include <iostream>

char* copy(const char* str);
char* readString(std::istream& is, char delimiter);
void skipWhiteSpaces(std::istream& is);