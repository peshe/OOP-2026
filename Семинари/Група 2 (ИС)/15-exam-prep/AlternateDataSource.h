#pragma once
#include "DataSource.h"

template <typename T>
class AlternateDataSource : public DataSource<T>
{
public:
    explicit AlternateDataSource(const std::vector<DataSource<T>*>& sources) : arr(sources) {}
    static AlternateDataSource TakeSources(const std::vector<DataSource<T>*>& sources) { return AlternateDataSource(sources); }
    AlternateDataSource(const AlternateDataSource& other);
    AlternateDataSource& operator=(const AlternateDataSource& other);
    ~AlternateDataSource() override;

    T Get() override;
    bool HasNext() const override;
    bool Reset() override;
    AlternateDataSource* Clone() override { return new AlternateDataSource(*this); }

private:
    int BoundNext(int idx) const;
    void MoveToNextSourceIndex();

private:
    std::vector<DataSource<T>*> arr;
    int currSource = 0;
};

template<typename T>
AlternateDataSource<T>::AlternateDataSource(const AlternateDataSource& other)
{
    for (int i = 0; i < other.arr.size(); i++)
        arr.push_back(other.arr[i]->Clone());
    currSource = other.currSource;
}

template<typename T>
AlternateDataSource<T>& AlternateDataSource<T>::operator=(const AlternateDataSource& other)
{
    if (this == &other)
        return *this;

    AlternateDataSource temp(other);
    std::swap(this->arr, temp.arr);
    std::swap(this->currSource, temp.currSource);
    return *this;
}

template<typename T>
AlternateDataSource<T>::~AlternateDataSource()
{
    for (int i = 0; i < arr.size(); i++)
        delete arr[i];
    arr.clear();
}

template<typename T>
T AlternateDataSource<T>::Get()
{
    T res = arr[currSource]->Get();
    MoveToNextSourceIndex();
    return res;
}

template<typename T>
bool AlternateDataSource<T>::HasNext() const
{
    return arr[currSource]->HasNext();
}

template<typename T>
bool AlternateDataSource<T>::Reset()
{
    for (int i = 0; i < arr.size(); i++)
        if (!arr[i]->Reset())
            return false;

    return true;
}

template<typename T>
int AlternateDataSource<T>::BoundNext(int idx) const
{
    if (arr.size() == 0)
        return 0;

    return (idx + 1) % arr.size();
}

template<typename T>
void AlternateDataSource<T>::MoveToNextSourceIndex()
{
    int lastSource = currSource;
    for (currSource = BoundNext(currSource); currSource != lastSource; currSource = BoundNext(currSource))
        if (arr[currSource]->HasNext())
            break;
}
