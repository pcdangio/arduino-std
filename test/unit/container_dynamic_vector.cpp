// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_CONTAINER_DYNAMIC_VECTOR

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::container::dynamic::vector {

// UTILITY
/// \brief Fills a vector with sequential values.
/// \param[in] vector The vector to fill.
/// \param[in] size The number of sequential values to append.
void fill_vector(std::vector<uint8_t>& vector, std::size_t size)
{
    for(std::size_t i = 0; i < size; ++i)
    {
        vector.push_back(i);
    }
}

// ACCESS
/// \brief Tests the std::vector::operator[] function.
test(container_dynamic_vector, bracket_operator)
{
    // Specify a capacity.
    const std::size_t capacity = 5;

    // Create and fill a vector.
    std::vector<uint8_t> vector(capacity);
    fill_vector(vector, capacity);
    
    // Verify access over entire range.
    for(std::size_t i = 0; i < capacity; ++i)
    {
        assertEqual(vector[i], uint8_t(i));
    }

    // Specify a position value.
    const std::size_t index = 1;
    const uint8_t value = 33;

    // Set a value.
    vector[index] = value;

    // Verify value was set.
    assertEqual(vector[index], value);
}
/// \brief Tests the std::vector::operator[] const function.
test(container_dynamic_vector, bracket_operator_const)
{
    // Specify a capacity.
    const std::size_t capacity = 5;

    // Create and fill a vector.
    std::vector<uint8_t> vector(capacity);
    fill_vector(vector, capacity);

    // Copy construct a const vector.
    const std::vector<uint8_t> const_vector(vector);
    
    // Verify access over entire range.
    for(std::size_t i = 0; i < capacity; ++i)
    {
        assertEqual(const_vector[i], uint8_t(i));
    }
}
/// \brief Tests the std::vector::at function.
test(container_dynamic_vector, at)
{
    // Specify a capacity.
    const std::size_t capacity = 5;

    // Create and fill a vector.
    std::vector<uint8_t> vector(capacity);
    fill_vector(vector, capacity);
    
    // Verify access over entire range.
    for(std::size_t i = 0; i < capacity; ++i)
    {
        assertEqual(vector.at(i), uint8_t(i));
    }

    // Specify a position value.
    const std::size_t index = 1;
    const uint8_t value = 33;

    // Set a value.
    vector.at(index) = value;

    // Verify value was set.
    assertEqual(vector.at(index), value);
}
/// \brief Tests the std::vector::at const function.
test(container_dynamic_vector, at_const)
{
    // Specify a capacity.
    const std::size_t capacity = 5;

    // Create and fill a vector.
    std::vector<uint8_t> vector(capacity);
    fill_vector(vector, capacity);

    // Copy construct a const vector.
    const std::vector<uint8_t> const_vector(vector);
    
    // Verify access over entire range.
    for(std::size_t i = 0; i < capacity; ++i)
    {
        assertEqual(const_vector.at(i), uint8_t(i));
    }
}
/// \brief Tests the std::vector::front function.
test(container_dynamic_vector, front)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    fill_vector(vector, vector.capacity());

    // Verify front returns first element.
    assertEqual(vector.front(), uint8_t(0));
}
/// \brief Tests the std::vector::front const function.
test(container_dynamic_vector, front_const)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    fill_vector(vector, vector.capacity());

    // Copy construct a const vector.
    const std::vector<uint8_t> const_vector(vector);

    // Verify front returns first element.
    assertEqual(const_vector.front(), uint8_t(0));
}
/// \brief Tests the std::vector::back function.
test(container_dynamic_vector, back)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    fill_vector(vector, vector.capacity());

    // Verify back returns last element.
    assertEqual(vector.back(), uint8_t(4));
}
/// \brief Tests the std::vector::front const function.
test(container_dynamic_vector, back_const)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    fill_vector(vector, vector.capacity());

    // Copy construct a const vector.
    const std::vector<uint8_t> const_vector(vector);

    // Verify back returns last element.
    assertEqual(const_vector.back(), uint8_t(4));
}
/// \brief Tests the std::vector::data function.
test(container_dynamic_vector, data)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    fill_vector(vector, vector.capacity());

    // Verify data returns a pointer to the first element.
    assertEqual(*vector.data(), uint8_t(0));
}
/// \brief Tests the std::vector::data const function.
test(container_dynamic_vector, data_const)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    fill_vector(vector, vector.capacity());

    // Copy construct a const vector.
    const std::vector<uint8_t> const_vector(vector);

    // Verify data returns a pointer to the first element.
    assertEqual(*const_vector.data(), uint8_t(0));
}

