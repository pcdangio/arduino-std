/// \file std/container/dynamic/base.hpp
/// \brief Defines the std::container::dynamic::base template class.
#ifndef STD___CONTAINER___DYNAMIC___BASE_H
#define STD___CONTAINER___DYNAMIC___BASE_H

// std
#include <std/container/iterator.hpp>
#include <std/stddef.hpp>

// arduino
#include <Arduino.h>

/// \brief Contains all code for standard library components.
namespace std {

/// \brief Contains all code for std container components.
namespace container {

/// \brief Contains all code for dynamic container components.
namespace dynamic {

/// \brief A base dynamic-sized container.
/// \tparam object_type The object type stored in the container.
template <typename object_type>
class base
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new base container instance.
    /// \param[in] capacity The maximum capacity of the container.
    base(std::size_t capacity)
        : m_begin(new object_type[capacity]),
          m_end(m_begin),
          m_capacity(m_begin + capacity)
    {}
    /// \brief Copy-constructs a new base container instance from another base container.
    /// \param[in] other The other instance to copy-construct from.
    /// \note This performs a deep copy.
    base(const std::container::dynamic::base<object_type>& other)
        : m_begin(new object_type[other.capacity()]),
          m_end(m_begin + (other.m_end - other.m_begin)),
          m_capacity(m_begin + (other.m_capacity - other.m_begin))
    {
        // Copy values from other.
        auto this_entry = base::m_begin;
        auto other_entry = other.m_begin;
        while(other_entry < other.m_end)
        {
            *this_entry++ = *other_entry++;
        }
    }
    /// \brief Move-constructs a new base container instance from another base container.
    /// \param[in] other The other instance to move-construct from.
    base(std::container::dynamic::base<object_type>&& other)
        : m_begin(other.m_begin),
          m_end(other.m_end),
          m_capacity(other.m_capacity)
    {
        // Reset the other container to a new allocation.
        std::size_t capacity = base::m_capacity - base::m_begin;
        other.m_begin = new object_type[capacity];
        other.m_end = other.m_begin;
        other.m_capacity = other.m_begin + capacity;
    }
    ~base()
    {
        // Clean up allocated memory.
        delete [] base::m_begin;
    }

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

    // MODIFIERS
    /// \brief Erases an element from the container.
    /// \param[in] position The iterator position to erase.
    /// \return An iterator to the element after the erased element.
    std::iterator<object_type> erase(std::iterator<object_type> position)
    {
        // Shift left by one.
        base::shift_left(position + 1, 1);

        // Position now points to the next element.
        return position;
    }
    /// \brief Erases an element from the container.
    /// \param[in] position The const iterator position to erase.
    /// \return An iterator to the element after the erased element.
    std::const_iterator<object_type> erase(std::const_iterator<object_type> position)
    {
        // Shift left by one.
        base::shift_left(const_cast<std::iterator<object_type>>(position + 1), 1);

        // Position now points to the next element.
        return position;
    }
    /// \brief Erases a range of elements from the container.
    /// \param[in] begin The iterator to the beginning of the range.
    /// \param[in] end The iterator to the end of the range.
    /// \return An iterator to the element after the last erased element.
    std::iterator<object_type> erase(std::iterator<object_type> begin, std::iterator<object_type> end)
    {
        // Shift left by number of elements in the inclusive range.
        base::shift_left(end + 1, end - begin + 1);

        // Begin now points to the next element.
        return begin;
    }
    /// \brief Erases a range of elements from the container.
    /// \param[in] begin The const iterator to the beginning of the range.
    /// \param[in] end The const iterator to the end of the range.
    /// \return An iterator to the element after the last erased element.
    std::const_iterator<object_type> erase(std::const_iterator<object_type> begin, std::const_iterator<object_type> end)
    {
        // Shift left by number of elements in the inclusive range.
        base::shift_left(const_cast<std::iterator<object_type>>(end + 1), end - begin + 1);

        // Begin now points to the next element.
        return begin;
    }
    /// \brief Clears all values from the container.
    void clear()
    {
        // Reset end iterator.
        base::m_end = base::m_begin;
    }

    // CAPACITY
    /// \brief Gets the size of the container.
    /// \return The size of the container.
    std::size_t size() const
    {
        return base::m_end - base::m_begin;
    }
    /// \brief Gets the maximum capacity of the container.
    /// \return The capacity of the container.
    std::size_t capacity() const
    {
        return base::m_capacity - base::m_begin;
    }
    /// \brief Checks if the container is empty.
    /// \return TRUE if the container is empty, otherwise FALSE.
    bool empty() const
    {
        return base::m_end == base::m_begin;
    }
    /// \brief Checks if the container is at capacity.
    /// \return TRUE if the container is at capacity, otherwise FALSE.
    bool full() const
    {
        return base::m_end == base::m_capacity;
    }

protected:
    // MEMORY
    /// \brief Stores a pointer to the beginning of the container's contiguous memory.
    object_type* m_begin;
    /// \brief Stores a pointer to the end of the container's populated contiguous memory.
    object_type* m_end;
    /// \brief Stores a pointer to the capacity limit of the container's contiguous memory.
    object_type* m_capacity;

