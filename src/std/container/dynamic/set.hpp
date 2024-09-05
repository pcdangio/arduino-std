/// \file std/container/dynamic/set.hpp
/// \brief Defines the std::set template class.
#ifndef STD___CONTAINER___DYNAMIC___SET_H
#define STD___CONTAINER___DYNAMIC___SET_H

// std
#include <std/container/dynamic/base.hpp>
#include <std/utility/forward.hpp>
#include <std/utility/pair.hpp>

namespace std {

/// \brief A container that stores unique values.
/// \tparam object_type The object type stored by this container.
template <typename object_type>
class set
    : public std::container::dynamic::base<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new empty set instance.
    /// \param[in] capacity The maximum capacity of this set.
    set(std::size_t capacity)
        : std::container::dynamic::base<object_type>(capacity)
    {}
    /// \brief Copy-constructs a new set from an existing set.
    /// \param[in] other The other set to copy-construct from.
    set(const std::set<object_type>& other)
        : std::container::dynamic::base<object_type>(other)
    {}
    /// \brief Move-constructs a new set from an existing set.
    /// \param[in] other The other set to move-construct from.
    set(std::set<object_type>&& other)
        : std::container::dynamic::base<object_type>(std::forward<std::set<object_type>>(other))
    {}

    // LOOKUP
    /// \brief Finds a value in this set.
    /// \param[in] value The value to find.
    /// \return An iterator to the found value, or set::end() if the value is not present in the set.
    std::iterator<object_type> find(const object_type& value) const
    {
        // Create output iterator.
        std::iterator<object_type> entry;

        // Iterate over values.
        for(entry = set::m_begin; entry != set::m_end; ++entry)
        {
            // Check if value matches the desired value.
            if(*entry == value)
            {
                // break loop.
                break;
            }
        }

        // Return the iterator, which, if value was found, points to it, otherwise is m_end.
        return entry;
    }
    /// \brief Checks if this set contains a value.
    /// \param[in] value The value to check.
    /// \return TRUE if the value exists in this set, otherwise FALSE.
    bool contains(const object_type& value) const
    {
        // Iterate over values.
        for(auto entry = set::m_begin; entry != set::m_end; ++entry)
        {
            // Check if value matches the desired value.
            if(*entry == value)
            {
                // Indicate found.
                return true;
            }
        }

        // If this point reached, value wasn't found.
        return false;
    }

    // MODIFIERS
    /// \brief Inserts a new unique value into this set.
    /// \param[in] value The value to insert.
    /// \return A pair containing an iterator to the inserted value, and a boolean indicating if the value was newly inserted.
    /// Returns set::end() and false if the set is at capacity.
    std::pair<std::iterator<object_type>,bool> insert(const object_type& value)
    {
        // Check if set already contains value.
        for(auto entry = set::m_begin; entry != set::m_end; ++entry)
        {
            // Check if value matches the new value.
            if(*entry == value)
            {
                // Return iterator to entry and false for existing value.
                return std::pair<std::iterator<object_type>,bool>(entry, false);
            }
        }

        // Verify capacity.
        if(set::m_end == set::m_capacity)
        {
            // Return iterator to end and false for existing value.
            return std::pair<std::iterator<object_type>,bool>(set::m_end, false);
        }

        // Get iterator to new position and increment end.
        std::iterator<object_type> entry = set::m_end++;

        // Set value at new position.
        *entry = value;

        // Return iterator to entry and false for existing value.
        return std::pair<std::iterator<object_type>,bool>(entry, true);
    }
    /// \brief Erases a value from the set.
    /// \param[in] value The value to erase.
    /// \return TRUE if the value was erased, FALSE if the set did not contain the value.
    bool erase(const object_type& value)
    {
        // Try to find the value in the set.
        for(auto entry = set::m_begin; entry != set::m_end; ++entry)
        {
            // Check if entry equals the value.
            if(*entry == value)
            {
                // Erase at the entry's position.
                std::container::dynamic::base<object_type>::erase(entry);

                // Indicate success.
                return true;
            }
        }

        // Indicate failure; entry was not found.
        return false;
    }
    using std::container::dynamic::base<object_type>::erase;
    /// \brief Copy-assigns the contents of another set to this set.
    /// \param[in] other The other set to copy-assign from.
    /// \return A reference to this set.
    std::set<object_type>& operator=(const std::set<object_type>& other)
    {
        // Use base container's operator= function.
        std::container::dynamic::base<object_type>::operator=(other);

        return *this;
    }
    /// \brief Move-assigns the contents of another set to this set.
    /// \param[in] other The other set to move-assign from.
    /// \return A reference to this set.
    std::set<object_type>& operator=(std::set<object_type>&& other)
    {
        // Use base container's operator= function.
        std::container::dynamic::base<object_type>::operator=(std::forward<std::set<object_type>>(other));

        return *this;
    }
    /// \brief Swaps the contents of this set with another set.
    /// \param[in] other The other set to swap with.
    void swap(std::set<object_type>* other)
    {
        // Use base container's swap function.
        std::container::dynamic::base<object_type>::swap(other);
    }

    // COMPARISON
    /// \brief Checks if this set is equal to another set.
    /// \param[in] other The other set to compare with.
    /// \return TRUE if the two sets are equal, otherwise FALSE.
    bool operator==(const std::set<object_type>& other) const
    {
        // Use base container's operator== function.
        return std::container::dynamic::base<object_type>::operator==(other);
    }
    /// \brief Checks if this set is unequal with another set.
    /// \param[in] other The other set to compare with.
    /// \return TRUE if the two sets are unequal, otherwise FALSE.
    bool operator!=(const std::set<object_type>& other) const
    {
        // Use base container's operator!= function.
        return std::container::dynamic::base<object_type>::operator!=(other);
    }
};

}

#endif