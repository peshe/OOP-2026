#pragma once
#include "DataSource.h"

template<typename T, typename Generator>
class GeneratorDataSource : public DataSource<T>
{
public:
    GeneratorDataSource(const Generator& generator) : generator(generator) {}

    T Get() override;
    bool HasNext() const override;
    bool Reset() override;
    GeneratorDataSource* Clone() override { return new GeneratorDataSource(*this); }

private:
    Generator generator;
};

template<typename T, typename Generator>
T GeneratorDataSource<T, Generator>::Get()
{
    return generator();
}

template<typename T, typename Generator>
bool GeneratorDataSource<T, Generator>::HasNext() const
{
    return true;
}

template<typename T, typename Generator>
bool GeneratorDataSource<T, Generator>::Reset()
{
    return false;
}
