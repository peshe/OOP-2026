#include <fstream>
#include <iostream>

int countCharInFile(const char* filename, char target) {
    std::ifstream file(filename);

    if (!file) return -1;

    char ch;
    int count = 0;

    // Ensures we don't skip whitespaces and newlines
    while (file.get(ch)) {
        if (ch == target) ++count;
    }

    return count;
}