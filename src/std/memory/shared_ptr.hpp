/// \file std/memory/shared_ptr.hpp
/// \brief Defines the std::shared_ptr class.
#ifndef STD___SHARED_PTR_H
#define STD___SHARED_PTR_H

// arduino
#include <Arduino.h>

/// \brief Contains all code for the Arduino Standard Library implementation.
namespace std {

/// \brief A smart pointer that retains shared ownership of an object through a pointer.
/// \tparam object_type The managed object's type.
template <class object_type>
class shared_ptr
{
public:
    // CONSTRUCTORS
    /// \brief Constructs an empty shared_ptr instance.
    shared_ptr()
        : m_instance(nullptr),
          m_reference_count(nullptr)
    {}
    /// \brief Constructs a shared_ptr instance that takes ownership over an existing raw pointer.
    /// \param instance The existing raw pointer to take ownership over.
    shared_ptr(object_type* instance)
        : m_instance(instance),
          m_reference_count(instance ? new size_t(1) : nullptr)
    {}
    /// \brief Copy-constructs a shared_ptr instance from another shared_ptr.
    /// \param other The other shared_ptr instance to copy from.
    shared_ptr(const shared_ptr<object_type>& other)
        : m_instance(other.m_instance),
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
        : m_instance(other.m_instance),
          m_reference_count(other.m_reference_count)
    {
        // Increment reference count.
        shared_ptr::increment();
    }
    /// \brief Move-constructs a shared_ptr instance from another shared_ptr.
    /// \param other The other shared_ptr instance to move.
    shared_ptr(shared_ptr<object_type>&& other)
        : m_instance(other.m_instance),
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
        : m_instance(other.m_instance),
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
    /// \brief Releases ownership of the managed object.
    void reset()
    {
        // Decrement reference count.
        shared_ptr::decrement();

        // Clear instance/reference count.
        shared_ptr::m_instance = nullptr;
        shared_ptr::m_reference_count = nullptr;
    }
    /// \brief Copies ownership from another shared_ptr.
    /// \param other The other shared_ptr to copy ownership from.
    /// \return A reference to this shared_ptr.
    shared_ptr<object_type>& operator=(const shared_ptr& other)
    {
        // Copy assign.
        shared_ptr::copy_assign(other.m_instance, other.m_reference_count);

        return *this;
    }
    /// \brief Copies ownership from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param other The other shared_ptr to copy ownership from.
    /// \return A reference to this shared_ptr.
    template <class other_type>
    shared_ptr<object_type>& operator=(const shared_ptr<other_type>& other)
    {
        // Copy assign.
        shared_ptr::copy_assign(other.m_instance, other.m_reference_count);

        return *this;
    }
    /// \brief Moves ownership from another shared_ptr.
    /// \param other The other shared_ptr to move ownership from.
    /// \return A reference to this shared_ptr.
    shared_ptr<object_type>& operator=(shared_ptr&& other)
    {
        // Move assign.
        shared_ptr::move_assign(other.m_instance, other.m_reference_count);

        return *this;
    }
    /// \brief Moves ownership from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param other The other shared_ptr to move ownership from.
    /// \return A reference to this shared_ptr.
    template <class other_type>
    shared_ptr<object_type>& operator=(shared_ptr<other_type>&& other)
    {
        // Move assign.
        shared_ptr::move_assign(other.m_instance, other.m_reference_count);

        return *this;
    }

    // ACCESS
    /// \brief Gets the raw pointer that this shared_ptr manages.
    /// \return The managed raw pointer.
    object_type* get() const
    {
        return shared_ptr::m_instance;
    }
    /// \brief Dereferences the managed object.
    /// \return A reference to the managed object.
    object_type& operator*() const
    {
        return *shared_ptr::m_instance;
    }
    /// \brief Dereferences the managed object.
    /// \return A pointer to the managed object.
    object_type* operator->() const
    {
        return shared_ptr::m_instance;
    }

    // COMPARISON
    /// \brief Checks if this shared_ptr manages the same object as another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param other The other shared_ptr.
    /// \return TRUE if both shared_ptrs manage the same object, otherwise FALSE.
    template <class other_type>
    bool operator==(const shared_ptr<other_type>& other)
    {
        return shared_ptr::m_instance == other.m_instance;
    }
    /// \brief Checks if this shared_ptr manages the a different object from another shared_ptr.
    /// \tparam other_type The object type of the other shared_ptr. If different from this shared_ptr, the object type must be implicitly convertible.
    /// \param other The other shared_ptr.
    /// \return TRUE if the shared_ptrs manage different objects, otherwise FALSE.
    template <class other_type>
    bool operator!=(const shared_ptr<other_type>& other)
    {
        return shared_ptr::m_instance != other.m_instance;
    }

    // PROPERTIES
    /// \brief Checks if the shared_ptr has a valid object instance.
    /// \return TRUE if the object instance is valid, FALSE if the object instance is nullptr.
    operator bool() const
    {
        return shared_ptr::m_instance != nullptr;
    }
    /// \brief Checks if the shared_ptr has a valid object instance.
    /// \return TRUE if the object instance is valid, FALSE if the object instance is nullptr.
    bool valid() const
    {
        return shared_ptr::m_instance != nullptr;
    }

private:
    // FRIENDSHIP
    template <class other_type>
    friend class shared_ptr;

    // INSTANCE
    /// \brief The shared raw pointer of the managed object instance.
    object_type* m_instance;
    
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
    
    // ASSIGNMENT
    /// \brief Copy assigns another shared_ptr instance.
    /// \param instance The instance from the other shared_ptr.
    /// \param reference_count The reference_ount from the other shared_ptr.
    void copy_assign(object_type* instance, size_t* reference_count)
    {
        // Decrement prior reference count.
        shared_ptr::decrement();

        // Copy source instance/reference count.
        shared_ptr::m_instance = instance;
        shared_ptr::m_reference_count = reference_count;

        // Increment new reference count.
        shared_ptr::increment();
    }
    /// \brief Move assigns another shared_ptr instance.
    /// \param instance The instance from the other shared_ptr.
    /// \param reference_count The reference_ount from the other shared_ptr.
    void move_assign(object_type*& instance, size_t*& reference_count)
    {
        // Decrement prior reference count.
        shared_ptr::decrement();

        // Copy new instance/reference count
        shared_ptr::m_instance = instance;
        shared_ptr::m_reference_count = reference_count;

        // Clear the source instance / reference count.
        instance = nullptr;
        reference_count = nullptr;

        // No increment required as ownership was moved.
    }
};

}

#endif