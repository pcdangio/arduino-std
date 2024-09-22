/// \file std/memory/smart_ptr/unique_ptr.hpp
/// \brief Defines the std::unique_ptr class.
#ifndef STD___MEMORY___SMART_PTR___UNIQUE_PTR_H
#define STD___MEMORY___SMART_PTR___UNIQUE_PTR_H

// std
#include <std/memory/smart_ptr/base.hpp>
#include <std/utility/forward.hpp>

namespace std {

/// \brief A smart pointer that retains sole ownership of an object through a pointer.
/// \tparam object_type The managed object's type.
template <class object_type>
class unique_ptr
    : public std::memory::smart_ptr::base<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs an empty unique_ptr instance.
    unique_ptr()
        : std::memory::smart_ptr::base<object_type>(nullptr)
    {}
    /// \brief Constructs a unique_ptr instance that takes ownership over an existing raw pointer.
    /// \param[in] instance The existing raw pointer to take ownership over.
    unique_ptr(object_type* instance)
        : std::memory::smart_ptr::base<object_type>(instance)
    {}
    /// \brief Move-constructs a unique_ptr instance from another unique_ptr.
    /// \param[in] other The other unique_ptr instance to move.
    unique_ptr(std::unique_ptr<object_type>&& other)
        : std::memory::smart_ptr::base<object_type>(std::forward<std::unique_ptr<object_type>>(other))
    {
        // Remove instance from other.
        other.m_instance = nullptr;
    }
    /// \brief Move-constructs a unique_ptr instance from another unique_ptr.
    /// \tparam other_type The object type of the other unique_ptr. If different from this unique_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other unique_ptr instance to move.
    template <class other_type>
    unique_ptr(std::unique_ptr<other_type>&& other)
        : std::memory::smart_ptr::base<object_type>(std::forward<std::unique_ptr<other_type>>(other))
    {
        // Remove instance from other.
        other.m_instance = nullptr;
    }
    ~unique_ptr()
    {
        // Free instance if necessary.
        if(unique_ptr::m_instance)
        {
            delete unique_ptr::m_instance;
        }
    }

    // MODIFIERS
    /// \brief Replaces the managed object.
    /// \param[in] instance The raw pointer to take sole ownership over.
    void reset(object_type* instance = nullptr)
    {
        // Free instance.
        delete unique_ptr::m_instance;

        // Update instance.
        unique_ptr::m_instance = instance;
    }
    /// \brief Releases the managed object.
    /// \return A raw pointer to the object instance.
    object_type* release()
    {
        // Create output.
        object_type* output = unique_ptr::m_instance;

        // Clear instance.
        unique_ptr::m_instance = nullptr;

        return output;
    }
    /// \brief Swaps this unique_ptr's managed object with another unique_ptr.
    /// \param[in] other The other unique_ptr to swap with.
    void swap(std::unique_ptr<object_type>& other)
    {
        // Create a temporary copy of this unique_ptr's object.
        object_type* temporary = unique_ptr::m_instance;

        // Assign other unique_ptr's object to this unique_ptr.
        unique_ptr::m_instance = other.m_instance;

        // Assign this unique_ptr's object to other.
        other.m_instance = temporary;
    }
    /// \brief Moves ownership from another unique_ptr.
    /// \param[in] other The other unique_ptr to move ownership from.
    /// \return A reference to this unique_ptr.
    std::unique_ptr<object_type>& operator=(std::unique_ptr<object_type>&& other)
    {
        // Free prior instance.
        delete unique_ptr::m_instance;

        // Copy new instance.
        unique_ptr::m_instance = other.m_instance;

        // Clear the source instance.
        other.m_instance = nullptr;

        return *this;
    }
    /// \brief Moves ownership from another unique_ptr.
    /// \tparam other_type The object type of the other unique_ptr. If different from this unique_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other unique_ptr to move ownership from.
    /// \return A reference to this unique_ptr.
    template <class other_type>
    std::unique_ptr<object_type>& operator=(std::unique_ptr<other_type>&& other)
    {
        // Free prior instance.
        delete unique_ptr::m_instance;

        // Copy new instance.
        unique_ptr::m_instance = other.m_instance;

        // Clear the source instance.
        other.m_instance = nullptr;

        return *this;
    }

    // COMPARISON
    /// \brief Checks if this unique_ptr is equal to another unique_ptr.
    /// \tparam other_type The object type of the other unique_ptr. If different from this unique_ptr, the object must be implicitly convertible.
    /// \param[in] other The other unique_ptr to compare with.
    /// \return TRUE if the two unique_ptrs are equal, otherwise FALSE.
    template <class other_type>
    bool operator==(const std::unique_ptr<other_type>& other) const
    {
        // Use base smart_ptr comparison.
        return std::memory::smart_ptr::base<object_type>::operator==(other);
    }
    /// \brief Checks if this unique_ptr's internally managed pointer is equal to nullptr.
    /// \return TRUE if this unique_ptr's internal pointer is equal to nullptr, otherwise FALSE.
    bool operator==(decltype(nullptr)) const
    {
        // Use base smart_ptr comparison.
        return std::memory::smart_ptr::base<object_type>::operator==(nullptr);
    }
    /// \brief Checks if this unique_ptr is not equal to another unique_ptr.
    /// \tparam other_type The object type of the other unique_ptr. If different from this unique_ptr, the object must be implicitly convertible.
    /// \param[in] other The other unique_ptr to compare with.
    /// \return TRUE if the two unique_ptrs are not equal, otherwise FALSE.
    template <class other_type>
    bool operator!=(const std::unique_ptr<other_type>& other) const
    {
        // Use base smart_ptr comparison.
        return std::memory::smart_ptr::base<object_type>::operator!=(other);
    }
    /// \brief Checks if this unique_ptr's internally managed pointer is not equal to nullptr.
    /// \return TRUE if this unique_ptr's internal pointer is not equal to nullptr, otherwise FALSE.
    bool operator!=(decltype(nullptr)) const
    {
        // Use base smart_ptr comparison.
        return std::memory::smart_ptr::base<object_type>::operator!=(nullptr);
    }

private:
    // FRIENDSHIP
    template <class other_type>
    friend class unique_ptr;
};

// MAKE_UNIQUE
/// \brief Creates a new object instance managed by a unique_ptr.
/// \tparam object_type The managed object's type.
/// \tparam argument_types The variadic argument types that the object will be constructed with.
/// \param[in] arguments The arguments to forward to the object's constructor.
/// \return A unique_ptr that owns the created object instance.
template <class object_type, class... argument_types>
std::unique_ptr<object_type> make_unique(argument_types&&... arguments)
{
    return std::unique_ptr<object_type>(new object_type(std::forward<argument_types>(arguments)...));
}

}

#endif