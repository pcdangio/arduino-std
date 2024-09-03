/// \file std/memory/smart_ptr/shared_ptr.hpp
/// \brief Defines the std::shared_ptr class.
#ifndef STD___MEMORY___SMART_PTR___SHARED_PTR_H
#define STD___MEMORY___SMART_PTR___SHARED_PTR_H

// std
#include <std/memory/smart_ptr/base.hpp>
#include <std/utility/forward.hpp>
#include <std/stddef.hpp>

namespace std {

/// \brief A smart pointer that retains shared ownership of an object through a pointer.
/// \tparam object_type The managed object's type.
template <class object_type>
class shared_ptr
    : public std::memory::smart_ptr::base<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs an empty shared_ptr instance.
    shared_ptr()
        : m_reference_count(nullptr)
    {}
    /// \brief Constructs a shared_ptr instance that takes ownership over an existing raw pointer.
    /// \param[in] instance The existing raw pointer to take ownership over.
    shared_ptr(object_type* instance)
        : std::memory::smart_ptr::base<object_type>(instance),
          m_reference_count(instance ? new std::size_t(1) : nullptr)
    {}
    /// \brief Copy-constructs a shared_ptr instance from another shared_ptr.
    /// \param[in] other The other shared_ptr instance to copy from.
    shared_ptr(const std::shared_ptr<object_type>& other)
        : std::memory::smart_ptr::base<object_type>(other),
          m_reference_count(other.m_reference_count)
    {
        // Increment reference count.
        shared_ptr::increment();
    }
    /// \brief Copy-constructs a shared_ptr instance from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other shared_ptr instance to copy from.
    template <class other_type>
    shared_ptr(const std::shared_ptr<other_type>& other)
        : std::memory::smart_ptr::base<object_type>(other),
          m_reference_count(other.m_reference_count)
    {
        // Increment reference count.
        shared_ptr::increment();
    }
    /// \brief Move-constructs a shared_ptr instance from another shared_ptr.
    /// \param[in] other The other shared_ptr instance to move.
    shared_ptr(std::shared_ptr<object_type>&& other)
        : std::memory::smart_ptr::base<object_type>(std::forward(other)),
          m_reference_count(other.m_reference_count)
    {
        // Remove reference count from other.
        other.m_reference_count = nullptr;

        // Reference count increment not necessary since being moved.
    }
    /// \brief Move-constructs a shared_ptr instance from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other shared_ptr instance to move.
    template <class other_type>
    shared_ptr(std::shared_ptr<other_type>&& other)
        : std::memory::smart_ptr::base<object_type>(std::forward(other)),
          m_reference_count(other.m_reference_count)
    {
        // Remove reference count from other.
        other.m_reference_count = nullptr;

        // Reference count increment not necessary since being moved.
    }
    ~shared_ptr()
    {
        // Decrement reference count.
        shared_ptr::decrement();
    }

