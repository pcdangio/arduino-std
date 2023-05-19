/// \file std/container/fixed/array.hpp
/// \brief Defines the std::array class.
#ifndef STD___ARRAY_H
#define STD___ARRAY_H

// std
#include <std/container/fixed/fixed.hpp>

namespace std {

/// \brief A fixed-size array container.
/// \tparam object_type The type of value stored in the array.
template <typename object_type>
class array
    : public std::container::fixed<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new array instance.
    /// \param size The size of the array.
    array(size_t size)
        : std::container::fixed<object_type>(size)
    {}

    // ACCESS
    /// \brief Gets a reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A reference to the value.
    object_type& operator[](size_t index)
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& operator[](size_t index) const
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A reference to the value.
    object_type& at(size_t index)
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& at(size_t index) const
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a reference to the first value in the vector.
    /// \return A reference to the first value.
    object_type& front()
    {
        return *array::m_begin;
    }
    /// \brief Gets a const reference to the first value in the vector.
    /// \return A const reference to the first value.
    const object_type& front() const
    {
        return *array::m_begin;
    }
    /// \brief Gets a reference to the last value in the vector.
    /// \return A reference to the last value.
    object_type& back()
    {
        return *array::m_end;
    }
    /// \brief Gets a const reference to the last value in the vector.
    /// \return A const reference to the last value.
    const object_type& back() const
    {
        return *array::m_end;
    }
    /// \brief Gets a pointer to the vector's underlying data.
    /// \return A pointer to the underlying data.
    object_type* data()
    {
        return array::m_begin;
    }
    /// \brief Gets a const pointer to the vector's underlying data.
    /// \return A const pointer to the underlying data.
    const object_type* data() const
    {
        return array::m_begin;
    }
};

}

#endif