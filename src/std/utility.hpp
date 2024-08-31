/// \file std/utility.hpp
/// \brief Declares std utility functions.
#ifndef STD___UTILITY_H
#define STD___UTILITY_H

namespace std {

/// \brief Forwards a value while maintaining its value category.
/// \tparam object_type The type of the object to be forwardd.
/// \param[in] object The object to forward.
/// \return The value with it's value category preserved.
template <typename object_type>
object_type&& forward(object_type& object)
{
    // Convert the object to an r_value reference.
    return static_cast<object_type&&>(object);
}

/// \brief Converts an object to an r_value reference to be moved.
/// \tparam object_type The type of the object to be moved.
/// \param[in] object The object to convert to an r_value reference.
/// \return An r_value reference to the object.
template <typename object_type>
object_type&& move(object_type& object)
{
    // Convert the object to an r_value reference.
    return static_cast<object_type&&>(object);
}

}

#endif