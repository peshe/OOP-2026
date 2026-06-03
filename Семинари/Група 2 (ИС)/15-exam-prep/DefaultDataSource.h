#pragma once
#include "DataSource.h"

template <typename T>
class DefaultDataSource : public DataSource<T>
{
public:
    ~DefaultDataSource() override = default;

    T Get() override;
    bool HasNext() const override;
    bool Reset() override;

    DefaultDataSource* Clone() override { return new DefaultDataSource(*this); }
};

template<typename T>
T DefaultDataSource<T>::Get()
{
    return T{};
}

template<typename T>
bool DefaultDataSource<T>::HasNext() const
{
    return true;
}

template<typename T>
bool DefaultDataSource<T>::Reset()
{
    return true;
}
