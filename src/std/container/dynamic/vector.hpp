/// \file std/container/dynamic/vector.hpp
/// \brief Defines the std::vector class.
#ifndef STD___VECTOR_H
#define STD___VECTOR_H

// std
#include <std/container/dynamic/dynamic.hpp>

namespace std {

/// \brief A dynamically-sized array container.
/// \tparam object_type 
template <typename object_type>
class vector
    : public std::container::dynamic<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new vector.
    /// \param capacity The maximum capacity of the vector.
    vector(size_t capacity)
        : std::container::dynamic<object_type>(capacity)
    {}

    // MODIFIERS
    /// \brief Adds a new value to the back of the vector.
    /// \param value The value to add.
    /// \return TRUE if the value was added, FALSE if the vector is at capacity.
    bool push_back(const object_type& value)
    {
        // Check if there is space to add the value.
        if(vector::m_end == vector::m_capacity)
        {
            return false;
        }

        // Add the new value to the end of the array and increment end pointer.
        *vector::m_end++ = value;

        return true;
    }
    /// \brief Removes the last value from the back of the vector.
    void pop_back()
    {
        // Check if vector is empty.
        if(vector::m_begin == vector::m_end)
        {
            return;
        }

        // Decrement end pointer.
        --vector::m_end;
    }
    /// \brief Inserts a new value into the vector.
    /// \param position The position to insert the value into.
    /// \param value The value to insert.
    /// \return TRUE if the value was inserted, FALSE if the vector is at capacity.
    bool insert(std::iterator<object_type> position, const object_type& value)
    {
        // Shift back-end subset backwards.
        if(!vector::shift_backward(position, 1))
        {
            return false;
        }

        // Assign new value.
        *position = value;

        return true;
    }
    /// \brief Inserts a range of new values into the vector.
    /// \param position The position to insert the values into.
    /// \param begin The begin iterator for the values to insert.
    /// \param end The end iterator for the values to insert.
    /// \return TRUE if the values were inserted, FALSE if there is not enough space in the vector.
    bool insert(std::iterator<object_type> position, std::const_iterator<object_type> begin, std::const_iterator<object_type> end)
    {
        // Shift back-end subset backwards.
        if(!vector::shift_backward(position, end-begin))
        {
            return false;
        }

        // Copy entries.
        for(auto source = begin, destination = position; source != end; ++source, ++destination)
        {
            *destination = *source;
        }

        return true;
    }
    /// \brief Fills the vector with a specified value.
    /// \param value The value to fill the vector with.
    void fill(const object_type& value)
    {
        // Iterate through vector and assign value at each position.
        for(auto destination = vector::m_begin; destination != vector::m_end; ++destination)
        {
            *destination = value;
        }
    }
    /// \brief Erases a value at a specified position in the vector.
    /// \param position The position of the value to erase.
    void erase(std::iterator<object_type> position)
    {
        // Shift back-end subset forward.
        vector::shift_forward(position, 1);
    }
    /// @brief Erases a range of values from the vector.
    /// @param begin An iterator to the beginning of the range in the vector.
    /// @param end An iterator to the end of the range in the vector.
    void erase(std::iterator<object_type> begin, std::iterator<object_type> end)
    {
        // Shift back-end subset forward.
        vector::shift_forward(begin, end-begin);
    }
    /// \brief Resizes the vector to a specified size.
    /// \param size The new size to set.
    /// \return TRUE if the resize succeeded, FALSE if vector does not have enough capacity.
    /// \note Indeterminant values will fill the new space if size is increased.
    bool resize(size_t size)
    {
        // Validate new size.
        if(size > vector::capacity)
        {
            return false;
        }

        // Update end position.
        vector::m_end = vector::m_begin + size;

        return true;
    }
    /// \brief Resizes the vector to a specified size.
    /// \param size The new size to set.
    /// \param value The value to fill new space with if size is increased.
    /// \return TRUE if the resize succeeded, FALSE if vector does not have enough capacity.
    bool resize(size_t size, const object_type& value)
    {
        // Store original end position.
        auto original_end = vector::m_end;

        // Try to resize vector.
        if(!vector::resize(size))
        {
            return false;
        }

        // Fill remaining portion of vector (if any).
        for(auto destination = original_end; destination < vector::m_end; ++destination)
        {
            *destination = value;
        }

        return true;
    }

    // ACCESS
    /// \brief Gets a reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A reference to the value.
    object_type& operator[](size_t index)
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& operator[](size_t index) const
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A reference to the value.
    object_type& at(size_t index)
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& at(size_t index) const
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a reference to the first value in the vector.
    /// \return A reference to the first value.
    object_type& front()
    {
        return *vector::m_begin;
    }
    /// \brief Gets a const reference to the first value in the vector.
    /// \return A const reference to the first value.
    const object_type& front() const
    {
        return *vector::m_begin;
    }
    /// \brief Gets a reference to the last value in the vector.
    /// \return A reference to the last value.
    object_type& back()
    {
        return *vector::m_end;
    }
    /// \brief Gets a const reference to the last value in the vector.
    /// \return A const reference to the last value.
    const object_type& back() const
    {
        return *vector::m_end;
    }
    /// \brief Gets a pointer to the vector's underlying data.
    /// \return A pointer to the underlying data.
    object_type* data()
    {
        return vector::m_begin;
    }
    /// \brief Gets a const pointer to the vector's underlying data.
    /// \return A const pointer to the underlying data.
    const object_type* data() const
    {
        return vector::m_begin;
    }
};

}

#endif