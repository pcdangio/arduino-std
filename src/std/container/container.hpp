/// \file std/container/container.hpp
/// \brief Defines the std::container class.
#ifndef STD___CONTAINER_H
#define STD___CONTAINER_H

// container
#include <std/container/iterator.hpp>

// arduino
#include <Arduino.h>

namespace std {

/// \brief A container for storing an array of objects.
/// \tparam object_type The object type stored in the container.
template <typename object_type>
class container
{
public:
    // CONSTRUCTORSposition
    /// \brief Constructs a new container instance.
    /// \param capacity The maximum capacity of the container.
    container(size_t capacity)
        : m_begin(new object_type[capacity]),
          m_end(m_begin),
          m_capacity(m_begin + capacity),
          capacity(capacity)
    {}
    ~container()
    {
        // Free container data.
        delete [] container::m_begin;
    }

    // MODIFIERS
    /// \brief Inserts a new element into the container.
    /// \param position The position to insert the element into.
    /// \param value The value to insert.
    bool insert(std::iterator<object_type> position, const object_type& value)
    {
        // Check for space.
        if(container::m_end == container::m_capacity)
        {
            return false;
        }

        // Update end position.
        ++container::m_end;

        // Move remaining entries backward.
        for(object_type* entry = container::m_end; entry != position; --entry)
        {
            *entry = *(entry - 1);
        }

        // Store new value at position.
        *position = value;

        return true;
    }
    /// \brief Erases an object at a specified position in the container.
    /// \param position The position to erase.
    void erase(std::iterator<object_type> position)
    {
        // Move remaining entries forward.
        for(++position; position != container::m_end; ++position)
        {
            *(position - 1) = *position;
        }

        // Update end position.
        --container::m_end;
    }
    /// \brief Clears all objects from the container.
    void clear()
    {
        // Reset array end.
        container::m_end = container::m_begin;
    }

    // ACCESS
    /// \brief Gets an iterator to the beginning of the container.
    /// \return The begin iterator.
    std::iterator<object_type> begin() const
    {
        return container::m_begin;
    }
    /// \brief Gets an iterator to the end of the container.
    /// \return The end iterator.
    std::iterator<object_type> end() const
    {
        return container::m_end;
    }
    /// \brief Gets a const_iterator to the beginning of the container.
    /// \return The begin const_iterator.
    std::const_iterator<object_type> cbegin() const
    {
        return container::m_begin;
    }
    /// \brief Gets a const_iterator to the end of the container.
    /// \return The end const_iterator.
    std::const_iterator<object_type> cend() const
    {
        return container::m_end;
    }

    // INSPECTION
    /// \brief Checks if the container contains an object.
    /// \param object The object to check.
    /// \return TRUE if the container contains the object, otherwise FALSE.
    bool contains(const object_type& object) const
    {
        // Iterate through container.
        for(auto entry = container::m_begin; entry != container::m_end; ++entry)
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
        return container::m_end - container::m_begin;
    }
    /// \brief Checks if the container is empty.
    /// \return TRUE if the container is empty, otherwise FALSE.
    bool empty() const
    {
        return container::m_begin == container::m_end;
    }

protected:
    // ENTRIES
    /// \brief A pointer to the beginning of the container array.
    object_type* m_begin;
    /// \brief A pointer to the end of the existing data in the container array.
    object_type* m_end;
    /// \brief A pointer to the end of the the container array.
    object_type* m_capacity;
};

}

#endif