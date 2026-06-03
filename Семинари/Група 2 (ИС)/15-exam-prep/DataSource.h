#pragma once
#include <vector>

template<typename T>
class DataSource
{
public:
    virtual ~DataSource() = default;
    virtual T Get() = 0;
    virtual std::vector<T> GetMultiple(int count);
    virtual bool HasNext() const = 0;
    virtual bool Reset() = 0;
    virtual DataSource* Clone() = 0;
    virtual T operator()();
    virtual DataSource& operator>>(T& rhs);
    virtual operator bool() const;
};

template<typename T>
std::vector<T> DataSource<T>::GetMultiple(int count)
{
    std::vector<T> res;
    for (int i = 0; i < count && HasNext(); i++)
        res.push_back(Get());
    return res;
}

template<typename T>
T DataSource<T>::operator()()
{
    return Get();
}

template<typename T>
DataSource<T>& DataSource<T>::operator>>(T& rhs)
{
    rhs = Get();
    return *this;
}

template<typename T>
DataSource<T>::operator bool() const
{
    return HasNext();
}
