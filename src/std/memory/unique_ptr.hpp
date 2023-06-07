/// \file std/memory/unique_ptr.hpp
/// \brief Defines the std::unique_ptr class.
#ifndef STD___UNIQUE_PTR_H
#define STD___UNIQUE_PTR_H

// std
#include <std/memory/smart_ptr.hpp>

namespace std {

/// \brief A smart pointer that retains sole ownership of an object through a pointer.
/// \tparam object_type The managed object's type.
template <class object_type>
class unique_ptr
    : public std::memory::smart_ptr<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs an empty unique_ptr instance.
    unique_ptr()
        : std::memory::smart_ptr<object_type>(nullptr)
    {}
    /// \brief Constructs a unique_ptr instance that takes ownership over an existing raw pointer.
    /// \param instance The existing raw pointer to take ownership over.
    unique_ptr(object_type* instance)
        : std::memory::smart_ptr<object_type>(instance)
    {}
    /// \brief Move-constructs a unique_ptr instance from another unique_ptr.
    /// \param other The other unique_ptr instance to move.
    unique_ptr(unique_ptr<object_type>&& other)
        : std::memory::smart_ptr<object_type>(other.m_instance)
    {
        // Remove instance from other.
        other.m_instance = nullptr;
    }
    /// \brief Move-constructs a unique_ptr instance from another unique_ptr with a different, but implicitly convertible object type.
    /// \tparam other_type The object type of the other unique_ptr.
    /// \param other The other unique_ptr instance to move.
    template <class other_type>
    unique_ptr(unique_ptr<other_type>&& other)
        : std::memory::smart_ptr<object_type>(other.m_instance)
    {
        // Remove instance from other.
        other.m_instance = nullptr;
    }
    ~unique_ptr()
    {
        // Free instance.
        delete unique_ptr::m_instance;
    }

    // FACTORY
    /// \brief Creates a new object instance and wraps it in a unique_ptr.
    /// \tparam args The variadic argument types that the object will be constructed with.
    /// \param arguments The arguments to forward to the object's constructor.
    /// \return A unique_ptr that owns the created object instance.
    template <class... args>
    static unique_ptr create(args&&... arguments)
    {
        return unique_ptr(new object_type(arguments...));
    }

    // MODIFIERS
    /// \brief Releases ownership of the managed object.
    void reset()
    {
        // Free instance.
        delete unique_ptr::m_instance;

        // Clear instance.
        unique_ptr::m_instance = nullptr;
    }
    /// \brief Moves ownership from another unique_ptr.
    /// \param other The other unique_ptr to move ownership from.
    /// \return A reference to this unique_ptr.
    unique_ptr<object_type>& operator=(unique_ptr&& other)
    {
        // Move assign.
        unique_ptr::move_assign(other.m_instance, other.m_reference_count);

        return *this;
    }
    /// \brief Moves ownership from another unique_ptr.
    /// \tparam other_type The object type of the other unique_ptr. If different from this unique_ptr, the object type must be implicitly convertible.
    /// \param other The other unique_ptr to move ownership from.
    /// \return A reference to this unique_ptr.
    template <class other_type>
    unique_ptr<object_type>& operator=(unique_ptr<other_type>&& other)
    {
        // Move assign.
        unique_ptr::move_assign(other.m_instance, other.m_reference_count);

        return *this;
    }

private:
    // FRIENDSHIP
    template <class other_type>
    friend class unique_ptr;
    
    // ASSIGNMENT
    /// \brief Move assigns another unique_ptr instance.
    /// \param instance The instance from the other unique_ptr.
    /// \param reference_count The reference_ount from the other unique_ptr.
    void move_assign(object_type*& instance)
    {
        // Free prior instance.
        delete unique_ptr::m_instance;

        // Copy new instance count
        unique_ptr::m_instance = instance;

        // Clear the source instance.
        instance = nullptr;
    }
};

}

#endif