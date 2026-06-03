#pragma once
#include <fstream>
#include "DataSource.h"

template <typename T>
class FileDataSource : public DataSource<T>
{
public:
    explicit FileDataSource(const std::string& filepath);
    FileDataSource(const FileDataSource& other);
    FileDataSource& operator=(const FileDataSource& other);
    ~FileDataSource() override = default;

    T Get() override;
    bool HasNext() const override;
    bool Reset() override;

    FileDataSource* Clone() override { return new FileDataSource(*this); }

private:
    std::string filepath;
    std::ifstream fileStream;
    int g = 0;
};

template<typename T>
FileDataSource<T>::FileDataSource(const std::string& filepath)
    : filepath(filepath)
    , fileStream(filepath)
{
}

template<typename T>
FileDataSource<T>::FileDataSource(const FileDataSource& other)
    : FileDataSource(other.filepath)
{
    fileStream.seekg(other.g);
    this->g = other.g;
}

template<typename T>
FileDataSource<T>& FileDataSource<T>::operator=(const FileDataSource& other)
{
    if (this == &other)
        return *this;

    FileDataSource temp(other);
    std::swap(this->filepath, temp.filepath);
    std::swap(this->g, temp.g);
    this->fileStream.open(filepath);
    this->fileStream.seekg(temp.g);

    return *this;
}

template<typename T>
T FileDataSource<T>::Get()
{
    T res;
    fileStream >> res;
    while (!fileStream.eof() && isspace(fileStream.peek()))
        fileStream.get();

    this->g = fileStream.tellg();
    return res;
}

template<typename T>
bool FileDataSource<T>::HasNext() const
{
    return fileStream && !fileStream.eof();
}

template<typename T>
bool FileDataSource<T>::Reset()
{
    fileStream.seekg(0);
    fileStream.clear();
    return true;
}
