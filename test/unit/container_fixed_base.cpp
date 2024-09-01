// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_CONTAINER_FIXED_BASE

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::container::fixed::base {

// CONSTRUCTORS
/// \brief Tests the std::container::fixed::base default constructor.
test(container_fixed_base, constructor_default)
{
    // Specify size.
    const std::size_t size = 5;

    // Create container.
    std::container::fixed::base<uint8_t,size> container;
    
    // Verify container size.
    assertEqual(container.size(), size);

    // Verify valid begin iterator.
    assertNotEqual(container.begin(), nullptr);

    // Verify valid end iterator.
    assertEqual(container.end(), container.begin() + size);
}
/// \brief Tests the std::container::fixed::base copy constructor.
test(container_fixed_base, constructor_copy)
{
    // Create and populate container_a.
    std::container::fixed::base<uint8_t,5> container_a;

    // Populate container_a.
    uint8_t i = 0;
    for(auto entry = container_a.begin(); entry != container_a.end(); ++entry, ++i)
    {
        *entry = i;
    }

    // Copy construct container_b from container_a.
    std::container::fixed::base<uint8_t,5> container_b(container_a);

    // Verify container sizes match.
    assertEqual(container_b.size(), container_a.size());

    // Verify data matches.
    auto a_entry = container_a.begin();
    auto b_entry = container_b.begin();
    for(;b_entry < container_b.end(); ++a_entry,++b_entry)
    {
        assertEqual(*b_entry, *a_entry);
    }
}

// ACCESS
/// \brief Tests the std::container::fixed::base::begin function.
test(container_fixed_base, begin)
{
    // Create container.
    std::container::fixed::base<uint8_t,5> container;

    // Verify begin points to a valid memory location.
    assertNotEqual(container.begin(), nullptr);
}
/// \brief Tests the std::container::fixed::base::end function.
test(container_fixed_base, end)
{
    // Specify size.
    const std::size_t size = 5;

    // Create container.
    std::container::fixed::base<uint8_t,size> container;

    // Verify end points to a valid memory location.
    assertEqual(container.end(), container.begin() + size);
}
/// \brief Tests the std::container::fixed::base::cbegin function.
test(container_fixed_base, cbegin)
{
    // Create container.
    std::container::fixed::base<uint8_t,5> container;

    // Verify cbegin points to a valid memory location.
    assertNotEqual(container.cbegin(), nullptr);
}
/// \brief Tests the std::container::fixed::base::cend function.
test(container_fixed_base, cend)
{
    // Specify size.
    const std::size_t size = 5;

    // Create container.
    std::container::fixed::base<uint8_t,size> container;

    // Verify cend points to a valid memory location.
    assertEqual(container.cend(), container.cbegin() + size);
}

// CAPACITY
/// \brief Tests the std::container::fixed::base::size value.
test(container_fixed_base, size)
{
    // Specify size.
    const std::size_t size = 5;

    // Create container.
    std::container::fixed::base<uint8_t,size> container;
    
    // Verify container size.
    assertEqual(container.size(), size);
}

}

#endif