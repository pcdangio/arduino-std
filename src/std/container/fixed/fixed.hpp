/// \file std/container/fixed/fixed.hpp
/// \brief Defines the std::container::fixed class.
#ifndef STD___CONTAINER___FIXED_H
#define STD___CONTAINER___FIXED_H

// std
#include <std/container/iterator.hpp>

// arduino
#include <Arduino.h>

namespace std {
/// \brief Contains all code for container base classes.
namespace container {

/// \brief A fixed-size container.
/// \tparam object_type The type of object stored in the container.
template <typename object_type>
class fixed
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new fixed instance.
    /// \param size The size of the container.
    fixed(size_t size)
        : m_begin(new object_type[size]),
          m_end(m_begin + size),
          size(size)
    {}
    ~fixed()
    {
        // Free array resources.
        delete [] fixed::m_begin;
    }

    // ACCESS
    /// \brief Gets an iterator to the beginning of the container.
    /// \return The begin iterator.
    std::iterator<object_type> begin() const
    {
        return fixed::m_begin;
    }
    /// \brief Gets an iterator to the end of the container.
    /// \return The end iterator.
    std::iterator<object_type> end() const
    {
        return fixed::m_end;
    }
    /// \brief Gets a const_iterator to the beginning of the container.
    /// \return The begin const_iterator.
    std::const_iterator<object_type> cbegin() const
    {
        return fixed::m_begin;
    }
    /// \brief Gets a const_iterator to the end of the container.
    /// \return The end const_iterator.
    std::const_iterator<object_type> cend() const
    {
        return fixed::m_end;
    }

    // INSPECTION
    /// \brief Checks if the container contains an object.
    /// \param object The object to check.
    /// \return TRUE if the container contains the object, otherwise FALSE.
    bool contains(const object_type& object) const
    {
        // Iterate through container.
        for(auto entry = fixed::m_begin; entry != fixed::m_end; ++entry)
        {
            // Check if entry is equal to object.
            if(*entry == object)
            {
                return true;
            }
        }

        // If this point reached, object not present in container.
        return false;
    }

    // SIZE
    /// \brief The size of the container.
    const size_t size;

protected:
    // ARRAY
    /// \brief A pointer to the beginning of the container.
    object_type* const m_begin;
    /// \brief A pointer to the end of the container.
    object_type* const m_end;
};

}}

#endif