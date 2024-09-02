// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_MEMORY_SMART_PTR

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::memory::smart_ptr {

// UTILITY
/// \brief A derived smart_ptr for testing protected members.
class derived
    : public std::memory::smart_ptr<uint8_t>
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new derived smart_ptr instance.
    /// \param[in] instance The raw pointer to assign to the smart_ptr.
    derived(uint8_t* instance)
        : std::memory::smart_ptr<uint8_t>(instance)
    {}

    // COMPARISON
    using std::memory::smart_ptr<uint8_t>::operator==;
    using std::memory::smart_ptr<uint8_t>::operator!=;
};
/// \brief A test struct for dereference checking.
struct test_struct
{
    // CONSTRUCTORS
    /// \brief Constructs a new test_struct instance.
    /// \param[in] value The value to set.
    test_struct(uint8_t value)
        : value(value)
    {}

    // FIELDS
    /// \brief A test value.
    uint8_t value;
};

// TESTS: CONSTRUCTORS
/// \brief Tests the std::memory::smart_ptr default constructor.
test(memory_smart_ptr, constructor_default)
{
    /// Default-construct a smart_ptr.
    std::memory::smart_ptr<uint8_t> smart_ptr;

    // Verify instance is nullptr.
    assertFalse(smart_ptr);
}
/// \brief Tests the std::memory::smart_ptr constructor with a raw pointer.
test(memory_smart_ptr, constructor_raw_pointer)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a smart_ptr from a raw pointer.
    std::memory::smart_ptr<uint8_t> smart_ptr(raw_pointer);

    // Verify the raw pointer was stored.
    assertEqual(smart_ptr.get(), raw_pointer);

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr copy constructor.
test(memory_smart_ptr, constructor_copy)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a smart_ptr from a raw pointer.
    std::memory::smart_ptr<uint8_t> smart_ptr_a(raw_pointer);

    // Copy-construct a new smart_ptr.
    std::memory::smart_ptr<uint8_t> smart_ptr_b(smart_ptr_a);

    // Verify the two smart_ptrs are equal.
    assertEqual(smart_ptr_b.get(), smart_ptr_a.get());

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr move constructor.
test(memory_smart_ptr, constructor_move)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a smart_ptr from a raw pointer.
    std::memory::smart_ptr<uint8_t> smart_ptr_a(raw_pointer);

    // Move-construct a new smart_ptr.
    std::memory::smart_ptr<uint8_t> smart_ptr_b(std::move(smart_ptr_a));

    // Verify smart_ptr_b now contains the raw_pointer.
    assertEqual(smart_ptr_b.get(), raw_pointer);

    // Verify smart_ptr_a is now empty.
    assertFalse(smart_ptr_a);

    // Clean up raw pointer.
    delete raw_pointer;
}

// TESTS: OBSERVERS
/// \brief Tests the std::memory::smart_ptr::get function.
test(memory_smart_ptr, get)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a smart_ptr from a raw pointer.
    std::memory::smart_ptr<uint8_t> smart_ptr(raw_pointer);

    // Verify get() returns the raw_pointer.
    assertEqual(smart_ptr.get(), raw_pointer);

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr::operator* function.
test(memory_smart_ptr, operator_dereference)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a smart_ptr from a raw pointer.
    std::memory::smart_ptr<uint8_t> smart_ptr(raw_pointer);

    // Verify operator*() returns the raw pointer.
    assertEqual(*smart_ptr, raw_pointer);

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr::operator-> function.
test(memory_smart_ptr, operator_arrow)
{
    // Create a raw pointer.
    test_struct* const raw_pointer = new test_struct(0x12);

    // Construct a smart_ptr from a raw pointer.
    std::memory::smart_ptr<test_struct> smart_ptr(new test_struct(0x12));

    // Verify operator->() permits access to the struct's value.
    assertEqual(smart_ptr->value, uint8_t(0x12));

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr::operator bool function with a valid pointer.
test(memory_smart_ptr, operator_bool_valid)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct a smart_ptr from a raw pointer.
    std::memory::smart_ptr<uint8_t> smart_ptr(raw_pointer);

    // Verify operator bool returns true.
    assertTrue(smart_ptr);

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr::operator bool function with an invalid pointer.
test(memory_smart_ptr, operator_bool_invalid)
{
    // Construct a nullptr smart_ptr.
    std::memory::smart_ptr<uint8_t> smart_ptr;

    // Verify operator bool returns false.
    assertFalse(smart_ptr);
}

// TESTS: COMPARISON
/// \brief Tests the std::memory::smart_ptr::operator== function with equal smart_ptrs.
test(memory_smart_ptr, operator_equal_equal)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct two smart_ptrs from the raw pointer.
    derived smart_ptr_a(raw_pointer), smart_ptr_b(raw_pointer);

    // Verify operator== returns true.
    assertTrue(smart_ptr_a == smart_ptr_b);

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr::operator== function with unequal smart_ptrs.
test(memory_smart_ptr, operator_equal_unequal)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct two smart_ptrs from the raw pointer.
    derived smart_ptr_a(raw_pointer), smart_ptr_b(nullptr);

    // Verify operator== returns false.
    assertFalse(smart_ptr_a == smart_ptr_b);

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr::operator!= function with equal smart_ptrs.
test(memory_smart_ptr, operator_not_equal_equal)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct two smart_ptrs from the raw pointer.
    derived smart_ptr_a(raw_pointer), smart_ptr_b(raw_pointer);

    // Verify operator!= returns false.
    assertFalse(smart_ptr_a != smart_ptr_b);

    // Clean up raw pointer.
    delete raw_pointer;
}
/// \brief Tests the std::memory::smart_ptr::operator!= function with unequal smart_ptrs.
test(memory_smart_ptr, operator_not_equal_unequal)
{
    // Create a raw pointer.
    uint8_t* const raw_pointer = new uint8_t(0x12);

    // Construct two smart_ptrs from the raw pointer.
    derived smart_ptr_a(raw_pointer), smart_ptr_b(nullptr);

    // Verify operator!= returns true.
    assertTrue(smart_ptr_a != smart_ptr_b);

    // Clean up raw pointer.
    delete raw_pointer;
}

}

#endif