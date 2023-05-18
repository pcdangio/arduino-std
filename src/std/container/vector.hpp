/// \file std/container/vector.hpp
/// \brief Defines the std::vector class.
#ifndef STD___VECTOR_H
#define STD___VECTOR_H

// std
#include <std/container/container.hpp>

namespace std {

/// \brief A vector for storing a variable length array.
/// \tparam object_type 
template <typename object_type>
class vector
    : public std::container<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new vector.
    /// \param capacity The maximum capacity of the vector.
    vector(size_t capacity)
        : std::container<object_type>(capacity)
    {}

    // MODIFIERS
    /// \brief Adds a new value to the back of the vector.
    /// \param value The value to add.
    /// \return TRUE if the value was added, FALSE if the vector is at capacity.
    bool push_back(const object_type& value)
    {
        // Check if there is space to add the object.
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

    // ACCESS
    /// \brief Gets a reference to the object at a specified index.
    /// \param index The index of the object to get.
    /// \return A reference to the object.
    object_type& operator[](size_t index)
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a const reference to the object at a specified index.
    /// \param index The index of the object to get.
    /// \return A const reference to the object.
    const object_type& operator[](size_t index) const
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a reference to the object at a specified index.
    /// \param index The index of the object to get.
    /// \return A reference to the object.
    object_type& at(size_t index)
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a const reference to the object at a specified index.
    /// \param index The index of the object to get.
    /// \return A const reference to the object.
    const object_type& at(size_t index) const
    {
        return *(vector::m_begin + index);
    }
    /// \brief Gets a reference to the first object in the vector.
    /// \return A reference to the first object.
    object_type& front()
    {
        return *vector::m_begin;
    }
    /// \brief Gets a const reference to the first object in the vector.
    /// \return A const reference to the first object.
    const object_type& front() const
    {
        return *vector::m_begin;
    }
    /// \brief Gets a reference to the last object in the vector.
    /// \return A reference to the last object.
    object_type& back()
    {
        return *vector::m_end;
    }
    /// \brief Gets a const reference to the last object in the vector.
    /// \return A const reference to the last object.
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