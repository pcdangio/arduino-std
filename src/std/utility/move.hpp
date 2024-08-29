/// \file std/utility/move.hpp
/// \brief Defines the std::move template function.
#ifndef STD___UTILITY___MOVE_H
#define STD___UTILITY___MOVE_H

namespace std {

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