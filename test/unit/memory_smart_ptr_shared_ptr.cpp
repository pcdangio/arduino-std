// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_MEMORY_SMART_PTR_SHARED_PTR

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::memory::smart_ptr::shared_ptr {

// TESTS: CONSTRUCTORS
/// \brief Tests the std::shared_ptr default constructor.
test(memory_smart_ptr_shared_ptr, constructor_default)
{
    // Default construct a shared_ptr.
    std::shared_ptr<uint8_t> shared_ptr;

    // Verify shared_ptr is empty.
    assertEqual(shared_ptr.get(), nullptr);

    // Verify reference count is zero.
    assertEqual(shared_ptr.use_count(), std::size_t(0));
}
/// \brief Tests the std::shared_ptr copy constructor with the same object type.
test(memory_smart_ptr_shared_ptr, constructor_copy_same)
{
    // Specify a raw pointer that will be managed.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a new shared_ptr over the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);

    // Copy construct a second shared_ptr.
    std::shared_ptr<uint8_t> shared_ptr_b(shared_ptr_a);

    // Verify both shared_ptrs manage the same raw pointer.
    assertEqual(shared_ptr_a.get(), raw_pointer);
    assertEqual(shared_ptr_b.get(), raw_pointer);

    // Verify use count is 2.
    assertEqual(shared_ptr_a.use_count(), std::size_t(2));
    assertEqual(shared_ptr_b.use_count(), std::size_t(2));
}
/// \brief Tests the std::shared_ptr copy constructor with different object types.
test(memory_smart_ptr_shared_ptr, constructor_copy_different)
{
    // Specify a raw pointer that will be managed.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a new shared_ptr over the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);

    // Copy construct a second const shared_ptr.
    std::shared_ptr<const uint8_t> shared_ptr_b(shared_ptr_a);

    // Verify both shared_ptrs manage the same raw pointer.
    assertEqual(shared_ptr_a.get(), raw_pointer);
    assertEqual(shared_ptr_b.get(), raw_pointer);

    // Verify use count is 2.
    assertEqual(shared_ptr_a.use_count(), std::size_t(2));
    assertEqual(shared_ptr_b.use_count(), std::size_t(2));
}
/// \brief Tests the std::shared_ptr move constructor with the same object type.
test(memory_smart_ptr_shared_ptr, constructor_move_same)
{
    // Specify a raw pointer that will be managed.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a new shared_ptr over the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);

    // Move construct a second shared_ptr.
    std::shared_ptr<uint8_t> shared_ptr_b(std::move(shared_ptr_a));

    // Verify shared_ptr_a is now empty.
    assertEqual(shared_ptr_a.get(), nullptr);
    assertEqual(shared_ptr_a.use_count(), std::size_t(0));

    // Verify shared_ptr_b now contains the raw pointer.
    assertEqual(shared_ptr_b.get(), raw_pointer);
    assertEqual(shared_ptr_b.use_count(), std::size_t(1));
}
/// \brief Tests the std::shared_ptr move constructor with a different object type.
test(memory_smart_ptr_shared_ptr, constructor_move_different)
{
    // Specify a raw pointer that will be managed.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a new shared_ptr over the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);

    // Move construct a second const shared_ptr.
    std::shared_ptr<const uint8_t> shared_ptr_b(std::move(shared_ptr_a));

    // Verify shared_ptr_a is now empty.
    assertEqual(shared_ptr_a.get(), nullptr);
    assertEqual(shared_ptr_a.use_count(), std::size_t(0));

    // Verify shared_ptr_b now contains the raw pointer.
    assertEqual(shared_ptr_b.get(), raw_pointer);
    assertEqual(shared_ptr_b.use_count(), std::size_t(1));
}

// TESTS: MODIFIERS
/// \brief Tests the std::shared_ptr::reset function with a nullptr.
test(memory_smart_ptr_shared_ptr, reset_nullptr)
{
    // Create a shared_ptr over a raw_pointer.
    std::shared_ptr<uint8_t> shared_ptr(new uint8_t(0x12));

    // Reset the shared_ptr to null.
    shared_ptr.reset();

    // Verify shared_ptr is empty.
    assertEqual(shared_ptr.get(), nullptr);
    assertEqual(shared_ptr.use_count(), std::size_t(0));
}
/// \brief Tests the std::shared_ptr::reset function with a new pointer.
test(memory_smart_ptr_shared_ptr, reset_instance)
{
    // Create a shared_ptr over a raw_pointer.
    std::shared_ptr<uint8_t> shared_ptr(new uint8_t(0x12));

    // Create a new raw_pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Reset the shared_ptr to the new raw pointer.
    shared_ptr.reset(raw_pointer);

    // Verify shared_ptr is owns new raw pointer.
    assertEqual(shared_ptr.get(), raw_pointer);
    assertEqual(shared_ptr.use_count(), std::size_t(1));
}
/// \brief Tests the std::shared_ptr::swap function.
test(memory_smart_ptr_shared_ptr, swap)
{
    // Create smart_ptr_a over raw_pointer_a.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer_a);

    // Create smart_ptr_b over raw_pointer_b.
    uint8_t* const raw_pointer_b = new uint8_t(0x12);
    std::shared_ptr<uint8_t> shared_ptr_b(raw_pointer_b);

    // Create smart_ptr_c over raw_pointer_c to increase use count.
    std::shared_ptr<uint8_t> shared_ptr_c(shared_ptr_b);

    // Swap the two smart_ptrs.
    shared_ptr_a.swap(shared_ptr_b);

    // Verify shared_ptr_a now manages raw_pointer_b.
    assertEqual(shared_ptr_a.get(), raw_pointer_b);
    assertEqual(shared_ptr_a.use_count(), std::size_t(2));

    // Verify shared_ptr_b now manages raw_pointer_a.
    assertEqual(shared_ptr_b.get(), raw_pointer_a);
    assertEqual(shared_ptr_b.use_count(), std::size_t(1));
}
/// \brief Tests the std::shared_ptr::operator= copy function with different instances.
test(memory_smart_ptr_shared_ptr, operator_assign_copy_different)
{
    // Create raw pointers.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    uint8_t* const raw_pointer_b = new uint8_t(0x34);

    // Create shared_ptr_a over raw_pointer_a.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer_a);

    // Create shared_ptr_b1,2 over raw_pointer_b.
    std::shared_ptr<uint8_t> shared_ptr_b1(raw_pointer_b);
    std::shared_ptr<uint8_t> shared_ptr_b2(shared_ptr_b1);

    // Assign shared_ptr_a to shared_ptr_b1.
    shared_ptr_b1 = shared_ptr_a;

    // Verify shared_ptr_b1 now manages raw_pointer_a.
    assertEqual(shared_ptr_b1.get(), raw_pointer_a);
    assertEqual(shared_ptr_b1.use_count(), std::size_t(2));

    // Verify shared_ptr_b2 use_count is equal to 1.
    assertEqual(shared_ptr_b2.use_count(), std::size_t(1));
}
/// \brief Tests the std::shared_ptr::operator= copy function with same instances.
test(memory_smart_ptr_shared_ptr, operator_assign_copy_same)
{
    // Create raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Create two shared_ptrs that manage the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);
    std::shared_ptr<uint8_t> shared_ptr_b(shared_ptr_a);

    // Assign shared_ptr_a to shared_ptr_b1.
    shared_ptr_b = shared_ptr_a;

    // Verify shared_ptr_b still manages raw_pointer.
    assertEqual(shared_ptr_b.get(), raw_pointer);
    assertEqual(shared_ptr_b.use_count(), std::size_t(2));
}
/// \brief Tests the std::shared_ptr::operator= other copy function with different instances.
test(memory_smart_ptr_shared_ptr, operator_assign_copy_other_different)
{
    // Create raw pointers.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    uint8_t* const raw_pointer_b = new uint8_t(0x34);

    // Create shared_ptr_a over raw_pointer_a.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer_a);

    // Create const shared_ptr_b1,2 over raw_pointer_b.
    std::shared_ptr<const uint8_t> shared_ptr_b1(raw_pointer_b);
    std::shared_ptr<const uint8_t> shared_ptr_b2(shared_ptr_b1);

    // Assign shared_ptr_a to shared_ptr_b1.
    shared_ptr_b1 = shared_ptr_a;

    // Verify shared_ptr_b1 now manages raw_pointer_a.
    assertEqual(shared_ptr_b1.get(), raw_pointer_a);
    assertEqual(shared_ptr_b1.use_count(), std::size_t(2));

    // Verify shared_ptr_b2 use_count is equal to 1.
    assertEqual(shared_ptr_b2.use_count(), std::size_t(1));
}
/// \brief Tests the std::shared_ptr::operator= other copy function with same instances.
test(memory_smart_ptr_shared_ptr, operator_assign_copy_other_same)
{
    // Create raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Create two shared_ptrs that manage the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);
    std::shared_ptr<const uint8_t> shared_ptr_b(shared_ptr_a);

    // Assign shared_ptr_a to shared_ptr_b1.
    shared_ptr_b = shared_ptr_a;

    // Verify shared_ptr_b still manages raw_pointer.
    assertEqual(shared_ptr_b.get(), raw_pointer);
    assertEqual(shared_ptr_b.use_count(), std::size_t(2));
}
/// \brief Tests the std::shared_ptr::operator= move function with different instances.
test(memory_smart_ptr_shared_ptr, operator_assign_move_different)
{
    // Create raw pointers.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    uint8_t* const raw_pointer_b = new uint8_t(0x34);

    // Create shared_ptr_a over raw_pointer_a.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer_a);

    // Create shared_ptr_b1,2 over raw_pointer_b.
    std::shared_ptr<uint8_t> shared_ptr_b1(raw_pointer_b);
    std::shared_ptr<uint8_t> shared_ptr_b2(shared_ptr_b1);

    // Assign shared_ptr_a to shared_ptr_b1.
    shared_ptr_b1 = std::move(shared_ptr_a);

    // Verify shared_ptr_b1 now manages raw_pointer_a.
    assertEqual(shared_ptr_b1.get(), raw_pointer_a);
    assertEqual(shared_ptr_b1.use_count(), std::size_t(1));

    // Verify shared_ptr_a is now empty.
    assertEqual(shared_ptr_a.get(), nullptr);
    assertEqual(shared_ptr_a.use_count(), std::size_t(0));

    // Verify shared_ptr_b2 use_count is equal to 1.
    assertEqual(shared_ptr_b2.use_count(), std::size_t(1));
}
/// \brief Tests the std::shared_ptr::operator= move function with same instances.
test(memory_smart_ptr_shared_ptr, operator_assign_move_same)
{
    // Create raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Create two shared_ptrs that manage the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);
    std::shared_ptr<uint8_t> shared_ptr_b(shared_ptr_a);

    // Assign shared_ptr_a to shared_ptr_b.
    shared_ptr_b = std::move(shared_ptr_a);

    // Verify shared_ptr_b still manages raw_pointer.
    assertEqual(shared_ptr_b.get(), raw_pointer);
    assertEqual(shared_ptr_b.use_count(), std::size_t(1));

    // Verify shared_ptr_a is now empty.
    assertEqual(shared_ptr_a.get(), nullptr);
    assertEqual(shared_ptr_a.use_count(), std::size_t(0));
}
/// \brief Tests the std::shared_ptr::operator= other copy function with different instances.
test(memory_smart_ptr_shared_ptr, operator_assign_move_other_different)
{
    // Create raw pointers.
    uint8_t* const raw_pointer_a = new uint8_t(0x12);
    uint8_t* const raw_pointer_b = new uint8_t(0x34);

    // Create shared_ptr_a over raw_pointer_a.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer_a);

    // Create const shared_ptr_b1,2 over raw_pointer_b.
    std::shared_ptr<const uint8_t> shared_ptr_b1(raw_pointer_b);
    std::shared_ptr<const uint8_t> shared_ptr_b2(shared_ptr_b1);

    // Assign shared_ptr_a to shared_ptr_b1.
    shared_ptr_b1 = std::move(shared_ptr_a);

    // Verify shared_ptr_b1 now manages raw_pointer_a.
    assertEqual(shared_ptr_b1.get(), raw_pointer_a);
    assertEqual(shared_ptr_b1.use_count(), std::size_t(1));

    // Verify shared_ptr_a is now empty.
    assertEqual(shared_ptr_a.get(), nullptr);
    assertEqual(shared_ptr_a.use_count(), std::size_t(0));

    // Verify shared_ptr_b2 use_count is equal to 1.
    assertEqual(shared_ptr_b2.use_count(), std::size_t(1));
}
/// \brief Tests the std::shared_ptr::operator= other copy function with same instances.
test(memory_smart_ptr_shared_ptr, operator_assign_move_other_same)
{
    // Create raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Create two shared_ptrs that manage the raw pointer.
    std::shared_ptr<uint8_t> shared_ptr_a(raw_pointer);
    std::shared_ptr<const uint8_t> shared_ptr_b(shared_ptr_a);

    // Assign shared_ptr_a to shared_ptr_b.
    shared_ptr_b = std::move(shared_ptr_a);

    // Verify shared_ptr_b still manages raw_pointer.
    assertEqual(shared_ptr_b.get(), raw_pointer);
    assertEqual(shared_ptr_b.use_count(), std::size_t(1));

    // Verify shared_ptr_a is now empty.
    assertEqual(shared_ptr_a.get(), nullptr);
    assertEqual(shared_ptr_a.use_count(), std::size_t(0));
}

// TESTS: OBSERVERS
/// \brief Tests the std::shared_ptr::use_count function.
test(memory_smart_ptr_shared_ptr, use_count)
{
    // Create a shared_ptr.
    std::shared_ptr<uint8_t> shared_ptr(new uint8_t(0x12));

    // Verify use_count is one.
    assertEqual(shared_ptr.use_count(), std::size_t(1));

    // Reset the shared_ptr.
    shared_ptr.reset();

    // Verify use_count is zero.
    assertEqual(shared_ptr.use_count(), std::size_t(0));
}

// TESTS: MAKE_PAIR
/// \brief Tests the std::make_shared function.
test(memory_smart_ptr_shared_ptr, make_shared)
{
    // Create an expected value.
    const uint8_t value = 0x12;

    // Create a shared_ptr using make_shared with value.
    std::shared_ptr<uint8_t> shared_ptr = std::make_shared<uint8_t>(value);

    // Verify a valid shared_ptr was created.
    assertNotEqual(shared_ptr.get(), nullptr);
    assertEqual(shared_ptr.use_count(), std::size_t(1));

    // Verify constructor value was passed.
    assertEqual(*shared_ptr, value);
}

}

#endif