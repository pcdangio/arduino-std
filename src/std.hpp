/// \file std.hpp
/// \brief The primary include header for the std library.
#ifndef STD_H
#define STD_H

// CONTAINER
#include <std/container/iterator.hpp>
#include <std/container/fixed/base.hpp>
#include <std/container/fixed/array.hpp>
#include <std/container/dynamic/base.hpp>
#include <std/container/dynamic/map.hpp>
#include <std/container/dynamic/set.hpp>
#include <std/container/dynamic/vector.hpp>

// MEMORY
#include <std/memory/smart_ptr/base.hpp>
#include <std/memory/smart_ptr/unique_ptr.hpp>
#include <std/memory/smart_ptr/shared_ptr.hpp>

// FUNCTIONAL
#include <std/functional/callable/base.hpp>
#include <std/functional/callable/global.hpp>
#include <std/functional/callable/member.hpp>
#include <std/functional/function.hpp>

// UTILITY
#include <std/utility/forward.hpp>
#include <std/utility/move.hpp>
#include <std/utility/pair.hpp>
#include <std/utility/remove_reference.hpp>

// DEFINITIONS
#include <std/stddef.hpp>

#endif