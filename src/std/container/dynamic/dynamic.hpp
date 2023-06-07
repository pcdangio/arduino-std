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

    // SHIFT
    /// \brief Shifts a back-end subset of values backwards, increasing the size of the container.
    /// \param current_position The starting position of the back-end subset to shift backwards.
    /// \param count The number of elements to shift the subset backwards.
    /// \return TRUE if the shift succeeded, FALSE if the container does not have enough capacity.
    bool shift_backward(std::iterator<object_type> current_position, size_t count)
    {
        // Validate count.
        if(count == 0)
        {
            // No shift necessary.
            return true;
        }

        // Calculate new end position.
        auto new_end = (current_position + count) + (dynamic::m_end - current_position);

        // Check for space.
        if(new_end > dynamic::m_capacity)
        {
            return false;
        }

        // Move entries backwards.
        for(auto source = dynamic::m_end - 1, destination = new_end - 1; source >= current_position; --source, --destination)
        {
            *destination = *source;
        }

        // Update end position.
        dynamic::m_end = new_end;

        return true;
    }
    /// \brief Shifts a back-end subset of values forwards, decreasing the size of the container.
    /// \param current_position The starting position of the back-end subset to shift fowards.
    /// \param count The number of elements to shift the subset forwards.
    void shift_forward(std::iterator<object_type> current_position, size_t count)
    {
        // Validate count.
        if(count == 0)
        {
            // No shift necessary.
            return;
        }

        // Move remaining entries forward.
        auto destination = current_position - count;
        for(auto source = current_position; source != dynamic::m_end; ++source, ++destination)
        {
            *destination = *source;
        }

        // Update end position.
        dynamic::m_end = destination;
    }
};

}}

#endif