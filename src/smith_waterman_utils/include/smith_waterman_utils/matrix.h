#ifndef SMITH_WATERMAN_UTILS_MATRIX_H
#define SMITH_WATERMAN_UTILS_MATRIX_H

#include <memory>

namespace sw
{
template<typename T>
class Matrix
{
public:
    Matrix(size_t rows, size_t columns);

    T& operator()(size_t i, size_t j);
    const T& operator()(size_t i, size_t j) const;

    [[nodiscard]] size_t rows() const { return m_rows; }
    [[nodiscard]] size_t columns() const { return m_columns; }

    template<typename T>
    friend void fill(Matrix<T>& m, T value)
    {
        std::fill(m.m_elements.get(), m.m_elements.get() + m.m_columns * m.m_rows, value);
    }

private:
    size_t m_rows;
    size_t m_columns;
    std::unique_ptr<T[]> m_elements;
};

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns) : m_rows(rows), m_columns(columns), m_elements(new T[rows * columns])
{}

template<typename T>
T& Matrix<T>::operator()(const size_t i, const size_t j)
{
    return m_elements[i + j * m_rows];
}

template<typename T>
const T& Matrix<T>::operator()(const size_t i, const size_t j) const
{
    return m_elements[i + j * m_rows];
}
}  // namespace sw

#endif
