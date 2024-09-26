/// \file std/container/fixed/base.hpp
/// \brief Defines the std::container::fixed::base class.
#ifndef STD___CONTAINER___FIXED___BASE_H
#define STD___CONTAINER___FIXED___BASE_H

// std
#include <std/container/iterator.hpp>
#include <std/stddef.hpp>

// arduino
#include <Arduino.h>

namespace std::container {

/// \brief Contains all code for std fixed container components.
namespace fixed {

/// \brief A base fixed-size container.
/// \tparam object_type The type of object stored in the container.
/// \tparam size_value The size of the container.
template <typename object_type, std::size_t size_value>
class base
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new base fixed container instance.
    base()
        : m_begin(&m_data[0]),
          m_end(m_begin + size_value)
    {}
    /// \brief Copy constructs a new base fixed container instance from another.
    /// \param[in] other The other container to copy construct from.
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
    std::iterator<object_type> begin()
    {
        return base::m_begin;
    }
    /// \brief Gets an iterator to the end of the container.
    /// \return The end iterator.
    std::iterator<object_type> end()
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

    // CAPACITY
    /// \brief Gets the size of the container.
    /// \return The size of the container.
    std::size_t size() const
    {
        return base::m_end - base::m_begin;
    }

    // COMPARISON
    /// \brief Checks if this container is equal to another container.
    /// \param[in] other The other array to compare with.
    /// \return TRUE if the two containers are equal, otherwise FALSE.
    bool operator==(const std::container::fixed::base<object_type,size_value>& other) const
    {
        // Iterate through both containers.
        auto this_entry = base::m_begin;
        auto other_entry = other.m_begin;
        while(this_entry != base::m_end)
        {
            // Compare the two entries.
            if(*this_entry++ != *other_entry++)
            {
                return false;
            }
        }

        // Indicate equal.
        return true;
    }
    /// \brief Checks if this container is not equal to another container.
    /// \param[in] other The other array to compare with.
    /// \return TRUE if the two containers are not equal, otherwise FALSE.
    bool operator!=(const std::container::fixed::base<object_type,size_value>& other) const
    {
        // Iterate through both containers.
        auto this_entry = base::m_begin;
        auto other_entry = other.m_begin;
        while(this_entry != base::m_end)
        {
            // Compare the two entries.
            if(*this_entry++ != *other_entry++)
            {
                return true;
            }
        }

        // Indicate equal.
        return false;
    }
    
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