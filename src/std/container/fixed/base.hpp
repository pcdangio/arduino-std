/// \file std/container/fixed/base.hpp
/// \brief Defines the std::container::fixed::base class.
#ifndef STD___CONTAINER___FIXED___BASE_H
#define STD___CONTAINER___FIXED___BASE_H

// std
#include <std/container/iterator.hpp>

// arduino
#include <Arduino.h>

namespace std::container {

/// \brief Contains all code for std fixed container components.
namespace fixed {

/// \brief A base fixed-size container.
/// \tparam object_type The type of object stored in the container.
/// \tparam size_value The size of the container.
template <typename object_type, size_t size_value>
class base
{
public:
    // CONSTRUCTORS
    base()
        : m_begin(&m_data[0]),
          m_end(m_begin + size_value)
    {}
    base(const std::container::fixed::base<object_type,size_value>& other)
        : m_begin(&m_data[0]),
          m_end(m_begin + size_value)
    {
        // Deep copy data from other container into this container.
        auto this_entry = base::m_begin;
        auto other_entry = other.m_begin;
        while(other_entry < other.m_end)
        {
            *this_entry++ = *other_entry++;
        }
    }
    base(std::container::fixed::base<object_type,size_value>&& other) = delete;

    // ACCESS
    /// \brief Gets an iterator to the beginning of the container.
    /// \return The begin iterator.
    std::iterator<object_type> begin() const
    {
        return base::m_begin;
    }
    /// \brief Gets an iterator to the end of the container.
    /// \return The end iterator.
    std::iterator<object_type> end() const
    {
        return base::m_end;
    }
    /// \brief Gets a const_iterator to the beginning of the container.
    /// \return The begin const_iterator.
    std::const_iterator<object_type> cbegin() const
    {
        return base::m_begin;
    }
    /// \brief Gets a const_iterator to the end of the container.
    /// \return The end const_iterator.
    std::const_iterator<object_type> cend() const
    {
        return base::m_end;
    }

    // PROPERTIES
    /// \brief The size of the container.
    const size_t size = size_value;

protected:
    // DATA
    /// \brief Stores the container's data in a fixed size/location array.
    object_type m_data[size_value];

    // ITERATORS
    /// \brief An iterator to the beginning of the data array.
    object_type* const m_begin;
    /// \brief An iterator to the end of the data array.
    object_type* const m_end;
};

}}

#endif