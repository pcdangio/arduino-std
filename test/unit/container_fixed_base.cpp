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
    const size_t size = 5;

    // Create container.
    std::container::fixed::base<uint8_t,size> container;
    
    // Verify container size.
    assertEqual(container.size, size);

    // Verify valid begin iterator.
    assertNotEqual(container.begin(), nullptr);

    // Verify valid end iterator.
    assertEqual(container.end(), container.begin() + size);
}
/// \brief Tests the std::container::fixed::base copy constructor.
test(container_fixed_base, constructor_copy)
{
    // Specify size.
    const size_t size = 5;

    // Create and populate container_a.
    std::container::fixed::base<uint8_t,size> container_a;

    // Populate container_a.
    uint8_t i = 0;
    for(auto entry = container_a.begin(); entry != container_a.end(); ++entry, ++i)
    {
        *entry = i;
    }

    // Copy construct container_b from container_a.
    std::container::fixed::base<uint8_t,size> container_b(container_a);

    // Verify container size.
    assertEqual(container_b.size, size);

    // Verify valid begin iterator.
    assertNotEqual(container_b.begin(), nullptr);

    // Verify valid end iterator.
    assertEqual(container_b.end(), container_b.begin() + size);

    // Verify data matches.
    auto a_entry = container_a.begin();
    auto b_entry = container_b.begin();
    for(;b_entry < container_b.end(); ++a_entry,++b_entry)
    {
        assertEqual(*b_entry, *a_entry);
    }
}

// ITERATORS
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
    const size_t size = 5;

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
    const size_t size = 5;

    // Create container.
    std::container::fixed::base<uint8_t,size> container;

    // Verify cend points to a valid memory location.
    assertEqual(container.cend(), container.cbegin() + size);
}

// PROPERTIES
/// \brief Tests the std::container::fixed::base::size value.
test(container_fixed_base, size)
{
    // Specify size.
    const size_t size = 5;

    // Create container.
    std::container::fixed::base<uint8_t,size> container;
    
    // Verify container size.
    assertEqual(container.size, size);
}

}