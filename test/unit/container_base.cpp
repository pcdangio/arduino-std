// aunit
#include <AUnit.h>

// std
#include <std.hpp>

// TESTS: CONSTRUCTOR
/// \brief Tests the std::container::base constructor.
test(container_base, constructor)
{
    // Specify capacity and size.
    const size_t capacity = 1;
    const size_t size = 0;

    // Create base container.
    std::container::base<uint8_t> container(capacity, size);

    // Verify iterators.
    assertNotEqual(container.begin(), nullptr);
    assertEqual(container.end(), container.begin() + size);
    assertNotEqual(container.cbegin(), nullptr);
    assertEqual(container.cend(), container.cbegin() + size);

    // Verify properties.
    assertEqual(container.size(), size);
}

// TESTS: ITERATORS
/// \brief Tests the std::container::base::begin function.
test(container_base, begin)
{
    // Create base container.
    std::container::base<uint8_t> container(1, 1);

    // Verify begin points to a valid memory address.
    assertNotEqual(container.begin(), nullptr);
}
/// \brief Tests the std::container::base::end function.
test(container_base, end)
{
    // Specify capacity and size.
    const size_t capacity = 1;
    const size_t size = 1;

    // Create base container.
    std::container::base<uint8_t> container(capacity, size);

    // Verify end points to begin + size.
    assertEqual(container.end(), container.begin() + size);
}
/// \brief Tests the std::container::base::cbegin function.
test(container_base, cbegin)
{
    // Create base container.
    std::container::base<uint8_t> container(1, 1);

    // Verify cbegin points to a valid memory address.
    assertNotEqual(container.cbegin(), nullptr);
}
/// \brief Tests the std::container::base::cend function.
test(container_base, cend)
{
    // Specify capacity and size.
    const size_t capacity = 1;
    const size_t size = 1;

    // Create base container.
    std::container::base<uint8_t> container(capacity, size);

    // Verify cend points to cbegin + size.
    assertEqual(container.cend(), container.cbegin() + size);
}

// TESTS: PROPERTIES
/// \brief Tests the std::container::base::size function.
test(container_base, size)
{
    // Specify capacity and size.
    const size_t capacity = 1;
    const size_t size = 1;

    // Create base container.
    std::container::base<uint8_t> container(capacity, size);

    // Verify size returns the correct value.
    assertEqual(container.size(), size);
}