// MODIFIERS
/// \brief Tests the std::vector::push_back function with a valid configuration.
test(container_dynamic_vector, push_back)
{
    // Specify a capacity.
    const std::size_t capacity = 5;

    // Create a vector.
    std::vector<uint8_t> vector(capacity);

    // Push back elements until capacity filled.
    for(std::size_t i = 0; i < capacity; ++i)
    {
        assertTrue(vector.push_back(i));
    }

    // Verify vector size.
    assertEqual(vector.size(), capacity);

    // Verify components.
    for(uint8_t i = 0; i < capacity; ++i)
    {
        assertEqual(vector[i], i);
    }
}
/// \brief Tests the std::vector::push_back function with not enough capacity.
test(container_dynamic_vector, push_back_over_capacity)
{
    // Specify a capacity.
    const std::size_t capacity = 5;

    // Create a vector.
    std::vector<uint8_t> vector(capacity);

    // Push back elements until capacity filled.
    for(std::size_t i = 0; i < capacity; ++i)
    {
        vector.push_back(i);
    }

    // Try to push back over capacity.
    assertFalse(vector.push_back(100));

    // Verify vector size.
    assertEqual(vector.size(), capacity);

    // Verify elements.
    for(uint8_t i = 0; i < capacity; ++i)
    {
        assertEqual(vector[i], i);
    }
}
/// \brief Tests the std::vector::pop_back function with a valid configuration.
test(container_dynamic_vector, pop_back)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    fill_vector(vector, vector.capacity());

    // Pop an element off the back.
    vector.pop_back();

    // Verify vector size.
    assertEqual(vector.size(), vector.capacity() - 1);

    // Verify elements.
    for(uint8_t i = 0; i < vector.size(); ++i)
    {
        assertEqual(vector[i], i);
    }
}
/// \brief Tests the std::vector::pop_back function with an empty vector.
test(container_dynamic_vector, pop_back_empty)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Try to pop an element off the back.
    vector.pop_back();

    // Verify vector is empty.
    assertTrue(vector.empty());
}
/// \brief Tests the std::vector::insert function with a valid configuration.
test(container_dynamic_vector, insert)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Insert a value at the beginning.
    const uint8_t value = 0x12;
    auto position = vector.insert(vector.begin(), value);

    // Verify position still points to begin.
    assertEqual(position, vector.begin());

    // Verify new size.
    assertEqual(vector.size(), std::size_t(1));

    // Verify value was inserted.
    assertEqual(vector[0], value);

    // Assign the vector to all zeros, with space for one more value.
    vector.assign(0, 4);

    // Specify expected vector value.
    uint8_t expected_value[5] = {0,0,value,0,0};

    // Insert a value in the middle.
    position = vector.insert(vector.begin() + 2, value);

    // Verify position points to the insertion position.
    assertEqual(vector.begin() + 2, position);

    // Verify vector size.
    assertEqual(vector.size(), std::size_t(5));

    // Verify vector elements.
    for(std::size_t i = 0; i < vector.size(); ++i)
    {
        assertEqual(vector[i], expected_value[i]);
    }
}
/// \brief Tests the std::vector::insert function with an invalid position.
test(container_dynamic_vector, insert_invalid_position)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Verify insertion before vector begin fails.
    assertEqual(vector.insert(vector.begin() - 1, 0), nullptr);

    // Verify vector is still empty.
    assertTrue(vector.empty());

    // Verify insertion after vector end fails.
    assertEqual(vector.insert(vector.end() + 1, 0), nullptr);

    // Verify vector is still empty.
    assertTrue(vector.empty());
}
/// \brief Tests the std::vector::insert function with not enough capacity.
test(container_dynamic_vector, insert_over_capacity)
{
    // Create and fill a vector.
    std::vector<uint8_t> vector(5);
    vector.assign(0, vector.capacity());

    // Verify insertion before vector begin fails.
    assertEqual(vector.insert(vector.begin(), 0x12), nullptr);

    // Verify vector is still all zeros.
    for(auto entry = vector.begin(); entry != vector.end(); ++entry)
    {
        assertEqual(*entry, 0);
    }
}
/// \brief Tests the std::vector::assign value function with a valid configuration.
test(container_dynamic_vector, assign_value)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Specify values for assignment.
    const uint8_t value_a = 0x12;
    const uint8_t value_b = 0x34;

    // Assign all of vector to value_a.
    assertTrue(vector.assign(value_a, vector.capacity()));

    // Verify vector size.
    assertTrue(vector.full());

    // Verify values.
    for(auto entry = vector.begin(); entry != vector.end(); ++entry)
    {
        assertEqual(*entry, value_a);
    }

    // Assign value_b to 3 elements of the vector.
    assertTrue(vector.assign(value_b, 3));

    // Verify vector size.
    assertEqual(vector.size(), std::size_t(3));

    // Verify values.
    for(auto entry = vector.begin(); entry != vector.end(); ++entry)
    {
        assertEqual(*entry, value_b);
    }
}
/// \brief Tests the std::vector::assign value function with not enough capacity.
test(container_dynamic_vector, assign_value_over_capacity)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Verify assigning a value with a count greater than capacity fails.
    assertFalse(vector.assign(0, vector.capacity() + 1));
}
/// \brief Tests the std::vector::assign range function with a valid configuration.
test(container_dynamic_vector, assign_range)
{
    // Create two vectors.
    std::vector<uint8_t> vector_a(5), vector_b(5);

    // Populate vector_a.
    vector_a.assign(0, vector_a.capacity());

    // Assign vector_a to vector_b.
    assertTrue(vector_b.assign(vector_a.begin(), vector_a.end()));

    // Verify vector_b's size.
    assertEqual(vector_b.size(), vector_a.size());

    // Verify vector_b's values.
    for(auto entry = vector_b.begin(); entry != vector_b.end(); ++entry)
    {
        assertEqual(*entry, 0);
    }

    // Assign part of vector_a to vector_b.
    assertTrue(vector_b.assign(vector_a.begin(), vector_a.begin() + 3));

    // Verify vector_b's size.
    assertEqual(vector_b.size(), std::size_t(3));

    // Verify vector_b's values.
    for(auto entry = vector_b.begin(); entry != vector_b.end(); ++entry)
    {
        assertEqual(*entry, 0);
    }
}
/// \brief Tests the std::vector::assign range function with not enough capacity.
test(container_dynamic_vector, assign_range_over_capacity)
{
    // Create two vectors, with vector_b capacity smaller than vector_a.
    std::vector<uint8_t> vector_a(5), vector_b(3);

    // Populate vector_a.
    vector_a.assign(0, vector_a.capacity());

    // Verify assigning vector_a to vector_b fails due to over capacity.
    assertFalse(vector_b.assign(vector_a.begin(), vector_a.end()));

    // Verify vector_b is still empty.
    assertTrue(vector_b.empty());
}
/// \brief Tests the std::vector::resize default function with a valid configuration.
test(container_dynamic_vector, resize_default)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Resize the vector to capacity with default constructed values.
    assertTrue(vector.resize(vector.capacity()));

    // Verify vector's size.
    assertTrue(vector.full());

    // Verify vector_b's values.
    for(auto entry = vector.begin(); entry != vector.end(); ++entry)
    {
        assertEqual(*entry, 0);
    }

    // Resize vector to 3 elements.
    assertTrue(vector.resize(3));

    // Verify vector's size.
    assertEqual(vector.size(), std::size_t(3));

    // Verify vector_b's values.
    for(auto entry = vector.begin(); entry != vector.end(); ++entry)
    {
        assertEqual(*entry, 0);
    }
}
/// \brief Tests the std::vector::resize default function with not enough capacity.
test(container_dynamic_vector, resize_default_over_capacity)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Verify resizing the vector over capacity fails.
    assertFalse(vector.resize(vector.capacity() + 1));

    // Verify vector is empty.
    assertTrue(vector.empty());
}
/// \brief Tests the std::vector::resize value function with a valid configuration.
test(container_dynamic_vector, resize_value)
{
    // Specify value.
    const uint8_t value = 0x12;

    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Resize the vector to capacity with specified value.
    assertTrue(vector.resize(vector.capacity(), value));

    // Verify vector's size.
    assertTrue(vector.full());

    // Verify vector_b's values.
    for(auto entry = vector.begin(); entry != vector.end(); ++entry)
    {
        assertEqual(*entry, value);
    }

    // Resize vector to 3 elements.
    assertTrue(vector.resize(3, value));

    // Verify vector's size.
    assertEqual(vector.size(), std::size_t(3));

    // Verify vector_b's values.
    for(auto entry = vector.begin(); entry != vector.end(); ++entry)
    {
        assertEqual(*entry, value);
    }
}
/// \brief Tests the std::vector::resize value function with not enough capacity.
test(container_dynamic_vector, resize_value_over_capacity)
{
    // Create an empty vector.
    std::vector<uint8_t> vector(5);

    // Verify resizing the vector over capacity fails.
    assertFalse(vector.resize(vector.capacity() + 1, 0x12));

    // Verify vector is empty.
    assertTrue(vector.empty());
}

}

#endif