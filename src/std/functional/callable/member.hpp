/// \file std/functional/callable/member.hpp
/// \brief Defines the std::functional::callable::member template class.
#ifndef STD___FUNCTIONAL___CALLABLE___MEMBER_H
#define STD___FUNCTIONAL___CALLABLE___MEMBER_H

// std
#include <std/functional/callable/base.hpp>

namespace std::functional::callable {

/// \brief A callable that points to a class member function.
/// \tparam class_type The object type of the function's parent class.
/// \tparam return_type The return type of the callable.
/// \tparam argument_types The argument type(s) of the callable.
template <class class_type, typename return_type, typename... argument_types>
class member
    : public std::functional::callable::base<return_type,argument_types...>
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new member callable instance.
    /// \param[in] function The class member function to assign to this callable.
    /// \param[in] instance The class instance to call this callable through.
    member(return_type(class_type::*function)(argument_types...), class_type* instance)
        : m_function(function),
          m_instance(instance)
    {}

    // OVERRIDES
    return_type operator()(const argument_types&... arguments) const override
    {
        // Call the function pointer through the class instance and return the result.
        return (member::m_instance->*member::m_function)(arguments...);
    }
    operator bool() const override
    {
        // Verify function and class instance are valid pointers.
        return (member::m_function != nullptr) && (member::m_instance != nullptr);
    }

private:
    // FUNCTION
    /// \brief The class member function pointer.
    return_type(class_type::* const m_function)(argument_types...);
    /// \brief The class instance to execute the member function on.
    class_type* const m_instance;
};

}

#endif