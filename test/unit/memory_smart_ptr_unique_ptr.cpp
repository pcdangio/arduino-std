// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_MEMORY_SMART_PTR_UNIQUE_PTR

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::memory::smart_ptr::unique_ptr {

// TESTS: CONSTRUCTORS
/// \brief Tests the std::unique_ptr default constructor.
test(memory_smart_ptr_unique_ptr, constructor_default)
{
    // Default construct a unique_ptr.
    std::unique_ptr<uint8_t> unique_ptr;

    // Verify unique_ptr is empty.
    assertEqual(unique_ptr.get(), nullptr);
}
/// \brief Tests the std::unique_ptr move constructor with the same object type.
test(memory_smart_ptr_unique_ptr, constructor_move)
{
    // Specify a raw pointer that will be managed.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a new unique_ptr over the raw pointer.
    std::unique_ptr<uint8_t> unique_ptr_a(raw_pointer);

    // Move construct a second unique_ptr.
    std::unique_ptr<uint8_t> unique_ptr_b(std::move(unique_ptr_a));

    // Verify unique_ptr_a is now empty.
    assertEqual(unique_ptr_a.get(), nullptr);

    // Verify unique_ptr_b now contains the raw pointer.
    assertEqual(unique_ptr_b.get(), raw_pointer);
}
/// \brief Tests the std::unique_ptr move constructor with a different object type.
test(memory_smart_ptr_unique_ptr, constructor_move_implicit)
{
    // Specify a raw pointer that will be managed.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a new unique_ptr over the raw pointer.
    std::unique_ptr<uint8_t> unique_ptr_a(raw_pointer);

    // Move construct a second const unique_ptr.
    std::unique_ptr<const uint8_t> unique_ptr_b(std::move(unique_ptr_a));

    // Verify unique_ptr_a is now empty.
    assertEqual(unique_ptr_a.get(), nullptr);

    // Verify unique_ptr_b now contains the raw pointer.
    assertEqual(unique_ptr_b.get(), raw_pointer);
}

// TESTS: MODIFIERS
/// \brief Tests the std::unique_ptr::reset function
test(memory_smart_ptr_unique_ptr, reset)
{
    // Create a unique_ptr over a raw_pointer.
    std::unique_ptr<uint8_t> unique_ptr(new uint8_t(0x12));

    // Create a new raw_pointer.
    uint8_t* const raw_pointer = new uint8_t(0x34);

    // Reset the unique_ptr to the new raw pointer.
    unique_ptr.reset(raw_pointer);

    // Verify unique_ptr is owns new raw pointer.
    assertEqual(unique_ptr.get(), raw_pointer);
}
/// \brief Tests the std::unique_ptr::release function
test(memory_smart_ptr_unique_ptr, release)
{
    // Create raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Create a unique_ptr over raw_pointer.
    std::unique_ptr<uint8_t> unique_ptr(raw_pointer);

    // Release the unique_ptr.
    uint8_t* const released_pointer = unique_ptr.release();

    // Verify released pointer is correct.
    assertEqual(released_pointer, raw_pointer);

    // Verify unique_ptr is now empty.
    assertEqual(unique_ptr.get(), nullptr);
}
/// \brief Tests the std::unique_ptr::swap function.
test(memory_smart_ptr_unique_ptr, swap)
{
    // Create smart_ptr_a over raw_pointer_a.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    std::unique_ptr<uint8_t> unique_ptr_a(raw_pointer_a);

    // Create smart_ptr_b over raw_pointer_b.
    uint8_t* const raw_pointer_b = new uint8_t(0x12);
    std::unique_ptr<uint8_t> unique_ptr_b(raw_pointer_b);

    // Swap the two smart_ptrs.
    unique_ptr_a.swap(unique_ptr_b);

    // Verify unique_ptr_a now manages raw_pointer_b.
    assertEqual(unique_ptr_a.get(), raw_pointer_b);

    // Verify unique_ptr_b now manages raw_pointer_a.
    assertEqual(unique_ptr_b.get(), raw_pointer_a);
}
/// \brief Tests the std::unique_ptr::operator= move function with different instances.
test(memory_smart_ptr_unique_ptr, operator_assign)
{
    // Create raw pointers.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    uint8_t* const raw_pointer_b = new uint8_t(0x34);

    // Create unique_ptr_a over raw_pointer_a.
    std::unique_ptr<uint8_t> unique_ptr_a(raw_pointer_a);

    // Create unique_ptr_b over raw_pointer_b.
    std::unique_ptr<uint8_t> unique_ptr_b(raw_pointer_b);

    // Assign unique_ptr_a to unique_ptr_b.
    unique_ptr_b = std::move(unique_ptr_a);

    // Verify unique_ptr_b now manages raw_pointer_a.
    assertEqual(unique_ptr_b.get(), raw_pointer_a);

    // Verify unique_ptr_a is now empty.
    assertEqual(unique_ptr_a.get(), nullptr);
}
/// \brief Tests the std::unique_ptr::operator= other copy function with different instances.
test(memory_smart_ptr_unique_ptr, operator_assign_implicit)
{
    // Create raw pointers.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    uint8_t* const raw_pointer_b = new uint8_t(0x34);

    // Create unique_ptr_a over raw_pointer_a.
    std::unique_ptr<uint8_t> unique_ptr_a(raw_pointer_a);

    // Create unique_ptr_b over raw_pointer_b.
    std::unique_ptr<const uint8_t> unique_ptr_b(raw_pointer_b);

    // Assign unique_ptr_a to unique_ptr_b.
    unique_ptr_b = std::move(unique_ptr_a);

    // Verify unique_ptr_b now manages raw_pointer_a.
    assertEqual(unique_ptr_b.get(), raw_pointer_a);

    // Verify unique_ptr_a is now empty.
    assertEqual(unique_ptr_a.get(), nullptr);
}

// TESTS: MAKE_UNIQUE
/// \brief Tests the std::make_unique function.
test(memory_smart_ptr_unique_ptr, make_unique)
{
    // Create an expected value.
    const uint8_t value = 0x12;

    // Create a unique_ptr using make_shared with value.
    std::unique_ptr<uint8_t> unique_ptr = std::make_unique<uint8_t>(value);

    // Verify a valid unique_ptr was created.
    assertNotEqual(unique_ptr.get(), nullptr);

    // Verify constructor value was passed.
    assertEqual(*unique_ptr, value);
}

}

#endif