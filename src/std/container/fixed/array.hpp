/// \file std/container/fixed/array.hpp
/// \brief Defines the std::array class.
#ifndef STD___CONTAINER___FIXED___ARRAY_H
#define STD___CONTAINER___FIXED___ARRAY_H

// std
#include <std/container/fixed/base.hpp>

namespace std {

/// \brief A fixed-size array container.
/// \tparam object_type The type of object stored in the array container.
/// \tparam size_value The size of the array container.
template <typename object_type, std::size_t size_value>
class array
    : public std::container::fixed::base<object_type,size_value>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new array instance.
    array() = default;
    /// \brief Copy constructs a new array instance from another.
    /// \param[in] other The other array to copy construct from.
    array(const std::array<object_type,size_value>& other)
        : std::container::fixed::base<object_type,size_value>(other)
    {}
    array(std::array<object_type,size_value>&& other) = delete;

    // ACCESS
    /// \brief Gets a reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A reference to the value.
    object_type& operator[](std::size_t index)
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& operator[](std::size_t index) const
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A reference to the value.
    object_type& at(std::size_t index)
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a const reference to the value at a specified index.
    /// \param[in] index The index of the value to get.
    /// \return A const reference to the value.
    const object_type& at(std::size_t index) const
    {
        return *(array::m_begin + index);
    }
    /// \brief Gets a reference to the first value in the vector.
    /// \return A reference to the first value.
    object_type& front()
    {
        return *array::m_begin;
    }
    /// \brief Gets a const reference to the first value in the vector.
    /// \return A const reference to the first value.
    const object_type& front() const
    {
        return *array::m_begin;
    }
    /// \brief Gets a reference to the last value in the vector.
    /// \return A reference to the last value.
    object_type& back()
    {
        return *(array::m_end - 1);
    }
    /// \brief Gets a const reference to the last value in the vector.
    /// \return A const reference to the last value.
    const object_type& back() const
    {
        return *(array::m_end - 1);
    }
    /// \brief Gets a pointer to the vector's underlying data.
    /// \return A pointer to the underlying data.
    object_type* data()
    {
        return array::m_begin;
    }
    /// \brief Gets a const pointer to the vector's underlying data.
    /// \return A const pointer to the underlying data.
    const object_type* data() const
    {
        return array::m_begin;
    }

    // MODIFIERS
    /// \brief Assigns a specified value to all elements in the array.
    /// \param[in] value The value to assign.
    void fill(const object_type& value)
    {
        // Iterate through the array and assign the value.
        for(auto entry = array::m_begin; entry != array::m_end; ++entry)
        {
            *entry = value;
        }
    }
    /// \brief Swaps the contents of this array with another array.
    /// \param[in] other The other array to swap contents with.
    void swap(std::array<object_type,size_value>& other)
    {
        // Create a temporary for swapping.
        object_type temporary;

        // Iterate through both arrays.
        auto this_entry = array::m_begin;
        auto other_entry = other.m_begin;
        while(this_entry < array::m_end)
        {
            // Store other in temporary.
            temporary = *other_entry;

            // Store this in other and increment other.
            *other_entry++ = *this_entry;

            // Store temporary into this and increment this.
            *this_entry++ = temporary;
        }
    }
    /// \brief Deep-copies another array into this array.
    /// \param[in] other The other array to copy from.
    /// \return A reference to this array.
    std::array<object_type,size_value>& operator=(const std::array<object_type,size_value>& other)
    {
        // Iterate through both arrays.
        auto this_entry = array::m_begin;
        auto other_entry = other.m_begin;
        while(this_entry < array::m_end)
        {
            // Copy value of other to this array.
            *this_entry++ = *other_entry++;
        }

        return *this;
    }

    // COMPARISON
    /// \brief Checks if this array is equal to another array.
    /// \param[in] other The other array to compare with.
    /// \return TRUE if the two arrays are equal, otherwise FALSE.
    bool operator==(const std::array<object_type,size_value>& other) const
    {
        return std::container::fixed::base<object_type,size_value>::operator==(other);
    }
    /// \brief Checks if this array is not equal to another array.
    /// \param[in] other The other array to compare with.
    /// \return TRUE if the two arrays are not equal, otherwise FALSE.
    bool operator!=(const std::array<object_type,size_value>& other) const
    {
        return std::container::fixed::base<object_type,size_value>::operator!=(other);
    }
};

}

#endif