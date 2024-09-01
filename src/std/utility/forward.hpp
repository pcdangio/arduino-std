/// \file std/utility/forward.hpp
/// \brief Defines the std::forward template function.
#ifndef STD___UTILITY___FORWARD_H
#define STD___UTILITY___FORWARD_H

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

}

#endif