/// \file std/stddef.hpp
/// \brief Declares std type definitions.
#ifndef STD___STDDEF_H
#define STD___STDDEF_H

// arduino
#include <Arduino.h>

namespace std {

/// \brief An unsigned integer type large enough to hold the maximum possible size of any object on the system.
using size_t = ::size_t;

}

#endif