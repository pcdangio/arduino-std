/// \file std/utility/pair.hpp
/// \brief Defines the std::pair template class.
#ifndef STD___UTILITY___PAIR_H
#define STD___UTILITY___PAIR_H

// std
#include <std/utility/forward.hpp>

namespace std {

/// \brief An object which stores two different object types.
/// \tparam first_type The object type of the first value.
/// \tparam second_type The object type of the second value.
template <typename first_type, typename second_type>
struct pair
{
    // CONSTRUCTORS
    /// \brief Constructs a new pair instance with default-constructed values.
    pair() = default;
    /// \brief Constructs a new pair instance with copy-constructed values.
    /// \param[in] first The first value to copy-construct from.
    /// \param[in] second The second value to copy-construct from.
    pair(const first_type& first, const second_type& second)
        : first(first),
          second(second)
    {}
    /// \brief Constructs a new pair instance with move-constructed values.
    /// \param[in] first The first value to move-construct from.
    /// \param[in] second The second value to move-construct from.
    pair(first_type&& first, second_type&& second)
        : first(std::forward<first_type>(first)),
          second(std::forward<second_type>(second))
    {}
    /// \brief Constructs a new pair instance with values copy-constructed from another pair.
    /// \param[in] other The other pair to copy-construct from.
    pair(const std::pair<first_type,second_type>& other)
        : first(other.first),
          second(other.second)
    {}
    /// \brief Constructs a new pair instance with values move-constructed from another pair.
    /// \param[in] other The other pair to move-construct from.
    pair(std::pair<first_type,second_type>&& other)
        : first(std::forward<first_type>(other.first)),
          second(std::forward<second_type>(other.second))
    {}

    // VALUES
    /// \brief The first value within this pair.
    first_type first;
    /// \brief The second value within this pair.
    second_type second;

    // MODIFIERS
    /// \brief Assigns values from another pair to this pair.
    /// \param[in] other The other pair to assign values from.
    void operator=(const std::pair<first_type,second_type>& other)
    {
        // Copy the values from the other pair.
        pair::first = other.first;
        pair::second = other.second;
    }
    /// \brief Swaps the values of this pair with another pair.
    /// \param[in] other The other pair to swap values with.
    void swap(std::pair<first_type,second_type>& other)
    {
        // Create temporaries for swap.
        first_type first_copy = pair::first;
        second_type second_copy = pair::second;

        // Copy other into this pair.
        pair::first = other.first;
        pair::second = other.second;

        // Copy temporaries into other pair.
        other.first = first_copy;
        other.second = second_copy;
    }

    // COMPARISON
    /// \brief Checks if this pair's values are equal to another pair's values.
    /// \param[in] other The other pair to compare values with.
    /// \return TRUE if the pairs have equal values, otherwise FALSE.
    bool operator==(const std::pair<first_type,second_type>& other)
    {
        // Compare both values.
        return (pair::first == other.first) && (pair::second == other.second);
    }
};

}

#endif