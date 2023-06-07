/// \file std/container/dynamic/map.hpp
/// \brief Defines the std::map class.
#ifndef STD___MAP_H
#define STD___MAP_H

// std
#include <std/container/dynamic/dynamic.hpp>
#include <std/container/key_value.hpp>

namespace std {

/// \brief A map of key/value pairs.
/// \tparam key_type The object type of the map keys.
/// \tparam value_type The object type of the map values.
template <typename key_type, typename value_type>
class map
    : public std::container::dynamic<std::container::key_value<key_type,value_type>>
{
public:
    // CONSTRUCTOR
    /// \brief Constructs a new map instance.
    /// \param capacity The maximum capacity of the map.
    map(size_t capacity)
        : std::container::dynamic<std::container::key_value<key_type,value_type>>(capacity)
    {}

    // MODIFIERS
    /// \brief Inserts or updates a key/value pair in the map.
    /// \param key The key of the pair.
    /// \param value The value of the pair.
    /// \return TRUE if the map now contains the key/value pair, FALSE if the map is at capacity.
    bool insert(const key_type& key, const value_type& value)
    {
        // Try to find existing key.
        auto entry = map::find(key);

        // Check if entry was found.
        if(entry != map::m_end)
        {
            // Update the value.
            entry->value = value;
            // Indicate success.
            return true;
        }

        // Check for space.
        if(map::m_end == map::m_capacity)
        {
            return false;
        }

        // Add new key value pair.
        map::m_end->key = key;
        map::m_end->value = value;

        // Increment end pointer.
        ++map::m_end;

        return true;
    }
    /// \brief Erases a key/value pair from the map.
    /// \param key The key of the pair to erase.
    /// \return TRUE if the key/value pair was erased, FALSE if it did not exist in the map.
    bool erase(const key_type& key)
    {
        // Try to find key.
        auto entry = map::find(key);

        // Check if key was found.
        if(entry == map::m_end)
        {
            return false;
        }

        // Shift subset at entry location forwards.
        map::shift_forward(entry, 1);

        return true;
    }

    // ACCESS
    /// \brief Finds a key/value pair in the map.
    /// \param key The key of the pair to find.
    /// \return An iterator to the key/value pair.
    std::iterator<std::container::key_value<key_type,value_type>> find(const key_type& key)
    {
        // Iterate through the key/value pair array.
        auto entry = map::m_begin;
        for(; entry != map::m_end; ++entry)
        {
            // Check if the entry's key matches the given key.
            if(entry->key == key)
            {
                break;
            }
        }

        // Return iterator to entry/end.
        return entry;
    }
    /// \brief Finds a key/value pair in the map.
    /// \param key The key of the pair to find.
    /// \return A const iterator to the key/value pair.
    std::const_iterator<std::container::key_value<key_type,value_type>> find(const key_type& key) const
    {
        // Iterate through the key/value pair array.
        auto entry = map::m_begin;
        for(; entry != map::m_end; ++entry)
        {
            // Check if the entry's key matches the given key.
            if(entry->key == key)
            {
                break;
            }
        }

        // Return iterator to entry/end.
        return entry;
    }
    /// \brief Gets a reference to the value for the specified key.
    /// \param key The key of the value to get.
    /// \return A reference to the value.
    value_type& operator[](const key_type& key)
    {
        // Find key and return it's value.
        return map::find(key)->value;
    }
    /// \brief Gets a reference to the value for the specified key.
    /// \param key The key of the value to get.
    /// \return A const reference to the value.
    const value_type& operator[](const key_type& key) const
    {
        // Find key and return it's value.
        return map::find(key)->value;
    }
    /// \brief Gets a reference to the value for the specified key.
    /// \param key The key of the value to get.
    /// \return A reference to the value.
    value_type& at(const key_type& key)
    {
        // Find key and return it's value.
        return map::find(key)->value;
    }
    /// \brief Gets a reference to the value for the specified key.
    /// \param key The key of the value to get.
    /// \return A const reference to the value.
    const value_type& at(const key_type& key) const
    {
        // Find key and return it's value.
        return map::find(key)->value;
    }

    // INSPECTION
    /// \brief Checks if the map contains a specific key.
    /// \param key The key to check the map for.
    /// \return TRUE if the map contains the key, otherwise FALSE.
    bool contains(const key_type& key) const
    {
        // Try to find key.
        auto entry = map::find(key);

        // Check if entry is not end.
        return entry != map::m_end;
    }
};

}

#endif