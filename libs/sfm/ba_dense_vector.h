/*
 * Copyright (C) 2015, Simon Fuhrmann, Fabian Langguth
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#ifndef SFM_BA_DENSE_VECTOR_HEADER
#define SFM_BA_DENSE_VECTOR_HEADER

#include <stdexcept>
#include <vector>

#include "sfm/defines.h"

SFM_NAMESPACE_BEGIN
SFM_BA_NAMESPACE_BEGIN

template <typename T>
class DenseVector
{
public:
    DenseVector (void) = default;
    DenseVector (std::size_t size, T const& value = T(0));
    void resize (std::size_t size, T const& value = T(0));
    std::size_t size (void) const;

    T* begin (void);
    T* end (void);

    bool operator== (DenseVector const& rhs);
    T& operator[] (std::size_t index);
    T const& operator[] (std::size_t index) const;
    T& at (std::size_t index);
    T const& at (std::size_t index) const;

    DenseVector subtract (DenseVector const& rhs) const;

private:
    std::vector<T> values;
};

/* ------------------------ Implementation ------------------------ */

template <typename T>
DenseVector<T>::DenseVector (std::size_t size, T const& value)
{
    this->resize(size, value);
}

template <typename T>
void
DenseVector<T>::resize (std::size_t size, T const& value)
{
    this->values.clear();
    this->values.resize(size, value);
}

template <typename T>
std::size_t
DenseVector<T>::size (void) const
{
    return this->values.size();
}

template <typename T>
T*
DenseVector<T>::begin (void)
{
    return this->values.data();
}

template <typename T>
T*
DenseVector<T>::end (void)
{
    return this->values.data() + this->values.size();
}

template <typename T>
bool
DenseVector<T>::operator== (DenseVector const& rhs)
{
    if (this->size() != rhs.size())
        return false;
    for (std::size_t i = 0; i < this->size(); ++i)
        if (this->at(i) != rhs.at(i))
            return false;
    return true;
}

template <typename T>
T&
DenseVector<T>::operator[] (std::size_t index)
{
    return this->values[index];
}

template <typename T>
T const&
DenseVector<T>::operator[] (std::size_t index) const
{
    return this->values[index];
}

template <typename T>
T&
DenseVector<T>::at (std::size_t index)
{
    return this->values[index];
}

template <typename T>
T const&
DenseVector<T>::at (std::size_t index) const
{
    return this->values[index];
}

template <typename T>
DenseVector<T>
DenseVector<T>::subtract (DenseVector<T> const& rhs) const
{
    if (this->size() != rhs.size())
        throw std::invalid_argument("Incompatible vector dimensions");

    DenseVector<T> ret(this->size(), T(0));
    for (std::size_t i = 0; i < this->size(); ++i)
        ret.values[i] = this->values[i] - rhs.values[i];
    return ret;
}

SFM_BA_NAMESPACE_END
SFM_NAMESPACE_END

#endif // SFM_BA_DENSE_VECTOR_HEADER