    // MODIFIERS
    /// \brief Copy-assigns the contents of another container to this container.
    /// \param[in] other The other container to copy-assign from.
    /// \return A reference to this container.
    /// \note This performs a deep copy.
    std::container::dynamic::base<object_type>& operator=(const std::container::dynamic::base<object_type>& other)
    {
        // Free this container's memory.
        delete [] base::m_begin;

        // Create new memory based on the other container's capacity.
        base::m_begin = new object_type[other.m_capacity - other.m_begin];
        base::m_end = base::m_begin + (other.m_end - other.m_begin);
        base::m_capacity = base::m_begin + (other.m_capacity - other.m_begin);

        // Copy values from other.
        auto this_entry = base::m_begin;
        auto other_entry = other.m_begin;
        while(other_entry < other.m_end)
        {
            *this_entry++ = *other_entry++;
        }

        return *this;
    }
    /// \brief Move-assigns the contents of another container to this container.
    /// \param[in] other The other container to move-assign from.
    /// \return A reference to this container.
    std::container::dynamic::base<object_type>& operator=(std::container::dynamic::base<object_type>&& other)
    {
        // Free this container's memory.
        delete [] base::m_begin;

        // Copy other container's memory into this container.
        base::m_begin = other.m_begin;
        base::m_end = other.m_end;
        base::m_capacity = other.m_capacity;

        // Reset the other container's memory to a new allocation.
        std::size_t capacity = base::m_capacity - base::m_begin;
        other.m_begin = new object_type[capacity];
        other.m_end = other.m_begin;
        other.m_capacity = other.m_begin + capacity;

        return *this;
    }
    /// \brief Swaps the contents of this container with another container.
    /// \param[in] other The other container to swap with.
    void swap(std::container::dynamic::base<object_type>& other)
    {
        // Store this container's pointers in a temporary.
        auto temp_begin = base::m_begin;
        auto temp_end = base::m_end;
        auto temp_capacity = base::m_capacity;

        // Store the other container's pointers in this container.
        base::m_begin = other.m_begin;
        base::m_end = other.m_end;
        base::m_capacity = other.m_capacity;

        // Store this container's original pointers in the other container.
        other.m_begin = temp_begin;
        other.m_end = temp_end;
        other.m_capacity = temp_capacity;
    }

    // COMPARISON
    /// \brief Checks if this container is equal to another container.
    /// \param[in] other The other container to compare with.
    /// \return TRUE if the two containers are equal, otherwise FALSE.
    bool operator==(const std::container::dynamic::base<object_type>& other) const
    {
        // Verify container sizes match.
        if(base::m_end - base::m_begin != other.m_end - other.m_begin)
        {
            return false;
        }

        // Compare values.
        auto this_entry = base::m_begin;
        auto other_entry = other.m_begin;
        while(this_entry < base::m_end)
        {
            if(*this_entry++ != *other_entry++)
            {
                return false;
            }
        }

        // Indicate equal.
        return true;
    }
    /// \brief Checks if this container is unequal with another container.
    /// \param[in] other The other container to compare with.
    /// \return TRUE if the two containers are unequal, otherwise FALSE.
    bool operator!=(const std::container::dynamic::base<object_type>& other) const
    {
        // Check for size difference shortcut.
        if(base::m_end - base::m_begin != other.m_end - other.m_begin)
        {
            return true;
        }

        // Compare values.
        auto this_entry = base::m_begin;
        auto other_entry = other.m_begin;
        while(this_entry < base::m_end)
        {
            if(*this_entry++ != *other_entry++)
            {
                return true;
            }
        }

        // Indicate equal.
        return false;
    }

    // SHIFT
    /// \brief Shifts elements in the container left and reduces the size of the container.
    /// \param[in] position The position (inclusive) to begin the left-shift.
    /// \param[in] count The number of positions to shift left.
    /// \return TRUE if the shift succeeded, otherwise FALSE.
    bool shift_left(std::iterator<object_type> position, std::size_t count)
    {
        // Validate position.
        if(position < base::m_begin || position > base::m_end)
        {
            return false;
        }

        // Validate count bounds.
        if(position - base::m_begin < count)
        {
            return false;
        }

        // Shortcut if count is zero.
        if(count == 0)
        {
            return true;
        }

        // Create source and destination iterators.
        std::iterator<object_type> source = position;
        std::iterator<object_type> destination = position - count;

        // Shift elements left.
        while(source < base::m_end)
        {
            *destination++ = *source++;
        }

        // Update container end.
        base::m_end -= count;

        // Indicate success.
        return true;
    }
    /// \brief Shifts elements in the container right and increases the size of the container.
    /// \param[in] position The position (inclusive) to begin the right-shift.
    /// \param[in] count The number of positions to shift right.
    /// \return TRUE if the shift succeeded, otherwise FALSE.
    bool shift_right(std::iterator<object_type> position, std::size_t count)
    {
        // Validate position.
        if(position < base::m_begin || position > base::m_end)
        {
            return false;
        }

        // Validate count bounds.
        if(base::m_capacity - base::m_end < count)
        {
            return false;
        }

        // Shortcut if count is zero.
        if(count == 0)
        {
            return true;
        }

        // Shift elements right if container is not empty.
        if(base::m_end != base::m_begin)
        {
            // Create source and destination iterators.
            std::iterator<object_type> source = base::m_end - 1;
            std::iterator<object_type> destination = base::m_end + count - 1;

            // Shift elements right.
            while(source >= position)
            {
                *destination-- = *source--;
            }
        }

        // Update container end.
        base::m_end += count;

        // Indicate success.
        return true;
    }
};

}}}

#endif