// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_UTILITY_PAIR

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::utility::pair {

// UTILITY
/// \brief An object that monitors how it was constructed.
struct monitor
{
    // CONSTRUCTORS
    /// \brief Default-constructs a new monitor instance.
    monitor()
        : default_constructed(true),
          copy_constructed(false),
          move_constructed(false)
    {}
    /// \brief Copy-constructs a new monitor instance.
    /// \param[in] other The other monitor to copy-construct from.
    monitor(const monitor& other)
        : default_constructed(false),
          copy_constructed(true),
          move_constructed(false)
    {}
    /// \brief Move-constructs a new monitor instance.
    /// \param[in] other The other monitor to move-construct from.
    monitor(monitor&& other)
        : default_constructed(false),
          copy_constructed(false),
          move_constructed(true)
    {}

    // TRACKERS
    /// \brief Tracks if this monitor was default-constructed.
    const bool default_constructed;
    /// \brief Tracks if this monitor was copy-construted.
    const bool copy_constructed;
    /// \brief Tracks if this monitor was move-constructed.
    const bool move_constructed;
};

// TESTS: CONSTRUCTOR
/// \brief Tests the std::pair default constructor.
test(utility_pair, constructor_default)
{
    // Default construct a pair.
    std::pair<monitor,monitor> pair;

    // Verify both elements were default construted.
    assertTrue(pair.first.default_constructed);
    assertTrue(pair.second.default_constructed);
}
/// \brief Tests the std::pair value copy constructor.
test(utility_pair, constructor_value_copy)
{
    // Create a monitor to copy-construct from.
    monitor monitor_copy;

    // Construct a pair with values.
    std::pair<monitor,monitor> pair(monitor_copy, monitor_copy);

    // Verify both elements were copy-construted.
    assertTrue(pair.first.copy_constructed);
    assertTrue(pair.second.copy_constructed);
}
/// \brief Tests the std::pair value move constructor.
test(utility_pair, constructor_value_move)
{
    // Create a monitor to copy-construct from.
    monitor monitor_move;

    // Construct a pair with move semantics.
    std::pair<monitor,monitor> pair(std::move<monitor>(monitor_move), std::move<monitor>(monitor_move));

    // Verify both elements were move-construted.
    assertTrue(pair.first.move_constructed);
    assertTrue(pair.second.move_constructed);
}
/// \brief Tests the std::pair copy constructor.
test(utility_pair, constructor_copy)
{
    // Create a pair to copy from.
    std::pair<monitor,monitor> pair_copy;

    // Copy-construct a pair.
    std::pair<monitor,monitor> pair(pair_copy);

    // Verify both elements were copy-construted.
    assertTrue(pair.first.copy_constructed);
    assertTrue(pair.second.copy_constructed);
}
/// \brief Tests the std::pair move constructor.
test(utility_pair, constructor_move)
{
    // Create a pair to copy from.
    std::pair<monitor,monitor> pair_move;

    // Move-construct a pair.
    std::pair<monitor,monitor> pair(std::move<std::pair<monitor,monitor>>(pair_move));

    // Verify both elements were move-construted.
    assertTrue(pair.first.move_constructed);
    assertTrue(pair.second.move_constructed);
}

// TESTS: MODIFIERS
/// \brief Tests the std::pair::operator= function.
test(utility_pair, operator_assignment)
{
    // Create a populated pair.
    std::pair<uint8_t,uint8_t> pair_a(0x12,0x34);

    // Create a default pair.
    std::pair<uint8_t,uint8_t> pair_b;

    // Assign pair_a to pair_b.
    pair_b = pair_a;

    // Verify pairs are now equal.
    assertTrue(pair_b == pair_a);
}
/// \brief Tests the std::pair::swap function.
test(utility_pair, swap)
{
    // Create two populated pairs.
    std::pair<uint8_t,uint8_t> pair_a(0x12,0x34);
    std::pair<uint8_t,uint8_t> pair_b(0x56,0x78);

    // Swap the two pairs.
    pair_a.swap(pair_b);

    // Verify swap.
    assertEqual(pair_a.first, 0x56);
    assertEqual(pair_a.second, 0x78);
    assertEqual(pair_b.first, 0x12);
    assertEqual(pair_b.second, 0x34);
}

// COMPARISON
/// \brief Tests the std::pair::operator== function with equal pairs.
test(utility_pair, operator_equal_equal)
{
    // Create two equal pairs.
    std::pair<uint8_t,uint8_t> pair_a(0x12,0x34);
    std::pair<uint8_t,uint8_t> pair_b(0x12,0x34);

    // Verify the two pairs return as equal.
    assertTrue(pair_a == pair_b);
}
/// \brief Tests the std::pair::operator== function with unequal pairs.
test(utility_pair, operator_equal_unequal)
{
    // Create two unequal pairs.
    std::pair<uint8_t,uint8_t> pair_a(0x12,0x34);
    std::pair<uint8_t,uint8_t> pair_b(0x34,0x56);

    // Verify the two pairs return as not equal.
    assertFalse(pair_a == pair_b);
}
/// \brief Tests the std::pair::operator!= function with unequal pairs.
test(utility_pair, operator_unequal_unequal)
{
    // Create two unequal pairs.
    std::pair<uint8_t,uint8_t> pair_a(0x12,0x34);
    std::pair<uint8_t,uint8_t> pair_b(0x34,0x56);

    // Verify the two pairs are unequal.
    assertTrue(pair_a != pair_b);
}
/// \brief Tests the std::pair::operator!= function with equal pairs.
test(utility_pair, operator_unequal_equal)
{
    // Create two equal pairs.
    std::pair<uint8_t,uint8_t> pair_a(0x12,0x34);
    std::pair<uint8_t,uint8_t> pair_b(0x12,0x34);

    // Verify the two pairs are equal.
    assertFalse(pair_a != pair_b);
}

}

#endif