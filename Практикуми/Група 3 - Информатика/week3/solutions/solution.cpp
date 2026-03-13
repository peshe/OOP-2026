#include <fstream>
#include <new>
#include <cstring>
#include <iostream>

struct File {
    std::fstream file;
    char filename[256];
};

const char* rootFilePath(){
    return "/";
}

const char* baseFilePath(){
    return "";
}

char* strcat2(const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr) {
        return nullptr;
    }
    size_t len1 = std::strlen(str1);
    size_t len2 = std::strlen(str2);
    char* result = new (std::nothrow) char[len1 + len2 + 1];
    if (!result) {
        return nullptr;
    }
    std::strncpy(result, str1, len1);
    std::strcat(result, str2);
    
    return result;
}

char* addFolder(const char* path, const char* directory) {
    if (directory == nullptr || path == nullptr) {
        return nullptr;
    }
    char* res = strcat2(path, directory);
    if (res == nullptr) {
        return nullptr;
    }
    return res;
}

char* addFile(const char* path, const char* filename) {
    if (filename == nullptr || path == nullptr) {
        return nullptr;
    }
    char* res = strcat2(path, filename);
    if (res == nullptr) {
        return nullptr;
    }
    return res;
}


File* createFile(const char* filename, bool append=false, bool readonly=false, bool writeonly=false, bool readwrite=true) {
    File* f = new (std::nothrow) File;    
    int flag = 0;

    if (append == true) {
        flag |= std::ios::app;
    } else if (readonly == true) {
        flag |= std::ios::in;
    } else if (writeonly == true) {
        flag |= std::ios::out;
    } else if (readwrite == true) {
        flag |= std::ios::in | std::ios::out;
    }

    if (f) {
        if (strlen(filename) >= 256) {
            delete f;
            return nullptr;
        }
        std::strncpy(f->filename, filename, 255);
        f->filename[255] = '\0';
        f->file.open(filename, flag);
        if (!f->file.is_open()) {
            delete f;
            return nullptr;
        }
    }
    return f;
}

void deleteFile(File*& f) {
    if (f) {
        f->file.close();
        delete f;
        f=nullptr;
    }
}

const char* getFileName(File* f) {
    if (!f) {
        return nullptr;
    }
    return f->filename;
}

char* readFile(File* f, size_t size) {
    if (!f || !f->file.is_open()) {
        return nullptr;
    }
    
    char* buffer = new (std::nothrow) char[size + 1];
    if (!buffer) {
        return nullptr;
    }
    
    f->file.read(buffer, size);
    if (!f->file) {
        delete[] buffer;
        return nullptr;
    }
    buffer[size] = '\0';
    return buffer;
}

int writeFile(File* f, const char* data, size_t size) {
    if (!f || !f->file.is_open()) {
        return -1;
    }
    
    f->file << data;
    if (f->file.bad() || f->file.fail()) {
        return -1;
    }
    return 0;
}

void gotoStart(File* f) {
    if (f && f->file.is_open()) {
        f->file.seekp(0);
        f->file.seekg(0);
    }
}

char* readLine(File* f) {
    if (!f || !f->file.is_open()) {
        return nullptr;
    }
    char a;
    char* buffer = new (std::nothrow) char[1024];
    if (!buffer) {
        return nullptr;
    }
    while(f->file.get(a) && !f->file.eof() && a != '\n') {
        size_t len = std::strlen(buffer);
        if (len + 1 >= 1024) {
            char* newBuffer = new (std::nothrow) char[len * 2 + 1];
            if (!newBuffer) {
                delete[] buffer;
                return nullptr;
            }
            std::strncpy(newBuffer, buffer, len + 1);
            
            delete[] buffer;
            buffer = newBuffer;
        }
        buffer[len] = a;
        buffer[len + 1] = '\0';
    }
    return buffer;
}

bool isFileEmpty(File* f) {
    if (!f || !f->file.is_open()) {
        return true;
    }
    f->file.seekg(0, std::ios::end);
    bool res = (f->file.tellg() == 0);
    gotoStart(f);
    return res;
}



int main(){
    File* f = createFile(addFile(baseFilePath(), "base.txt"), false, false, false, true);
    if (f == nullptr) {
        std::cerr << "Failed to create file." << std::endl;
        return 1;
    }
    int writeResult = writeFile(f, "Hello, World!\n", 14);
    if (writeResult) {
        std::cerr << "Failed to write to file." << std::endl;
        deleteFile(f);
        return 1;
    }
    writeResult = writeFile(f, "Hello, World2!\n", 15);
    if (writeResult) {
        std::cerr << "Failed to write to file." << std::endl;
        deleteFile(f);
        return 1;
    }
    writeResult = writeFile(f, "Hello, World3!\n", 15);
    if (writeResult) {
        std::cerr << "Failed to write to file." << std::endl;
        deleteFile(f);
        return 1;
    }
    gotoStart(f);
    char* data = readFile(f, 14);
    std::cout << data << std::endl;
    delete[] data;
    gotoStart(f);
    char* line = readLine(f);
    std::cout << line << std::endl;
    delete[] line;
    char* line2 = readLine(f);
    std::cout << line2 << std::endl;
    delete[] line2;

    deleteFile(f);
}
