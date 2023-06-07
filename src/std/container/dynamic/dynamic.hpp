/// \file std/container/dynamic/dynamic.hpp
/// \brief Defines the std::dynamic::dynamic class.
#ifndef STD___CONTAINER___DYNAMIC_H
#define STD___CONTAINER___DYNAMIC_H

// container
#include <std/container/iterator.hpp>

// arduino
#include <Arduino.h>

namespace std {
namespace container {

/// \brief A dynamic-sized container.
/// \tparam object_type The object type stored in the container.
template <typename object_type>
class dynamic
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new dynamic container instance.
    /// \param capacity The maximum capacity of the container.
    dynamic(size_t capacity)
        : m_begin(new object_type[capacity]),
          m_end(m_begin),
          m_capacity(m_begin + capacity),
          capacity(capacity)
    {}
    ~dynamic()
    {
        // Free container data.
        delete [] dynamic::m_begin;
    }

    // MODIFIERS
    /// \brief Clears all values from the container.
    void clear()
    {
        // Reset array end.
        dynamic::m_end = dynamic::m_begin;
    }

    // ACCESS
    /// \brief Gets an iterator to the beginning of the container.
    /// \return The begin iterator.
    std::iterator<object_type> begin() const
    {
        return dynamic::m_begin;
    }
    /// \brief Gets an iterator to the end of the container.
    /// \return The end iterator.
    std::iterator<object_type> end() const
    {
        return dynamic::m_end;
    }
    /// \brief Gets a const_iterator to the beginning of the container.
    /// \return The begin const_iterator.
    std::const_iterator<object_type> cbegin() const
    {
        return dynamic::m_begin;
    }
    /// \brief Gets a const_iterator to the end of the container.
    /// \return The end const_iterator.
    std::const_iterator<object_type> cend() const
    {
        return dynamic::m_end;
    }

    // INSPECTION
    /// \brief Checks if the container contains an object.
    /// \param object The object to check.
    /// \return TRUE if the container contains the object, otherwise FALSE.
    bool contains(const object_type& object) const
    {
        // Iterate through container.
        for(auto entry = dynamic::m_begin; entry != dynamic::m_end; ++entry)
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
    /// \brief The maximum capacity of the container.
    const size_t capacity;
    /// \brief Gets the current size of the container.
    /// \return The current size.
    size_t size() const
    {
        return dynamic::m_end - dynamic::m_begin;
    }
    /// \brief Checks if the container is empty.
    /// \return TRUE if the container is empty, otherwise FALSE.
    bool empty() const
    {
        return dynamic::m_begin == dynamic::m_end;
    }
    /// \brief Checks if the container is full.
    /// \return TRUE if the container is at capacity, otherwise FALSE.
    bool full() const
    {
        return dynamic::m_end == dynamic::m_capacity;
    }

protected:
    // ENTRIES
    /// \brief A pointer to the beginning of the container array.
    object_type* const m_begin;
    /// \brief A pointer to the end of the existing data in the container array.
    object_type* m_end;
    /// \brief A pointer to the end of the the container array.
    object_type* const m_capacity;
};

}}

#endif