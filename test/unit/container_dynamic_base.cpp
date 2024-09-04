// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_CONTAINER_DYNAMIC_BASE

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::container::dynamic::base {

// UTILITY
/// \brief A derived version of the base dynamic container for testing purposes.
struct derived
    : public std::container::dynamic::base<uint8_t>
{
    // CONSTRUCTORS
    /// \brief Default constructs a new derived dynamic container instance.
    /// \param[in] capacity The capacity of the container.
    derived(std::size_t capacity)
        : std::container::dynamic::base<uint8_t>(capacity)
    {}
    /// \brief Copy-constructs a new derived dynamic container instance from an existing one.
    /// \param[in] other The other container to copy from.
    derived(const derived& other)
        : std::container::dynamic::base<uint8_t>(other)
    {}
    /// \brief Move-constructs a new derived dynamic container instance from an existing one.
    /// \param[in] other The other container to move from.
    derived(derived&& other)
        : std::container::dynamic::base<uint8_t>(other)
    {}

    // MODIFIERS
    /// \brief Fills the container with unique incremental values, starting at zero.
    /// \param[in] size The number of elements to fill the container with.
    void fill(std::size_t size)
    {
        // Update end size, clamping if necessary.
        derived::m_end = derived::m_begin + size;
        if(derived::m_end > derived::m_capacity)
        {
            derived::m_end = derived::m_capacity;
        }

        // Set elements.
        uint8_t i = 0;
        for(auto entry = derived::m_begin; entry != derived::m_end; ++entry)
        {
            *entry = i++;
        }
    }
    /// \brief Fills the container with a specified value.
    /// \param[in] value The value to fill the container with.
    /// \param[in] size The number of values to fill.
    void fill(uint8_t value, std::size_t size)
    {
        // Update end size, clamping if necessary.
        derived::m_end = derived::m_begin + size;
        if(derived::m_end > derived::m_capacity)
        {
            derived::m_end = derived::m_capacity;
        }

        // Set elements.
        for(auto entry = derived::m_begin; entry != derived::m_end; ++entry)
        {
            *entry = value;
        }
    }
    /// \brief Exposes the underlying base::operator= function.
    /// \param[in] other The other derived instance to assign from.
    /// \return TRUE if the assignment succeeded, otherwise FALSE.
    bool operator=(const derived& other)
    {
        return std::container::dynamic::base<uint8_t>::operator=(other);
    }
    /// \brief Exposes the underlying base::swap function.
    /// \param[in] other The other derived instance to swap with.
    void swap(derived& other)
    {
        std::container::dynamic::base<uint8_t>::swap(other);
    }

    // COMPARISON
    using std::container::dynamic::base<uint8_t>::operator==;
    using std::container::dynamic::base<uint8_t>::operator!=;

    // SHIFT
    using std::container::dynamic::base<uint8_t>::shift_left;
    using std::container::dynamic::base<uint8_t>::shift_right;
};

// TESTS: CONSTRUCTORS
/// \brief Tests the std::container::dynamic::base default constructor.
test(container_dynamic_base, constructor_default)
{
    // Specify capacity.
    const std::size_t capacity = 5;

    // Create container.
    std::container::dynamic::base<uint8_t> container(capacity);

    // Verify container is empty.
    assertTrue(container.empty());

    // Verify container capacity.
    assertEqual(container.capacity(), capacity);

    // Verify valid begin iterator.
    assertNotEqual(container.begin(), nullptr);
}
/// \brief Tests the std::container::dynamic::base copy constructor.
test(container_dynamic_base, constructor_copy)
{
    // Create and populate container_a.
    derived container_a(5);
    container_a.fill(3);

    // Copy construct container_b from container_a.
    std::container::dynamic::base<uint8_t> container_b(container_a);

    // Verify container capacities and sizes match.
    assertEqual(container_b.size(), container_a.size());
    assertEqual(container_b.capacity(), container_a.capacity());

    // Verify data matches.
    auto a_entry = container_a.begin();
    auto b_entry = container_b.begin();
    for(;b_entry < container_b.end(); ++a_entry,++b_entry)
    {
        assertEqual(*b_entry, *a_entry);
    }
}
/// \brief Tests the std::container::dynamic::base move constructor.
test(container_dynamic_base, constructor_move)
{
    // Specify capacity and size.
    const std::size_t capacity = 5;
    const std::size_t size = 3;

    // Create and populate container_a.
    derived container_a(capacity);
    container_a.fill(size);

    // Move construct container_b from container_a.
    std::container::dynamic::base<uint8_t> container_b(std::move(container_a));

    // Verify container_a capacity and size.
    assertEqual(container_a.capacity(), capacity);
    assertTrue(container_a.empty());

    // Verify container_b capacity and size.
    assertEqual(container_b.capacity(), capacity);
    assertEqual(container_b.size(), size);

    // Verify container_b contents.
    uint8_t i = 0;
    for(auto entry = container_b.cbegin(); entry != container_b.cend(); ++entry)
    {
        assertEqual(*entry, i++);
    }
}

// TESTS: ACCESS
/// \brief Tests the std::container::dynamic::base::begin function.
test(container_dynamic_base, begin)
{
    // Create container.
    std::container::dynamic::base<uint8_t> container(5);

    // Verify begin points to a valid memory location.
    assertNotEqual(container.begin(), nullptr);
}
/// \brief Tests the std::container::dynamic::base::end function.
test(container_dynamic_base, end)
{
    // Create container.
    derived container(5);

    // Verify end iterator while empty.
    assertEqual(container.end(), container.begin());

    // Populate container.
    const std::size_t size = 2;
    container.fill(2);

    // Verify end iterator while populated.
    assertEqual(container.end(), container.begin() + size);
}
/// \brief Tests the std::container::dynamic::base::cbegin function.
test(container_dynamic_base, cbegin)
{
    // Create container.
    std::container::dynamic::base<uint8_t> container(5);

    // Verify cbegin points to a valid memory location.
    assertNotEqual(container.cbegin(), nullptr);
}
/// \brief Tests the std::container::dynamic::base::cend function.
test(container_dynamic_base, cend)
{
    // Create container.
    derived container(5);

    // Verify cend iterator while empty.
    assertEqual(container.cend(), container.cbegin());

    // Populate container.
    const std::size_t size = 2;
    container.fill(2);

    // Verify cend iterator while populated.
    assertEqual(container.cend(), container.cbegin() + size);
}

// TESTS: MODIFIERS
/// \brief Tests the std::container::dynamic::base::erase function with a single iterator.
test(container_dynamic_base, erase_value)
{
    // Specify expected value of container after erase.
    // Assumes fill() is used to generate 0,1,2,3,4
    uint8_t expected[4] = {0, 1, 3, 4};

    // Create and fill container.
    derived container(7);
    container.fill(5);

    // Erase index 2 from the container.
    auto next_iterator = container.erase(container.begin() + 2);

    // Validate size.
    assertEqual(container.size(), std::size_t(4));

    // Validate elements match with expected values.
    for(uint8_t i = 0; i < container.size(); ++i)
    {
        assertEqual(*(container.cbegin() + i), expected[i]);
    }

    // Validate next iterator.
    assertEqual(next_iterator, container.begin() + 2);
}
/// \brief Tests the std::container::dynamic::base::erase function with a single const iterator.
test(container_dynamic_base, erase_value_const)
{
    // Specify expected value of container after erase.
    // Assumes fill() is used to generate 0,1,2,3,4
    uint8_t expected[4] = {0, 1, 3, 4};

    // Create and fill container.
    derived container(7);
    container.fill(5);

    // Erase index 2 from the container.
    auto next_iterator = container.erase(container.cbegin() + 2);

    // Validate size.
    assertEqual(container.size(), std::size_t(4));

    // Validate elements match with expected values.
    for(uint8_t i = 0; i < container.size(); ++i)
    {
        assertEqual(*(container.cbegin() + i), expected[i]);
    }

    // Validate next iterator.
    assertEqual(next_iterator, container.begin() + 2);
}
/// \brief Tests the std::container::dynamic::base::erase function with an iterator range.
test(container_dynamic_base, erase_range)
{
    // Specify expected value of container after erase.
    // Assumes fill() is used to generate 0,1,2,3,4
    uint8_t expected[2] = {0, 4};

    // Create and fill container.
    derived container(7);
    container.fill(5);

    // Erase from indices 1-3 from the container.
    auto next_iterator = container.erase(container.begin() + 1, container.begin() + 3);

    // Validate size.
    assertEqual(container.size(), std::size_t(2));

    // Validate elements match with expected values.
    for(uint8_t i = 0; i < container.size(); ++i)
    {
        assertEqual(*(container.cbegin() + i), expected[i]);
    }

    // Validate next iterator.
    assertEqual(next_iterator, container.begin() + 1);
}
/// \brief Tests the std::container::dynamic::base::erase function with a const iterator range.
test(container_dynamic_base, erase_range_const)
{
    // Specify expected value of container after erase.
    // Assumes fill() is used to generate 0,1,2,3,4
    uint8_t expected[2] = {0, 4};

    // Create and fill container.
    derived container(7);
    container.fill(5);

    // Erase from indices 1-3 from the container.
    auto next_iterator = container.erase(container.cbegin() + 1, container.cbegin() + 3);

    // Validate size.
    assertEqual(container.size(), std::size_t(2));

    // Validate elements match with expected values.
    for(uint8_t i = 0; i < container.size(); ++i)
    {
        assertEqual(*(container.cbegin() + i), expected[i]);
    }

    // Validate next iterator.
    assertEqual(next_iterator, container.begin() + 1);
}
/// \brief Tests the std::container::dynamic::base::clear function.
test(container_dynamic_base, clear)
{
    // Create and populate container.
    derived container(5);
    container.fill(container.capacity());

    // Clear the container.
    container.clear();

    // Verify container is empty.
    assertTrue(container.empty());
}
/// \brief Tests the std::container::dynamic::base::operator= function with a valid configuration.
test(container_dynamic_base, operator_assignment)
{
    // Create two containers.
    derived container_a(5), container_b(5);

    // Populate container_a.
    container_a.fill(container_a.capacity());

    // Set container_b equal to container_a.
    assertTrue(container_b = container_a);

    // Verify containers are equal.
    assertTrue(container_b == container_a);
}
/// \brief Tests the std::container::dynamic::base::operator= function with not enough capacity.
test(container_dynamic_base, operator_assignment_over_capacity)
{
    // Create two containers, with container_b having smaller capacity.
    derived container_a(5), container_b(3);

    // Populate container_a.
    container_a.fill(container_a.capacity());

    // Verify setting container_b equal to container_a fails.
    assertFalse(container_b = container_a);

    // Verify container_b is still empty.
    assertTrue(container_b.empty());
}
/// \brief Tests the std::container::dynamic::base::swap function.
test(container_dynamic_base, swap)
{
    // Create and populate container_a.
    derived container_a(5);
    container_a.fill(0x12, container_a.capacity());

    // Create and populate container_b.
    derived container_b(3);
    container_b.fill(0x34, container_b.capacity());

    // Swap the two arrays.
    container_a.swap(container_b);

    // Verify capacities were swapped.
    assertEqual(container_a.capacity(), std::size_t(3));
    assertEqual(container_b.capacity(), std::size_t(5));

    // Verify sizes were swapped.
    assertEqual(container_a.size(), std::size_t(3));
    assertEqual(container_b.size(), std::size_t(5));

    // Verify container_a's elements.
    for(auto entry = container_a.begin(); entry != container_a.end(); ++entry)
    {
        assertEqual(*entry, 0x34);
    }

    // Verify container_b's elements.
    for(auto entry = container_b.begin(); entry != container_b.end(); ++entry)
    {
        assertEqual(*entry, 0x12);
    }
}

// TESTS: COMPARISON
/// \brief Tests the std::container::dynamic::base::operator== function with equal containers.
test(container_dynamic_base, operator_equal_equal)
{
    // Create two populated, equal containers.
    derived container_a(5);
    container_a.fill(container_a.capacity());
    derived container_b(container_a);

    // Verify operator= returns true.
    assertTrue(container_a == container_b);
}
/// \brief Tests the std::container::dynamic::base::operator== function with unequal size containers.
test(container_dynamic_base, operator_equal_unequal_size)
{
    // Create two containers.
    derived container_a(5), container_b(5);

    // Fill the containers with equal values but different sizes.
    container_a.fill(container_a.capacity());
    container_a.fill(3);

    // Verify operator= returns false.
    assertFalse(container_a == container_b);
}
/// \brief Tests the std::container::dynamic::base::operator== function with unequal value containers.
test(container_dynamic_base, operator_equal_unequal_values)
{
    // Create two containers.
    derived container_a(5), container_b(5);

    // Fill the containers with unequal values.
    container_a.fill(container_a.capacity());
    container_b.fill(container_b.capacity());
    *(container_b.end() - 1) = 0xFF;

    // Verify operator== returns false.
    assertFalse(container_a == container_b);
}
/// \brief Tests the std::container::dynamic::base::operator!= function with unequal size containers.
test(container_dynamic_base, operator_unequal_unequal_size)
{
    // Create two containers.
    derived container_a(5), container_b(5);

    // Fill the containers with equal values but different sizes.
    container_a.fill(container_a.capacity());
    container_a.fill(3);

    // Verify operator!= returns true.
    assertTrue(container_a != container_b);
}
/// \brief Tests the std::container::dynamic::base::operator!= function with unequal value containers.
test(container_dynamic_base, operator_unequal_unequal_values)
{
    // Create two containers.
    derived container_a(5), container_b(5);

    // Fill the containers with equal values.
    container_a.fill(container_a.capacity());
    container_b.fill(container_b.capacity());
    *(container_b.end() - 1) = 0xFF;

    // Verify operator!= returns true.
    assertTrue(container_a != container_b);
}
/// \brief Tests the std::container::dynamic::base::operator!= function with equal containers.
test(container_dynamic_base, operator_unequal_equal)
{
    // Create two populated, equal containers.
    derived container_a(5);
    container_a.fill(container_a.capacity());
    derived container_b(container_a);

    // Verify operator!= returns false.
    assertFalse(container_a != container_b);
}

// TESTS: CAPACITY
/// \brief Tests the std::container::dynamic::base::size function.
test(container_dynamic_base, size)
{
    // Create container.
    derived container(5);

    // Verify initial size is zero.
    assertEqual(container.size(), std::size_t(0));

    // Fill the array with 3 elements and verify size.
    container.fill(3);
    assertEqual(container.size(), std::size_t(3));

    // Fill the array with 5 elements and verify size.
    container.fill(5);
    assertEqual(container.size(), std::size_t(5));
}
/// \brief Tests the std::container::dynamic::base::capacity function.
test(container_dynamic_base, capacity)
{
    // Specify capacity.
    const std::size_t capacity = 5;

    // Create container.
    std::container::dynamic::base<uint8_t> container(capacity);

    // Verify capacity.
    assertEqual(container.capacity(), capacity);
}
/// \brief Tests the std::container::dynamic::base::empty function.
test(container_dynamic_base, empty)
{
    // Create empty container.
    derived container(5);

    // Verify container is empty.
    assertTrue(container.empty());

    // Populate container and verify not empty.
    container.fill(container.capacity());
    assertFalse(container.empty());

    // Clear container and verify empty.
    container.clear();
    assertTrue(container.empty());
}
/// \brief Tests the std::container::dynamic::base::full function.
test(container_dynamic_base, full)
{
    // Create empty container.
    derived container(5);

    // Verify container is not full.
    assertFalse(container.full());

    // Populate container halfway and verify not full.
    container.fill(3);
    assertFalse(container.full());

    // Populate container fully and verify full.
    container.fill(container.capacity());
    assertTrue(container.full());

    // Clear container and verify not full.
    container.clear();
    assertFalse(container.full());
}

// TESTS: SHIFT
/// \brief Tests the std::container::dynamic::base::shift_left function with a valid configuration.
test(container_dynamic_base, shift_left)
{
    // Specify container elements after shift.
    // Assumes original container is {0,1,2,3,4,5,6,7}, with position = 5, count = 3.
    uint8_t expected[5] = {0,1,5,6,7};

    // Create and fill container.
    derived container(10);
    container.fill(8);

    // Shift left and verify success.
    assertTrue(container.shift_left(container.begin() + 5, 3));

    // Verify reduced size.
    assertEqual(container.size(), std::size_t(5));

    // Verify container contents after shift.
    for(uint8_t i = 0; i < container.size(); ++i)
    {
        assertEqual(*(container.cbegin() + i), expected[i]);
    }
}
/// \brief Tests the std::container::dynamic::base::shift_left function with an empty container.
test(container_dynamic_base, shift_left_empty)
{
    // Create an empty container.
    derived container(5);

    // Verify left shift fails.
    assertFalse(container.shift_left(container.begin(), 1));
}
/// \brief Tests the std::container::dynamic::base::shift_left function with an invalid position.
test(container_dynamic_base, shift_left_invalid_position)
{
    // Create and fill container.
    derived container(5);
    container.fill(3);

    // Shift left with position before begin and verify failure.
    assertFalse(container.shift_left(container.begin() - 1, 1));

    // Verify size did not change.
    assertEqual(container.size(), std::size_t(3));

    // Shift left with position past end and verify failure.
    assertFalse(container.shift_left(container.end(), 1));

    // Verify size did not change.
    assertEqual(container.size(), std::size_t(3));
}
/// \brief Tests the std::container::dynamic::base::shift_left function with an invalid count.
test(container_dynamic_base, shift_left_invalid_count)
{
    // Create and fill container.
    derived container(5);
    container.fill(3);

    // Shift left with invalid count and verify failure.
    assertFalse(container.shift_left(container.begin() + 1, 5));

    // Verify size did not change.
    assertEqual(container.size(), std::size_t(3));
}
/// \brief Tests the std::container::dynamic::base::shift_right function with a valid configuration.
test(container_dynamic_base, shift_right)
{
    // Specify container elements after shift.
    // Assumes original container is {0,1,2,3,4}, with position = 2, count = 3.
    uint8_t expected[8] = {0,1,2,3,4,2,3,4};

    // Create and fill container.
    derived container(10);
    container.fill(5);

    // Shift right and verify success.
    assertTrue(container.shift_right(container.begin() + 2, 3));

    // Verify increased size.
    assertEqual(container.size(), std::size_t(8));

    // Verify container contents after shift.
    for(uint8_t i = 0; i < container.size(); ++i)
    {
        assertEqual(*(container.cbegin() + i), expected[i]);
    }
}
/// \brief Tests the std::container::dynamic::base::shift_right function with an empty container.
test(container_dynamic_base, shift_right_empty)
{
    // Specify capacity and shift size.
    const std::size_t capacity = 5;
    const std::size_t shift_size = 3;

    // Create an empty container.
    derived container(capacity);

    // Verify right shift succeeds.
    assertTrue(container.shift_right(container.begin(), shift_size));

    // Verify increased size.
    assertEqual(container.size(), shift_size);
}
/// \brief Tests the std::container::dynamic::base::shift_right function with an invalid position.
test(container_dynamic_base, shift_right_invalid_position)
{
    // Create and fill container.
    derived container(5);
    container.fill(3);

    // Shift right with position before begin and verify failure.
    assertFalse(container.shift_right(container.begin() - 1, 1));

    // Verify size did not change.
    assertEqual(container.size(), std::size_t(3));

    // Shift right with position past end and verify failure.
    assertFalse(container.shift_right(container.end() + 1, 1));

    // Verify size did not change.
    assertEqual(container.size(), std::size_t(3));
}
/// \brief Tests the std::container::dynamic::base::shift_right function with an invalid count.
test(container_dynamic_base, shift_right_invalid_count)
{
    // Create and fill container.
    derived container(5);
    container.fill(3);

    // Shift left with invalid count and verify failure.
    assertFalse(container.shift_right(container.begin() + 2, 5));

    // Verify size did not change.
    assertEqual(container.size(), std::size_t(3));
}

}

#endif