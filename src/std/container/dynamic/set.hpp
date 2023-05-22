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
    /// \brief Inserts an object in the set.
    /// \param object The object to insert.
    /// \return TRUE if the set now contains the object, FALSE if the set is at capacity.
    bool insert(const object_type& object)
    {
        // Check if object already exists in list.
        if(set::contains(object))
        {
            return true;
        }

        // Check for size.
        if(set::m_end == set::m_capacity)
        {
            return false;
        }

        // Add new object and increment end pointer.
        *set::m_end++ = object;

        return true;
    }
    /// \brief Erases an object from the set.
    /// \param object The object to erase.
    /// \return TRUE if the object was erased, FALSE if it did not exist in the set.
    bool erase(const object_type& object)
    {
        // Search for object.
        auto entry = set::m_begin;
        for(; entry != set::m_end; ++entry)
        {
            if(*entry == object)
            {
                break;
            }
        }

        // Check if object was found.
        if(entry == set::m_end)
        {
            return false;
        }

        // Erase at position.
        set::erase(entry);

        return true;
    }
    using std::container::dynamic<object_type>::erase;
};

}

#endif