/// \file std/container/iterator.hpp
/// \brief Defines the std::iterator and std::const_iterator class.
#ifndef STD___ITERATOR_H
#define STD___ITERATOR_H

namespace std {

/// \brief An iterator for traversing through a container.
/// \tparam object_type The object type of the container.
template <typename object_type>
using iterator = object_type*;

/// \brief A const iterator for traversing through a container.
/// \tparam object_type The object type of the container.
template <typename object_type>
using const_iterator = const object_type*;

}

#endif