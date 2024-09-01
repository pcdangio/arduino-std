/// \file container/iterator.hpp
/// \brief Defines the std::container::iterator and std::container::const_iterator type definitions.
#ifndef STD___ITERATOR_H
#define STD___ITERATOR_H

namespace std {
namespace container {

/// \brief An iterator for traversing through a container.
/// \tparam object_type The object type of the container.
template <typename object_type>
using iterator = object_type*;

/// \brief A const iterator for traversing through a container.
/// \tparam object_type The object type of the container.
template <typename object_type>
using const_iterator = const object_type*;

}

/// \brief An iterator for traversing through a container.
/// \tparam object_type The object type of the container.
template <typename object_type>
using iterator = std::container::iterator<object_type>;

/// \brief A const iterator for traversing through a container.
/// \tparam object_type The object type of the container.
template <typename object_type>
using const_iterator = std::container::const_iterator<object_type>;

}

#endif