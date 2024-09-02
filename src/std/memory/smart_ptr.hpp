/// \file std/memory/smart_ptr.hpp
/// \brief Defines the std::memory::smart_ptr class.
#ifndef STD___MEMORY___SMART_PTR_H
#define STD___MEMORY___SMART_PTR_H

// arduino
#include <Arduino.h>

namespace std {

/// \brief Contains all code for memory-related components.
namespace memory {

/// \brief A base smart pointer class.
/// \tparam object_type The object type of the pointer managed by this smart pointer.
template <class object_type>
class smart_ptr
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new smart_ptr instance with a nullptr.
    smart_ptr()
        : m_instance(nullptr)
    {}
    /// \brief Constructs a new smart_ptr instance that takes ownership over a raw pointer.
    /// \param[in] instance The existing raw pointer to take ownership over.
    smart_ptr(object_type* instance)
        : m_instance(instance)
    {}
    /// \brief Copy-constructs a new smart_ptr instance from another smart_ptr.
    /// \param[in] other The other smart_ptr to copy-construct from.
    smart_ptr(const std::memory::smart_ptr<object_type>& other)
        : m_instance(other.m_instance)
    {}
    /// \brief Move-constructs a new smart_ptr instance from another smart_ptr.
    /// \param[in] other The other smart_ptr to move-construct from.
    smart_ptr(std::memory::smart_ptr<object_type>&& other)
        : m_instance(other.m_instance)
    {
        // Reset other's instance.
        other.m_instance = nullptr;
    }

    // OBSERVERS
    /// \brief Gets the raw pointer that this smart_ptr manages.
    /// \return The managed raw pointer.
    object_type* get() const
    {
        return smart_ptr::m_instance;
    }
    /// \brief Dereferences the managed object.
    /// \return A reference to the managed object.
    object_type& operator*() const
    {
        return *smart_ptr::m_instance;
    }
    /// \brief Dereferences the managed object.
    /// \return A pointer to the managed object.
    object_type* operator->() const
    {
        return smart_ptr::m_instance;
    }
    /// \brief Checks if the smart_ptr has a valid object instance.
    /// \return TRUE if the object instance is valid, FALSE if the object instance is nullptr.
    operator bool() const
    {
        return smart_ptr::m_instance != nullptr;
    }
    
protected:
    /// \brief The raw instance managed by this smart_ptr.
    object_type* m_instance;

    // COMPARISON
    /// \brief Checks if this smart_ptr manages the same object as another smart_ptr.
    /// \tparam other_type The object type of the other smart_ptr. If different from this smart_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other smart_ptr.
    /// \return TRUE if both smart_ptrs manage the same object, otherwise FALSE.
    template <class other_type>
    bool operator==(const smart_ptr<other_type>& other) const
    {
        return smart_ptr::m_instance == other.m_instance;
    }
    /// \brief Checks if this smart_ptr manages a different object from another smart_ptr.
    /// \tparam other_type The object type of the other smart_ptr. If different from this smart_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other smart_ptr.
    /// \return TRUE if the smart_ptrs manage different objects, otherwise FALSE.
    template <class other_type>
    bool operator!=(const smart_ptr<other_type>& other) const
    {
        return smart_ptr::m_instance != other.m_instance;
    }
};

}}

#endif