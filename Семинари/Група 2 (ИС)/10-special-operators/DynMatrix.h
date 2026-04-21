#pragma once
#include <utility>

template <typename DataType>
class DynMatrix
{
public:
    DynMatrix(unsigned rows, unsigned cols);
    DynMatrix(const DynMatrix& other);
    DynMatrix& operator=(const DynMatrix& other);
    ~DynMatrix();

    const DataType* operator[](unsigned row) const { return mat[row]; }
    DataType*       operator[](unsigned row)       { return mat[row]; }

    const DataType& At(unsigned row, unsigned col) const;
    DataType&       At(unsigned row, unsigned col);

    unsigned Rows() const { return rows; }
    unsigned Cols() const { return cols; }

private:
    void ValidatePos(unsigned row, unsigned col) const;
    void Allocate();
    void Clear();

    DataType** mat = nullptr;
    unsigned rows = 0;
    unsigned cols = 0;
};

template<typename DataType>
DynMatrix<DataType>::DynMatrix(unsigned rows, unsigned cols)
    : rows(rows)
    , cols(cols)
{
    Allocate();
}

template<typename DataType>
DynMatrix<DataType>::DynMatrix(const DynMatrix& other)
    : DynMatrix(other.rows, other.cols)  // Allocates using the constructor above
{
    try
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                mat[i][j] = other.mat[i][j];  // operator= may throw for some types
    }
    catch (...)
    {
        Clear();
        throw;
    }
}

template<typename DataType>
DynMatrix<DataType>& DynMatrix<DataType>::operator=(const DynMatrix& other)
{
    if (this != &other)
    {
        DynMatrix temp(other);  // can throw, but that's OK
        std::swap(mat, temp.mat);
        std::swap(rows, temp.rows);
        std::swap(cols, temp.cols);
    }
    return *this;
}

template<typename DataType>
DynMatrix<DataType>::~DynMatrix()
{
    Clear();
}

template<typename DataType>
const DataType& DynMatrix<DataType>::At(unsigned row, unsigned col) const
{
    ValidatePos(row, col);
    return mat[row][col];
}

template<typename DataType>
DataType& DynMatrix<DataType>::At(unsigned row, unsigned col)
{
    ValidatePos(row, col);
    return mat[row][col];
}

template<typename DataType>
void DynMatrix<DataType>::ValidatePos(unsigned row, unsigned col) const
{
    if (!mat || row >= rows || col >= cols)
        throw std::out_of_range("Out of range");
}

template<typename DataType>
void DynMatrix<DataType>::Allocate()
{
    mat = new DataType*[rows]{};
    try
    {
        for (int i = 0; i < rows; ++i)
            mat[i] = new DataType[cols]{};
    }
    catch (...)
    {
        Clear();
        throw;
    }
}

template<typename DataType>
void DynMatrix<DataType>::Clear()
{
    for (int i = 0; i < rows; ++i)
        delete[] mat[i];
    delete[] mat;
    mat = nullptr;
}
