/// \file std/functional/callable/global.hpp
/// \brief Defines the std::functional::callable::global template class.
#ifndef STD___FUNCTIONAL___CALLABLE___GLOBAL_H
#define STD___FUNCTIONAL___CALLABLE___GLOBAL_H

// std
#include <std/functional/callable/base.hpp>

namespace std::functional::callable {

/// \brief A callable that points to a global function.
/// \tparam return_type The return type of the callable.
/// \tparam argument_types The argument type(s) of the callable.
template <typename return_type, typename... argument_types>
class global
    : public std::functional::callable::base<return_type, argument_types...>
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new global callable instance.
    /// \param[in] function The global function to assign to this callable.
    global(return_type(*function)(argument_types...))
        : m_function(function)
    {}

    // OVERRIDES
    return_type operator()(const argument_types&... arguments) const override
    {
        // Call the global function and return the result.
        return (*global::m_function)(arguments...);
    }
    operator bool() const override
    {
        // Verify the function is a valid pointer.
        return global::m_function != nullptr;
    }
    std::functional::callable::base<return_type,argument_types...>* clone() const override
    {
        // Return a deep copy of this global callback.
        return new std::functional::callable::global<return_type,argument_types...>(global::m_function);
    }

private:
    // FUNCTION
    /// \brief The global callback function pointer.
    return_type(* const m_function)(argument_types...);
};

}

#endif