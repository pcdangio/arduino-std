#ifndef STD___CONTAINER___BASE_H
#define STD___CONTAINER___BASE_H

// std
#include <std/container/iterator.hpp>

// arduino
#include <Arduino.h>

/// \brief Contains all code for standard library components.
namespace std {

/// \brief Contains all code for std container components.
namespace container {

template <typename object_type>
class base
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new base container instance.
    /// \param[in] capacity The capacity of the container's contiguous memory.
    /// \param[in] size The size of the container's populated contiguous memory.
    base(size_t capacity, size_t size)
        : m_begin(new object_type[capacity]),
          m_end(m_begin + size)
    {}
    ~base()
    {
        // Free container memory if necessary.
        if(base::m_begin)
        {
            delete [] base::m_begin;
        }
    }

    // ACCESS
    /// \brief Gets an iterator to the beginning of the container.
    /// \return The begin iterator.
    std::iterator<object_type> begin() const
    {
        return base::m_begin;
    }
    /// \brief Gets an iterator to the end of the container.
    /// \return The end iterator.
    std::iterator<object_type> end() const
    {
        return base::m_end;
    }
    /// \brief Gets a const_iterator to the beginning of the container.
    /// \return The begin const_iterator.
    std::const_iterator<object_type> cbegin() const
    {
        return base::m_begin;
    }
    /// \brief Gets a const_iterator to the end of the container.
    /// \return The end const_iterator.
    std::const_iterator<object_type> cend() const
    {
        return base::m_end;
    }

    // PROPERTIES
    /// \brief Gets the size of the container.
    /// \return The size of the container.
    size_t size() const
    {
        return base::m_end - base::m_begin;
    }

protected:
    // MEMORY
    /// \brief Stores a pointer to the beginning of the container's contiguous memory.
    object_type* m_begin;
    /// \brief Stores a pointer to the end of the container's populated contiguous memory.
    object_type* m_end;
};


}

}

#endif