/// \file std/memory/shared_ptr.hpp
/// \brief Defines the std::shared_ptr class.
#ifndef STD___SHARED_PTR_H
#define STD___SHARED_PTR_H

// std
#include <std/memory/smart_ptr.hpp>

namespace std {

/// \brief A smart pointer that retains shared ownership of an object through a pointer.
/// \tparam object_type The managed object's type.
template <class object_type>
class shared_ptr
    : public std::memory::smart_ptr<object_type>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs an empty shared_ptr instance.
    shared_ptr()
        : std::memory::smart_ptr<object_type>(nullptr),
          m_reference_count(nullptr)
    {}
    /// \brief Constructs a shared_ptr instance that takes ownership over an existing raw pointer.
    /// \param instance The existing raw pointer to take ownership over.
    shared_ptr(object_type* instance)
        : std::memory::smart_ptr<object_type>(instance),
          m_reference_count(instance ? new size_t(1) : nullptr)
    {}
    /// \brief Copy-constructs a shared_ptr instance from another shared_ptr.
    /// \param other The other shared_ptr instance to copy from.
    shared_ptr(const shared_ptr<object_type>& other)
        : std::memory::smart_ptr<object_type>(other.m_instance),
          m_reference_count(other.m_reference_count)
    {
        // Increment reference count.
        shared_ptr::increment();
    }
    /// \brief Copy-constructs a shared_ptr instance from another shared_ptr with a different, but implicitly convertible object type.
    /// \tparam other_type The object type of the other shared_ptr.
    /// \param other The other shared_ptr instance to copy from.
    template <class other_type>
    shared_ptr(const shared_ptr<other_type>& other)
        : std::memory::smart_ptr<object_type>(other.m_instance),
          m_reference_count(other.m_reference_count)
    {
        // Increment reference count.
        shared_ptr::increment();
    }
    /// \brief Move-constructs a shared_ptr instance from another shared_ptr.
    /// \param other The other shared_ptr instance to move.
    shared_ptr(shared_ptr<object_type>&& other)
        : std::memory::smart_ptr<object_type>(other.m_instance),
          m_reference_count(other.m_reference_count)
    {
        // Remove instance/reference count from other.
        other.m_instance = nullptr;
        other.m_reference_count = nullptr;

        // Reference count increment not necessary since being moved.
    }
    /// \brief Move-constructs a shared_ptr instance from another shared_ptr with a different, but implicitly convertible object type.
    /// \tparam other_type The object type of the other shared_ptr.
    /// \param other The other shared_ptr instance to move.
    template <class other_type>
    shared_ptr(shared_ptr<other_type>&& other)
        : std::memory::smart_ptr<object_type>(other.m_instance),
          m_reference_count(other.m_reference_count)
    {
        // Remove instance/reference count from other.
        other.m_instance = nullptr;
        other.m_reference_count = nullptr;

        // Reference count increment not necessary since being moved.
    }
    ~shared_ptr()
    {
        // Decrement reference count.
        shared_ptr::decrement();
    }

    // FACTORY
    /// \brief Creates a new object instance and wraps it in a shared_ptr.
    /// \tparam args The variadic argument types that the object will be constructed with.
    /// \param arguments The arguments to forward to the object's constructor.
    /// \return A shared_ptr that owns the created object instance.
    template <class... args>
    static shared_ptr create(args&&... arguments)
    {
        return shared_ptr(new object_type(arguments...));
    }

    // MODIFIERS
    /// \brief Replaces the managed object.
    /// \param instance The raw pointer to take shared ownership over.
    void reset(object_type* instance = nullptr)
    {
        // Decrement reference count.
        shared_ptr::decrement();

        // Update instance and reference count.
        shared_ptr::m_instance = instance;
        shared_ptr::m_reference_count = instance ? new size_t(1) : nullptr;
    }
    /// \brief Copies ownership from another shared_ptr.
    /// \param other The other shared_ptr to copy ownership from.
    /// \return A reference to this shared_ptr.
    shared_ptr<object_type>& operator=(const shared_ptr& other)
    {
        // Check for difference.
        if(this != &other)
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
    /// \param other The other shared_ptr to copy ownership from.
    /// \return A reference to this shared_ptr.
    template <class other_type>
    shared_ptr<object_type>& operator=(const shared_ptr<other_type>& other)
    {
        // Check for difference.
        if(this != &other)
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
    /// \param other The other shared_ptr to move ownership from.
    /// \return A reference to this shared_ptr.
    shared_ptr<object_type>& operator=(shared_ptr&& other)
    {
        // Check for difference.
        if(this != &other)
        {
            // Decrement prior reference count.
            shared_ptr::decrement();

            // Copy new instance/reference count
            shared_ptr::m_instance = other.m_instance;
            shared_ptr::m_reference_count = other.m_reference_count;

            // Clear the source instance / reference count.
            other.m_instance = nullptr;
            other.m_reference_count = nullptr;

            // No increment required as ownership was moved.
        }

        return *this;
    }
    /// \brief Moves ownership from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param other The other shared_ptr to move ownership from.
    /// \return A reference to this shared_ptr.
    template <class other_type>
    shared_ptr<object_type>& operator=(shared_ptr<other_type>&& other)
    {
        // Check for difference.
        if(this != &other)
        {
            // Decrement prior reference count.
            shared_ptr::decrement();

            // Copy new instance/reference count
            shared_ptr::m_instance = other.m_instance;
            shared_ptr::m_reference_count = other.m_reference_count;

            // Clear the source instance / reference count.
            other.m_instance = nullptr;
            other.m_reference_count = nullptr;

            // No increment required as ownership was moved.
        }

        return *this;
    }

private:
    // FRIENDSHIP
    template <class other_type>
    friend class shared_ptr;
    
    // REFERENCE COUNT
    /// \brief The shared raw pointer of the managed object's reference count.
    size_t* m_reference_count;
    /// \brief Increments the reference count.
    void increment()
    {
        // Check if there is a valid reference count.
        if(shared_ptr::m_reference_count)
        {
            // Increment reference count.
            ++*shared_ptr::m_reference_count;
        }
    }
    /// \brief Decrements the reference count, and frees owned resources when no references are left.
    void decrement()
    {
        // Check if there is a valid reference count, decrement it, and check if zero.
        if(shared_ptr::m_reference_count && --*shared_ptr::m_reference_count == 0)
        {
            // Delete instance/reference count.
            delete shared_ptr::m_instance;
            delete shared_ptr::m_reference_count;
        }
    }
};

}

#endif