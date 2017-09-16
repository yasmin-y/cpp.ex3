
#ifndef EX3_MATRIX_HPP
#define EX3_MATRIX_HPP
#include <vector>
#include <unordered_set>
#include "Complex.h"

template <typename T>

class Matrix
{
    std::size_t _rows, _cols;
    std::vector<T> _values;
public:

    using const_iterator = typename std::vector<T>::const_iterator;

    /**
     * default ctor
     */
    Matrix();

    /**
     * zeros ctor
     */
    Matrix(std::size_t rows, std::size_t cols);

    /**
     * copy ctor
     */
    Matrix(const Matrix &other);

    /**
     * move ctor
     */
    Matrix(Matrix&& other);

    /**
     * values ctor
     */
    Matrix(std::size_t rows, std::size_t cols, const std::vector<T> &cells);

    ~Matrix();

    /**
     * assignment operator
     * @param rhs
     * @return
     */
    Matrix& operator= (const Matrix & rhs);
    bool operator==(const Matrix &rhs) const;

    bool operator!=(const Matrix &rhs) const;

    Matrix& operator-(const Matrix &rhs);

    /**
     * non const
     * @param rows
     * @param cols
     * @return
     */
    T&operator()(std::size_t rows, std::size_t cols);

    /**
     * const
     * @param rows
     * @param cols
     * @return
     */
    T operator()(std::size_t rows, std::size_t cols) const;

    size_t rows() const;

    size_t cols() const;

    const_iterator begin() const;

    const_iterator end() const;

    Matrix trans() const;

    bool isSquareMatrix() const;
};

template <typename T>
Matrix<T>::Matrix ()
{
    _rows = 1;
    _cols = 1;
    _values.push_back((T)0);
}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols) : _values(rows*cols, 0)
{
}

template <typename T>
Matrix<T>::Matrix(const Matrix &other) : _rows(other._rows) , _cols(other._cols), _values(other._values)
{
}

template <typename T>
Matrix<T>::Matrix(Matrix &&other) : _rows(std::move(other._rows)) , _cols(std::move(other._cols)),
                                    _values(std::move(other._values))
{
}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, const std::vector<T> &cells) : _rows(rows) ,
                                                                                     _cols(cols),
                                                                                     _values(cells)
{

}

template <typename T>
Matrix<T>::~Matrix()
{
}

template <typename T>
bool Matrix<T>::operator==(const Matrix &rhs) const
{
    return _rows == rhs._rows &&
           _cols == rhs._cols &&
           _values == rhs._values;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix &rhs) const
{
    return !(rhs == *this);
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &rhs)
{
    _rows = rhs._rows;
    _cols = rhs._cols;
    _values = rhs._values;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-(const Matrix &rhs)
{


    Matrix<T> subMatrix(_rows, _cols);
    for (std::size_t i = 0; i < _values.size(); ++i)
    {
        subMatrix._values.at(i) = _values.at(i)-rhs._values.at(i);
    }
    return subMatrix;
}

template <typename T>
T &Matrix<T>::operator()(std::size_t rows, std::size_t cols)
{
    return _values.at((_cols*rows) + cols);
}

template <typename T>
T Matrix<T>::operator()(std::size_t rows, std::size_t cols) const
{
    return _values.at((_cols*rows) + cols);
}

template <typename T>
size_t Matrix<T>::rows() const
{
    return _rows;
}
template <typename T>
size_t Matrix<T>::cols() const
{
    return _cols;
}


template<typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) noexcept{
    for (std::size_t i = 0; i < matrix.rows(); ++i)
    {
        for (std::size_t j = 0; j < matrix.cols(); ++j)
        {
            os << matrix(i,j)<< "\t";
        }
        os << "\n";
    }
    return os;
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const
{
    return _values.begin();
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::end() const
{
    return _values.end();
}

template<typename T>
Matrix<T> Matrix<T>::trans() const
{
    Matrix<T> transMatrix(_cols, _rows);
    for (std::size_t i = 0; i < _rows; ++i)
    {
        for (std::size_t j = 0; j < _cols; ++j)
        {
            transMatrix(i,j) = (*this)(j,i);
        }
    }
    return transMatrix;
}

template <typename T>
bool Matrix<T>::isSquareMatrix() const
{
    return (_rows == _cols);
}

template <>
Matrix<Complex> Matrix<Complex>::trans() const
{
    Matrix<Complex> transMatrix(_cols, _rows);
    for (std::size_t i = 0; i < _rows; ++i)
    {
        for (std::size_t j = 0; j < _cols; ++j)
        {
            transMatrix(i,j) = _values.at((i*_cols) + j);
        }
    }

    for (int i = 0; i < _rows * _cols; ++i)
    {
        transMatrix._values.at(i).conj();
    }
    return transMatrix;

}

#endif //EX3_MATRIX_HPP