    // MODIFIERS
    /// \brief Replaces the managed object.
    /// \param[in] instance The raw pointer to take shared ownership over.
    void reset(object_type* instance = nullptr)
    {
        // Decrement reference count.
        shared_ptr::decrement();

        // Update instance and reference count.
        shared_ptr::m_instance = instance;
        shared_ptr::m_reference_count = instance ? new std::size_t(1) : nullptr;
    }
    /// \brief Swaps this shared_ptr's managed objects with another shared_ptr.
    /// \param[in] other The other shared_ptr to swap with.
    void swap(std::shared_ptr<object_type>& other)
    {
        // Store current instance and reference count in a temporary.
        object_type* temp_instance = shared_ptr::m_instance;
        std::size_t temp_reference_count = shared_ptr::m_reference_count;

        // Store other in this.
        shared_ptr::m_instance = other.m_instance;
        shared_ptr::m_reference_count = other.m_reference_count;

        // Store this in other.
        other.m_instance = temp_instance;
        other.m_reference_count = temp_reference_count;
    }
    /// \brief Copies ownership from another shared_ptr.
    /// \param[in] other The other shared_ptr to copy ownership from.
    /// \return A reference to this shared_ptr.
    shared_ptr<object_type>& operator=(const shared_ptr<object_type>& other)
    {
        // Verify this shared_ptr doesn't already manage the same instance.
        if(shared_ptr::m_instance != other.m_instance)
        {
            // Decrement prior reference count.
            shared_ptr::decrement();

            // Copy source instance/reference count.
            shared_ptr::m_instance = other.m_instance;
            shared_ptr::m_reference_count = other.m_reference_count;

            // Increment new reference count.
            shared_ptr::increment();
        }

        return *this;
    }
    /// \brief Copies ownership from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other shared_ptr to copy ownership from.
    /// \return A reference to this shared_ptr.
    template <class other_type>
    shared_ptr<object_type>& operator=(const shared_ptr<other_type>& other)
    {
        // Verify this shared_ptr doesn't already manage the same instance.
        if(shared_ptr::m_instance != other.m_instance)
        {
            // Decrement prior reference count.
            shared_ptr::decrement();

            // Copy source instance/reference count.
            shared_ptr::m_instance = other.m_instance;
            shared_ptr::m_reference_count = other.m_reference_count;

            // Increment new reference count.
            shared_ptr::increment();
        }

        return *this;
    }
    /// \brief Moves ownership from another shared_ptr.
    /// \param[in] other The other shared_ptr to move ownership from.
    /// \return A reference to this shared_ptr.
    shared_ptr<object_type>& operator=(shared_ptr<object_type>&& other)
    {
        // Decrement the current use count. This applies for both same/different use cases.
        shared_ptr::decrement();

        // Check if instance is different.
        if(shared_ptr::m_instance != other.m_instance)
        {
            // Copy new instance/reference count
            shared_ptr::m_instance = other.m_instance;
            shared_ptr::m_reference_count = other.m_reference_count;
        }

        // Clear the other instance / reference count.
        other.m_instance = nullptr;
        other.m_reference_count = nullptr;

        return *this;
    }
    /// \brief Moves ownership from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param[in] other The other shared_ptr to move ownership from.
    /// \return A reference to this shared_ptr.
    template <class other_type>
    shared_ptr<object_type>& operator=(shared_ptr<other_type>&& other)
    {
        // Decrement the current use count. This applies for both same/different use cases.
        shared_ptr::decrement();

        // Check if instance is different.
        if(shared_ptr::m_instance != other.m_instance)
        {
            // Copy new instance/reference count
            shared_ptr::m_instance = other.m_instance;
            shared_ptr::m_reference_count = other.m_reference_count;
        }

        // Clear the other instance / reference count.
        other.m_instance = nullptr;
        other.m_reference_count = nullptr;

        return *this;
    }

    // OBSERVERS
    /// \brief Gets the current use count of the shared, managed object.
    /// \return The current number of shared owners over the managed object.
    std::size_t use_count() const
    {
        // Check if reference count exists.
        if(!shared_ptr::m_reference_count)
        {
            return 0;
        }

        // Return the current reference count.
        return *shared_ptr::m_reference_count;
    }

private:
    // FRIENDS
    template <typename other_type>
    friend class std::shared_ptr;

    // REFERENCE COUNT
    /// \brief The shared raw pointer of the managed object's reference count.
    std::size_t* m_reference_count;
    /// \brief Increments the reference count.
    void increment()
    {
        // Check if there is a valid reference count.
        if(shared_ptr::m_reference_count)
        {
            // Increment reference count.
            ++(*shared_ptr::m_reference_count);
        }
    }
    /// \brief Decrements the reference count, and frees owned resources when no references are left.
    void decrement()
    {
        // Check if there is a valid reference count, decrement it, and check if zero.
        if(shared_ptr::m_reference_count && (--(*shared_ptr::m_reference_count) == 0))
        {
            // Delete instance/reference count.
            delete shared_ptr::m_instance;
            delete shared_ptr::m_reference_count;

            // Reset them to nullptr.
            shared_ptr::m_instance = nullptr;
            shared_ptr::m_reference_count = nullptr;
        }
    }
};

// MAKE_SHARED
/// \brief Creates a new object instance managed by a shared_ptr.
/// \tparam object_type The managed object's type.
/// \tparam argument_types The variadic argument types that the object will be constructed with.
/// \param[in] arguments The arguments to forward to the object's constructor.
/// \return A shared_ptr that owns the created object instance.
template <class object_type, class... argument_types>
shared_ptr<object_type> make_shared(argument_types&&... arguments)
{
    return shared_ptr<object_type>(new object_type(std::forward<argument_types>(arguments)...));
}

}

#endif