/// \file std/utility/forward.hpp
/// \brief Defines the std::forward template function.
#ifndef STD___UTILITY___FORWARD_H
#define STD___UTILITY___FORWARD_H

// std
#include <std/utility/remove_reference.hpp>

namespace std {

/// \brief Forwards a value while maintaining its value category.
/// \tparam object_type The type of the object to be forwardd.
/// \param[in] object The object to forward.
/// \return The value with it's value category preserved.
template <typename object_type>
typename std::remove_reference<object_type>::type&& forward(object_type& object)
{
    // Convert the object to an r_value reference.
    return static_cast<typename std::remove_reference<object_type>::type&&>(object);
}

}

#endif