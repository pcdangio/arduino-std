// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_CONTAINER_DYNAMIC_MAP

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::container::dynamic::map {

// UTILITY
/// \brief Fills a map with sequential key/value pairs.
/// \param[in] map The map to fill.
/// \param[in] size The number of mappings to insert.
void fill_map(std::map<uint8_t,uint8_t>& map, std::size_t size)
{
    for(std::size_t i = 0; i < size; ++i)
    {
        map.insert(i,i);
    }
}

// LOOKUP
/// \brief Tests the std::map::find function with an existing key.
test(container_dynamic_map, find_existing)
{
    // Create and populate a map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Verify all mappings can be found.
    for(size_t i = 0; i < map.capacity(); ++i)
    {
        assertEqual(map.find(i), map.begin() + i);
    }
}
/// \brief Tests the std::map::find function with an empty map.
test(container_dynamic_map, find_empty)
{
    // Create an empty map.
    std::map<uint8_t,uint8_t> map(5);

    // Verify find returns map::end().
    assertEqual(map.find(0xFF), map.end());
}
/// \brief Tests the std::map::find function with a missing key.
test(container_dynamic_map, find_missing)
{
    // Create and populate a map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Verify find returns map::end() for a non-existent key.
    assertEqual(map.find(0xFF), map.end());
}
/// \brief Tests the std::map::find const function with an existing key.
test(container_dynamic_map, find_const_existing)
{
    // Create and populate a map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Copy-construct a const map.
    std::map<uint8_t,uint8_t> const_map(map);

    // Verify all mappings can be found.
    for(size_t i = 0; i < const_map.capacity(); ++i)
    {
        assertEqual(const_map.find(i), const_map.cbegin() + i);
    }
}
/// \brief Tests the std::map::find const function with an empty map.
test(container_dynamic_map, find_const_empty)
{
    // Create a const empty map.
    const std::map<uint8_t,uint8_t> map(5);

    // Verify find returns map::cend().
    assertEqual(map.find(0xFF), map.cend());
}
/// \brief Tests the std::map::find const function with a missing key.
test(container_dynamic_map, find_const_missing)
{
    // Create and populate a map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Copy-construct a const map.
    std::map<uint8_t,uint8_t> const_map(map);

    // Verify find returns map::cend() for a non-existent key.
    assertEqual(const_map.find(0xFF), const_map.cend());
}
/// \brief Tests the std::map::contains function with an existing.
test(container_dynamic_map, contains)
{
    // Create and populate a map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Verify contains returns true for a contained key.
    assertTrue(map.contains(3));
}
/// \brief Tests the std::map::contains function with a missing key.
test(container_dynamic_map, contains_missing)
{
    // Create and populate a map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Verify contains returns false for a missing key.
    assertFalse(map.contains(0xFF));
}

// MODIFIERS
/// \brief Tests the std::map::insert function with a new key.
test(container_dynamic_map, insert_new)
{
    // Create an empty map.
    std::map<uint8_t,uint8_t> map(5);

    // Fill map to capacity.
    for(std::size_t i = 0; i < map.capacity(); ++i)
    {
        // Insert and capture result.
        auto result = map.insert(i,i);

        // Verify result.
        assertEqual(result.first, map.begin() + i);
        assertTrue(result.second);
    }
}
/// \brief Tests the std::map::insert function with an existing key.
test(container_dynamic_map, insert_existing)
{
    // Create and fill map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Insert through capacity.
    for(std::size_t i = 0; i < map.capacity(); ++i)
    {
        // Insert and capture result.
        auto result = map.insert(i,i);

        // Verify result.
        assertEqual(result.first, map.begin() + i);
        assertFalse(result.second);
    }
}
/// \brief Tests the std::map::insert function when at capacity.
test(container_dynamic_map, insert_at_capacity)
{
    // Create and fill map.
    std::map<uint8_t,uint8_t> map(5);
    fill_map(map, map.capacity());

    // Try to insert a new mapping.
    auto result = map.insert(0xFF,0xFF);

    // Verify result.
    assertEqual(result.first, map.end());
    assertFalse(result.second);
}

}

#endif