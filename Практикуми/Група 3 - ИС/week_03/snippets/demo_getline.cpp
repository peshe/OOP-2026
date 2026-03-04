#include <fstream>
#include <iostream>

void demoGetline() {
    std::ifstream file("users.txt");

    if (!file) return;

    constexpr int MAX_SIZE = 128;

    char buffer[MAX_SIZE];

    // Read until '\n' or until MAX_SIZE - 1 characters are reached
    while (file.getline(buffer, MAX_SIZE)) {
        std::cout << "Read line: " << buffer << std::endl;
    }

    // If the line was longer than MAX_SIZE, the stream will enter a fail state
    if (file.fail() && !file.eof()) {
        std::cout << "ERROR: Found a line longer than the buffer." << std::endl;

        // We must clear the flags to continue using the stream
        file.clear();
    }
}