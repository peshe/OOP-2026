#pragma once
#include "DataSource.h"

template <typename T>
class ArrayDataSource : public DataSource<T>
{
public:
    ArrayDataSource(const std::vector<T>& source) : arr(source) {}
    ~ArrayDataSource() override = default;

    T Get() override;
    bool HasNext() const override;
    bool Reset() override;

    // TODO: operators
    ArrayDataSource& operator+=(const T& elem);
    ArrayDataSource operator+(const T& elem);

    ArrayDataSource& operator--();
    ArrayDataSource operator--(int);

    ArrayDataSource* Clone() override { return new ArrayDataSource(*this); }

private:
    std::vector<T> arr;
    int index = 0;
};

template<typename T>
T ArrayDataSource<T>::Get()
{
    return arr[index++];
}

template<typename T>
bool ArrayDataSource<T>::HasNext() const
{
    return index < arr.size();
}

template<typename T>
bool ArrayDataSource<T>::Reset()
{
    index = 0;
    return true;
}
