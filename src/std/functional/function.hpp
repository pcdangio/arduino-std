/// \file std/functional/function.hpp
/// \brief Defines the std::function template class.
#ifndef STD___FUNCTIONAL___FUNCTION_H
#define STD___FUNCTIONAL___FUNCTION_H

// std
#include <std/functional/callable/global.hpp>
#include <std/functional/callable/member.hpp>

namespace std {

// FORWARD DECLARATIONS
/// \brief An object that can store and call upon a function pointer.
/// \tparam function_type The signature of the function.
template <typename function_type>
class function;

/// \brief An object that can store and call upon  a function pointer.
/// \tparam return_type The return type of the function.
/// \tparam argument_types The argument type(s) of the function.
template <typename return_type, typename... argument_types>
class function<return_type(argument_types...)>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs an empty function instance.
    function()
        : m_callable(nullptr)
    {}
    /// \brief Constructs a new function instance that points to a global function.
    /// \param function The global function to point to.
    function(return_type(*function)(argument_types...))
        : m_callable(new std::functional::callable::global<return_type,argument_types...>(function))
    {}
    /// \brief Constructs a new function instance that points to a class member function.
    /// \tparam class_type The object type of the member function's parent class.
    /// \param[in] function The member function to point to.
    /// \param[in] instance The class instance to call the member function through.
    template <class class_type>
    function(return_type(class_type::*function)(argument_types...), class_type* instance)
        : m_callable(new std::functional::callable::member<class_type,return_type,argument_types...>(function, instance))
    {}
    /// \brief Copy-constructs a new function instance from another function.
    /// \param[in] other The other function to copy-construct from.
    function(const std::function<return_type(argument_types...)>& other)
        : m_callable(other.m_callable ? other.m_callable->clone() : nullptr)
    {}
    /// \brief Move-constructs a new function instance from another function.
    /// \param[in] other The other function to move-construct from.
    function(std::function<return_type(argument_types...)>&& other)
        : m_callable(other.m_callable)
    {
        // Reset other's callable pointer.
        other.m_callable = nullptr;
    }
    ~function()
    {
        // Clean up callable.
        if(function::m_callable)
        {
            delete function::m_callable;
        }
    }

    // MODIFIERS
    /// \brief Swaps the internal function pointers between this function and another function.
    /// \param[in] other The other function to swap with.
    void swap(std::function<return_type(argument_types...)>& other)
    {
        // Store this function's callable in a temporary.
        std::functional::callable::base<return_type,argument_types...>* temporary = function::m_callable;

        // Store other function's callable in this function.
        function::m_callable = other.m_callable;

        // Store this function's callable in the other function.
        other.m_callable = temporary;
    }
    /// \brief Copy-assigns another function to this function.
    /// \param[in] other The other function to copy-assign from.
    /// \return A reference to this function.
    std::function<return_type(argument_types...)>& operator=(const std::function<return_type(argument_types...)>& other)
    {
        // Delete current callable if required.
        if(function::m_callable)
        {
            delete function::m_callable;
        }

        // Check if other function's callable is valid.
        if(other.m_callable)
        {
            // Clone other function's callable into this function's callable.
            function::m_callable = other.m_callable->clone();
        }
        else
        {
            // Assign nullptr to this function's callable.
            function::m_callable = nullptr;
        }

        return *this;
    }
    /// \brief Move-assigns another function to this function.
    /// \param[in] other The other function to move-assign from.
    /// \return A reference to this function.
    std::function<return_type(argument_types...)>& operator=(std::function<return_type(argument_types...)>&& other)
    {
        // Delete current callable if required.
        if(function::m_callable)
        {
            delete function::m_callable;
        }

        // Move other function's callable into this function's callable.
        function::m_callable = other.m_callable;
        other.m_callable = nullptr;

        return *this;
    }

    // INVOKE
    /// \brief Invokes the function.
    /// \param[in] arguments The arguments(s) to invoke this function with.
    /// \return The return value of the function.
    return_type operator()(const argument_types&... arguments) const
    {
        return function::m_callable->operator()(arguments...);
    }

    // COMPARISON
    /// \brief Indicates if this function is valid and can be invoked.
    /// \return TRUE if the function has a valid pointer, otherwise FALSE.
    operator bool() const
    {
        // Check if callable exists, and if callable itself is valid.
        return (function::m_callable != nullptr) && *function::m_callable;
    }

private:
    /// \brief The callable object stored by this function.
    std::functional::callable::base<return_type,argument_types...>* m_callable;
};

}

#endif