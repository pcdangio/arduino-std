/// \file std/container/dynamic/map.hpp
/// \brief Defines the std::map template class.
#ifndef STD___CONTAINER___DYNAMIC___MAP_H
#define STD___CONTAINER___DYNAMIC___MAP_H

// std
#include <std/container/dynamic/base.hpp>
#include <std/utility/forward.hpp>
#include <std/utility/pair.hpp>

namespace std {

/// \brief An unsorted associative container that contains key-value pairs with unique keys.
/// \tparam key_type The object type of the map's key.
/// \tparam value_type The object type of the map's value.
template <typename key_type, typename value_type>
class map
    : public std::container::dynamic::base<std::pair<key_type,value_type>>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new map instance.
    /// \param[in] capacity The maximum capacity of the map.
    map(std::size_t capacity)
        : std::container::dynamic::base<std::pair<key_type,value_type>>(capacity)
    {}
    /// \brief Copy-constructs a map instance from another map.
    /// \param[in] other The other map to copy-construct from.
    map(const std::map<key_type,value_type>& other)
        : std::container::dynamic::base<std::pair<key_type,value_type>>(other)
    {}
    /// \brief Move-constructs a map instance from another map.
    /// \param[in] other The other map to move-construct from.
    map(std::map<key_type,value_type>&& other)
        : std::container::dynamic::base<std::pair<key_type,value_type>>(std::forward(other))
    {}

    // LOOKUP
    /// \brief Finds the mapping with a specified key.
    /// \param[in] key The key to find.
    /// \return An iterator to the mapping of the specified key, or map::end() if the key is not present in the map.
    std::iterator<std::pair<key_type,value_type>> find(const key_type& key)
    {
        return map::find_element(key);
    }
    /// \brief Finds the mapping with a specified key.
    /// \param[in] key The key to find.
    /// \return An iterator to the mapping of the specified key, or map::end() if the key is not present in the map.
    std::const_iterator<std::pair<key_type,value_type>> find(const key_type& key) const
    {
        return map::find_element(key);
    }
    /// \brief Checks if a mapping exists for a specified key.
    /// \param[in] key The key to check.
    /// \return TRUE if this map contains the specified key, otherwise FALSE.
    bool contains(const key_type& key) const
    {
        return map::find_element(key) != map::m_end;
    }

    // MODIFIERS
    /// \brief Inserts a key/value mapping into the map.
    /// \param[in] key The key of the mapping.
    /// \param[in] value The value of the mapping.
    /// \return A pair containing an iterator to the inserted value, and a boolean indicating if the mapping was newly inserted.
    /// Returns map::end() and false if the map is at capacity.
    std::pair<std::iterator<std::pair<key_type,value_type>>,bool> insert(const key_type& key, const value_type& value)
    {
        // Check if key already exists in the map.
        auto entry = map::find_element(key);
        if(entry != map::m_end)
        {
            // Map already contains the key.
            // Update the value.
            entry->second = value;
            // Output position to the mapping and false for no new insertion.
            return std::pair<std::iterator<std::pair<key_type,value_type>>,bool>(entry,false);
        }

        // Map does not yet contain the key.

        // Check capacity.
        if(map::m_end == map::m_capacity)
        {
            // Output end position and false for no new insertion.
            return std::pair<std::iterator<std::pair<key_type,value_type>>,bool>(map::m_end, false);
        }

        // Create output pair, storing the new position of the mapping and true for new insertion.
        std::pair<std::iterator<std::pair<key_type,value_type>>,bool> output(map::m_end, true);

        // Get an iterator to the new mapping position at m_end, and increment m_end.
        entry = map::m_end++;

        // Set the key/value.
        entry->first = key;
        entry->second = value;

        // Output entry position and true for new insertion.
        return std::pair<std::iterator<std::pair<key_type,value_type>>,bool>(entry, true);
    }
    /// \brief Copy-assigns the contents of this map from another map.
    /// \param[in] other The other map to copy-assign from.
    /// \return TRUE if the assignment succeeded, otherwise FALSE.
    bool operator=(const std::map<key_type,value_type>& other)
    {
        // Use base container's operator= function.
        return std::container::dynamic::base<std::pair<key_type,value_type>>::operator=(other);
    }
    /// \brief Swaps the contents of this map with another map.
    /// \param[in] other The other map to swap with.
    void swap(std::map<key_type,value_type>* other)
    {
        // Use base container's swap function.
        std::container::dynamic::base<std::pair<key_type,value_type>>::swap(other);
    }

    // COMPARISON
    /// \brief Checks if this map is equal to another map.
    /// \param[in] other The other map to compare with.
    /// \return TRUE if the two maps are equal, otherwise FALSE.
    bool operator==(const std::map<key_type,value_type>& other) const
    {
        // Use base container's operator== function.
        return std::container::dynamic::base<std::pair<key_type,value_type>>::operator==(other);
    }

private:
    // LOOKUP
    /// \brief Finds an element with a specified key.
    /// \param[in] key The key of the element to find.
    /// \return A pointer to the found element, or map::m_end if the map does not contain the element.
    std::pair<key_type,value_type>* find_element(const key_type& key) const
    {
        // Iterate through the map.
        auto entry = map::m_begin;
        for(; entry < map::m_end; ++entry)
        {
            // Check if key matches.
            if(entry->first == key)
            {
                // Break search loop.
                break;
            }
        }

        // Return the current entry iterator.
        return entry;
    }
};

}

#endif