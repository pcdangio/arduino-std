/// \file std/utility/remove_reference.hpp
/// \brief Defines the std::remove_reference template function.
#ifndef STD___UTILITY___REMOVE_REFERENCE_H
#define STD___UTILITY___REMOVE_REFERENCE_H

namespace std {

/// \brief Removes lvalue and rvalue references from an object type.
/// \tparam object_type The type of the object to remove references from.
template <typename object_type>
struct remove_reference
{
    /// \brief Captures the object type with lvalue and rvalue references removed.
    using type = object_type;
};

/// \brief Removes lvalue and rvalue references from an object type.
/// \tparam object_type The type of the object to remove references from.
template <typename object_type>
struct remove_reference<object_type&>
{
    /// \brief Captures the object type with lvalue and rvalue references removed.
    using type = object_type;
};

/// \brief Removes lvalue and rvalue references from an object type.
/// \tparam object_type The type of the object to remove references from.
template <typename object_type>
struct remove_reference<object_type&&>
{
    /// \brief Captures the object type with lvalue and rvalue references removed.
    using type = object_type;
};

}

#endif