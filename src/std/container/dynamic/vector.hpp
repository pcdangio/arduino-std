/// \file std/container/dynamic/vector.hpp
/// \brief Defines the std::vector template class.
#ifndef STD___CONTAINER___DYNAMIC___VECTOR_H
#define STD___CONTAINER___DYNAMIC___VECTOR_H

// std
#include <std/container/dynamic/base.hpp>

namespace std {

/// \brief A dynamic container that stores a sequence of objects.
/// \tparam object_type The object type stored by this container.
template <typename object_type>
class vector
    : public std::container::dynamic::base<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new empty vector.
    /// \param[in] capacity The maximum capacity of this vector.
    vector(std::size_t capacity)
        : std::container::dynamic::base<object_type>(capacity)
    {}
    /// \brief Copy-constructs a new vector from another vector.
    /// \param[in] other The other vector to copy-construct from.
    vector(const std::vector<object_type>& other)
        : std::container::dynamic::base<object_type>(other)
    {}
    /// \brief Move-constructs a new vector from another vector.
    /// \param[in] other The other vector to move-construct from.
    vector(std::vector<object_type>&& other)
        : std::container::dynamic::base<object_type>(other)
    {}

    // ACCESS
    /// \brief Gets a reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A reference to the value.
    object_type& operator[](std::size_t index)
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& operator[](std::size_t index) const
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A reference to the value.
    object_type& at(std::size_t index)
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& at(std::size_t index) const
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a reference to the first value in this vector.
    /// \return A reference to the first value.
    object_type& front()
    {
        return *vector::m_begin;
    }
    /// \brief Gets a const reference to the first value in this vector.
    /// \return A const reference to the first value.
    const object_type& front() const
    {
        return *vector::m_begin;
    }
    /// \brief Gets a reference to the last value in this vector.
    /// \return A reference to the last value.
    object_type& back()
    {
        return *(vector::m_end - 1);
    }
    /// \brief Gets a const reference to the last value in this vector.
    /// \return A const reference to the last value.
    const object_type& back() const
    {
        return *(vector::m_end - 1);
    }
    /// \brief Gets a pointer to the underlying sequential array of data stored by this vector.
    /// \return A pointer to the sequential array of data.
    object_type* data()
    {
        return vector::m_begin;
    }
    /// \brief Gets a pointer-to-const to the underlying sequential array of data stored by this vector.
    /// \return A pointer-to-const to the sequential array of data.
    const object_type* data() const
    {
        return vector::m_begin;
    }

