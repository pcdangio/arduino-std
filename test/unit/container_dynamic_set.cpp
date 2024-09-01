// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_CONTAINER_DYNAMIC_SET

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::container::dynamic::set {

// UTILITY
/// \brief Fills a set with unique, sequential values.
/// \param[in] set The set to fill.
/// \param[in] size The number of unique values to insert.
void fill_set(std::set<uint8_t>& set, std::size_t size)
{
    for(std::size_t i = 0; i < size; ++i)
    {
        set.insert(i);
    }
}

// LOOKUP
/// \brief Tests the std::set::find function with a valid configuration.
test(container_dynamic_set, find)
{
    // Create and fill a set.
    std::set<uint8_t> set(5);
    fill_set(set, set.capacity());

    // Find all values in the set.
    for(uint8_t i = 0; i < set.capacity(); ++i)
    {
        assertEqual(set.find(i), set.begin() + std::size_t(i));
    }
}
/// \brief Tests the std::set::find function with an empty set.
test(container_dynamic_set, find_empty)
{
    // Create an empty set.
    std::set<uint8_t> set(5);

    // Verify find returns set::end.
    assertEqual(set.find(0xFF), set.end());
}
/// \brief Tests the std::set::find function with a set without the desired value.
test(container_dynamic_set, find_missing)
{
    // Create and fill a set.
    std::set<uint8_t> set(5);
    fill_set(set, set.capacity());

    // Verify find on a nonexistant value returns set::end.
    assertEqual(set.find(0xFF), set.end());
}
/// \brief Tests the std::set::contains function with a valid configuration.
test(container_dynamic_set, contains)
{
    // Create and fill a set.
    std::set<uint8_t> set(5);
    fill_set(set, set.capacity());

    // Check contains on all values in the set.
    for(uint8_t i = 0; i < set.capacity(); ++i)
    {
        assertTrue(set.contains(i));
    }
}
/// \brief Tests the std::set::contains function with an empty set.
test(container_dynamic_set, contains_empty)
{
    // Create an empty set.
    std::set<uint8_t> set(5);

    // Verify contains returns false.
    assertFalse(set.contains(0xFF));
}
/// \brief Tests the std::set::contains function with a set without the desired value.
test(container_dynamic_set, contains_missing)
{
    // Create and fill a set.
    std::set<uint8_t> set(5);
    fill_set(set, set.capacity());

    // Verify contains returns false for a nonexistant value.
    assertFalse(set.contains(0xFF));
}

// MODIFIERS
/// \brief Tests the std::set::insert function with a valid configuration.
test(container_dynamic_set, insert)
{
    // Create an empty set.
    std::set<uint8_t> set(5);

    // Iteratively add unique values and verify success.
    for(uint8_t i = 0; i < set.capacity(); ++i)
    {
        assertTrue(set.insert(i));
    }

    // Verify set contains all values.
    for(uint8_t i = 0; i < set.capacity(); ++i)
    {
        assertTrue(set.contains(i));
    }
}
/// \brief Tests the std::set::insert function with a duplicate value.
test(container_dynamic_set, insert_duplicate_value)
{
    // Create empty set.
    std::set<uint8_t> set(5);

    // Add unique value to set.
    set.insert(0xFF);

    // Verify inserting the same value fails.
    assertFalse(set.insert(0xFF));

    // Verify set size is still only one.
    assertEqual(set.size(), std::size_t(1));

    // Verify set's only value is still the original value.
    assertTrue(set.contains(0xFF));
}
/// \brief Tests the std::set::insert function with not enough capacity.
test(container_dynamic_set, insert_over_capacity)
{
    // Create and fill set.
    std::set<uint8_t> set(5);
    fill_set(set, set.capacity());

    // Verify inserting another unique value fails due to over-capacity.
    assertFalse(set.insert(0xFF));

    // Verify set size is still at capacity.
    assertEqual(set.size(), set.capacity());

    // Verify set contains only original values.
    for(uint8_t i = 0; i < set.capacity(); ++i)
    {
        assertTrue(set.contains(i));
    }
}

}

#endif