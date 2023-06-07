/// \file std/container/dynamic/set.hpp
/// \brief Defines the std::set class.
#ifndef STD___SET_H
#define STD___SET_H

// std
#include <std/container/dynamic/dynamic.hpp>

namespace std {

/// \brief A unique set of objects.
/// \tparam object_type The type of object stored in the set.
template <typename object_type>
class set
    : public std::container::dynamic<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new set instance.
    /// \param capacity The maximum capacity of the set.
    set(size_t capacity)
        : std::container::dynamic<object_type>(capacity)
    {}

    // MODIFIERS
    /// \brief Inserts a value in the set.
    /// \param value The value to insert.
    /// \return TRUE if the set now contains the value, FALSE if the set is at capacity.
    bool insert(const object_type& value)
    {
        // Check if value already exists in list.
        if(set::contains(value))
        {
            return true;
        }

        // Check for size.
        if(set::m_end == set::m_capacity)
        {
            return false;
        }

        // Add new object and increment end pointer.
        *set::m_end++ = value;

        return true;
    }
    /// \brief Erases a value from the set.
    /// \param value The value to erase.
    /// \return TRUE if the value was erased, FALSE if it did not exist in the set.
    bool erase(const object_type& value)
    {
        // Try to find location of value.
        auto entry = set::find(value);
        if(entry == set::m_end)
        {
            return false;
        }

        // Shift back-end subset forwards at entry location.
        set::shift_forward(entry, 1);

        return true;
    }

    // INSPECTION
    /// \brief Finds a value in the set.
    /// \param value The value to find.
    /// \return If found, returns an iterator pointing to the found value.
    /// If the set does not contain the value, returns an iterator poinding to set::end().
    std::iterator<object_type> find(const object_type& value) const
    {
        // Search for value.
        auto entry = set::m_begin;
        for(; entry != set::m_end; ++entry)
        {
            if(*entry == value)
            {
                break;
            }
        }

        return entry;
    }
    /// \brief Checks if the set contains a value.
    /// \param value The value to check for.
    /// \return TRUE if the set contains the value, otherwise FALSE.
    bool contains(const object_type& value) const
    {
        return set::find(value) != set::m_end;
    }
};

}

#endif