    // MODIFIERS
    /// \brief Appends a new object to the end of this vector.
    /// \param[in] value The value to append.
    /// \return TRUE if the operation succeeded, FALSE if this vector is at capacity.
    bool push_back(const object_type& value)
    {
        // Verify container space.
        if(vector::m_end == vector::m_capacity)
        {
            return false;
        }

        // Add value to end and increment end.
        *vector::m_end++ = value;

        // Indicate success.
        return true;
    }
    /// \brief Removes the last object from this vector.
    void pop_back()
    {
        // Verify vector isn't empty.
        if(vector::m_end == vector::m_begin)
        {
            return;
        }

        // Decrement vector end.
        --vector::m_end;
    }
    /// \brief Inserts an object into this vector at a specified position.
    /// \param[in] position The position to insert the object at.
    /// \param[in] value The object to insert.
    /// \return An iterator to the inserted object. NULLPTR if vector is at capacity.
    std::iterator<object_type> insert(std::iterator<object_type> position, const object_type& value)
    {
        // Try to shift right at the specified position.
        if(!vector::shift_right(position, 1))
        {
            return nullptr;
        }

        // Copy value into the position.
        *position = value;

        // Return the position, as it contains the new value.
        return position;
    }
    /// \brief Assigns a size and value to this vector.
    /// \param[in] value The value to set all elements to.
    /// \param[in] count The size to set this vector to.
    /// \return TRUE if the assignment succeeded, FALSE if this vector does not have enough capacity.
    bool assign(const object_type& value, std::size_t count)
    {
        // Verify space in the container.
        if(vector::m_capacity - vector::m_begin < count)
        {
            return false;
        }

        // Update end.
        vector::m_end = vector::m_begin + count;

        // Assign value.
        for(auto entry = vector::m_begin; entry < vector::m_end; ++entry)
        {
            *entry = value;
        }

        // Indicate success.
        return true;
    }
    /// \brief Assigns a range of values to this vector.
    /// \param[in] begin An iterator to the beginning of the range to copy.
    /// \param[in] end An iterator to the end of the range to copy.
    /// \return TRUE if the assignment succeeded, FALSE if this vector does not have enough capacity.
    bool assign(std::const_iterator<object_type> begin, std::const_iterator<object_type> end)
    {
        // Calculate number of elements.
        std::size_t count = end - begin;

        // Verify space in the container.
        if(vector::m_capacity - vector::m_begin < count)
        {
            return false;
        }

        // Update end.
        vector::m_end = vector::m_begin + count;

        // Copy values.
        auto destination = vector::m_begin;
        auto source = begin;
        while(destination < vector::m_end)
        {
            *destination++ = *source++;
        }

        // Indicate success.
        return true;
    }
    /// \brief Resizes this vector to a specified size, default-constructing additional elements if needed.
    /// \param[in] size The size to set this vector to.
    /// \return TRUE if the resize succeeded, FALSE if this vector does not have enough capacity.
    bool resize(std::size_t size)
    {
        return vector::resize(size, object_type());
    }
    /// \brief Resizes this vector to a specified size, using a provided value for additional elements if needed.
    /// \param[in] size The size to set this vector to.
    /// \return TRUE if the resize succeeded, FALSE if this vector does not have enough capacity.
    bool resize(std::size_t size, const object_type& value)
    {
        // Check if size is greater than current size.
        if(size > vector::m_end - vector::m_begin)
        {
            // Increasing size of container.

            // Verify space in the container.
            if(vector::m_capacity - vector::m_begin < size)
            {
                return false;
            }

            // Capture original end.
            auto original_end = vector::m_end;

            // Update end.
            vector::m_end = vector::m_begin + size;

            // Populate new elements.
            for(auto entry = original_end; entry < vector::m_end; entry++)
            {
                *entry = value;
            }
        }
        // Check if size is smaller than the current size.
        else if(size < vector::m_end - vector::m_begin)
        {
            // Decreasing size of container.

            // Update end to lesser value.
            vector::m_end = vector::m_begin + size;
        }
        // Otherwise, size = vector size and nothing needs to be done.

        // Indicate success.
        return true;
    }
    /// \brief Copy-assigns the contents of this vector from another vector.
    /// \param[in] other The other vector to copy-assign from.
    /// \return TRUE if the assignment succeeded, FALSE if this vector does not have enough capacity.
    bool operator=(const std::vector<object_type>& other)
    {
        // Calculate size of other vector.
        std::size_t size = other.m_end - other.m_begin;

        // Verify space in the container.
        if(vector::m_capacity - vector::m_begin < size)
        {
            return false;
        }

        // Update end.
        vector::m_end = vector::m_begin + size;

        // Copy values.
        auto destination = vector::m_begin;
        auto source = other.m_begin;
        while(destination < vector::m_end)
        {
            *destination++ = *source++;
        }

        // Indicate success.
        return true;
    }
    /// \brief Swaps the contents of this vector with another vector.
    /// \param[in] other The other vector to swap with.
    void swap(std::vector<object_type>& other)
    {
        // Store this vector's pointers in a temporary.
        auto temp_begin = vector::m_begin;
        auto temp_end = vector::m_end;
        auto temp_capacity = vector::m_capacity;

        // Store the other vector's pointers in this vector.
        vector::m_begin = other.m_begin;
        vector::m_end = other.m_end;
        vector::m_capacity = other.m_capacity;

        // Store this vector's original pointers in the other vector.
        other.m_begin = temp_begin;
        other.m_end = temp_end;
        other.m_capacity = temp_capacity;
    }

    // COMPARISON
    /// \brief Checks if this vector is equal to another vector.
    /// \param[in] other The other vector to compare with.
    /// \return TRUE if the two vectors are equal, otherwise FALSE.
    bool operator==(const std::vector<object_type>& other)
    {
        // Verify vector sizes match.
        if(vector::m_end - vector::m_begin != other.m_end - other.m_begin)
        {
            return false;
        }

        // Compare values.
        auto this_entry = vector::m_begin;
        auto other_entry = other.m_begin;
        while(this_entry < vector::m_end)
        {
            if(*this_entry++ != *other_entry++)
            {
                return false;
            }
        }

        // Indicate equal.
        return true;
    }
};

}

#endif