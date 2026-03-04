#include <fstream>
#include <iostream>

void demoFileSize() {
    // Open in binary mode to ensure accurate byte counting
    std::ifstream file("image.png", std::ios::binary);

    if (!file) return;

    // Move the 'get' pointer to the end of the file
    // (0 bytes offset from the end)
    file.seekg(0, std::ios::end);

    // Ask the cursor for its current position
    // (since we're at the end, this value equals the total size in bytes)
    std::streampos size = file.tellg();

    std::cout << "File size: " << size << " bytes" << std::endl;

    // Move back to the beginning if we intend to start reading
    file.seekg(0, std::ios::beg);
}