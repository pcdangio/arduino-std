/// \file std/container/key_value.hpp
/// \brief Defines the std::container::key_value class.
#ifndef STD___CONTAINER___KEY_VALUE_H
#define STD___CONTAINER___KEY_VALUE_H

namespace std {
namespace container {

/// \brief A key/value pair.
/// \tparam key_type The object type of the key.
/// \tparam value_type The object type of the value.
template <typename key_type, typename value_type>
struct key_value
{
    /// \brief The key of the key/value pair.
    key_type key;
    /// \brief The value of the key/value pair.
    value_type value;
};

}}

#endif