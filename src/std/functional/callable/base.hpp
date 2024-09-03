/// \file std/functional/callable/base.hpp
/// \brief Defines the std::functional::callable::base template class.
#ifndef STD___FUNCTIONAL___CALLABLE___BASE_H
#define STD___FUNCTIONAL___CALLABLE___BASE_H

namespace std {

/// \brief Contains all code for functional components.
namespace functional {

/// \brief Contains all code for callable components.
namespace callable {

/// \brief A base callable object.
/// \tparam return_type The return type of the callable.
/// \tparam argument_types The argument type(s) of the callable.
template <typename return_type, typename... argument_types>
class base
{
public:
    // INVOKE
    /// \brief Invokes the callable.
    /// \param[in] arguments The arguments(s) to invoke this callable with.
    /// \return The return value of the callable.
    virtual return_type operator()(const argument_types&... arguments) const = 0;

    // PROPERTIES
    /// \brief Indicates if this callable can be called.
    /// \return TRUE if the callable points to a valid function, otherwise FALSE.
    virtual operator bool() const = 0;
};

}}}

#endif