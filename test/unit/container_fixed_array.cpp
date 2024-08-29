#include <AUnit.h>

// std
#include <std.hpp>

namespace test::container::fixed::array {

// UTILITY
/// \brief Populates an array with incremental values.
/// \param[in] begin The begin iterator of the array.
/// \param[in] end The end iterator of the array.
/// \param[in] start The starting value to increment from.
void populate_array(std::iterator<uint8_t> begin, std::iterator<uint8_t> end, uint8_t start = 0)
{
    // Set array values to indices.
    uint8_t i = start;
    for(auto entry = begin; entry != end; ++entry)
    {
        *entry = i++;
    }
}

// TESTS: ACCESS
/// \brief Tests the std::array::operator[] function.
test(container_fixed_array, bracket_operator)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());

    // Verify at() at all indices returns the correct value.
    for(size_t i = 0; i < array.size(); ++i)
    {
        assertEqual(array[i], uint8_t(i));
    }
}
/// \brief Tests the std::array::operator[] const function.
test(container_fixed_array, bracket_operator_const)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());

    // Create a const copy of the array.
    const std::array<uint8_t,5> const_array(array);

    // Verify at() at all indices returns the correct value.
    for(size_t i = 0; i < const_array.size(); ++i)
    {
        assertEqual(const_array[i], uint8_t(i));
    }
}
/// \brief Tests the std::array::at function.
test(container_fixed_array, at)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());
    
    // Verify at() at all indices returns the correct value.
    for(size_t i = 0; i < array.size(); ++i)
    {
        assertEqual(array.at(i), uint8_t(i));
    }
}
/// \brief Tests the std::array::at const function.
test(container_fixed_array, at_const)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());

    // Create a const copy of the array.
    const std::array<uint8_t,5> const_array(array);

    // Verify at() at all indices returns the correct value.
    for(size_t i = 0; i < const_array.size(); ++i)
    {
        assertEqual(const_array.at(i), uint8_t(i));
    }
}
/// \brief Tests the std::array::front function.
test(container_fixed_array, front)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());

    // Verify front gives zero.
    assertEqual(array.front(), uint8_t(0));
}
/// \brief Tests the std::array::front const function.
test(container_fixed_array, front_const)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());

    // Create a const copy of the array.
    const std::array<uint8_t,5> const_array(array);

    // Verify front gives zero.
    assertEqual(const_array.front(), uint8_t(0));
}
/// \brief Tests the std::array::back function.
test(container_fixed_array, back)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());

    // Verify back gives size-1.
    assertEqual(array.back(), uint8_t(array.size()-1));
}
/// \brief Tests the std::array::back const function.
test(container_fixed_array, back_const)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Populate array with indices.
    populate_array(array.begin(), array.end());

    // Create a const copy of the array.
    const std::array<uint8_t,5> const_array(array);

    // Verify back gives size-1.
    assertEqual(const_array.back(), uint8_t(array.size()-1));
}
/// \brief Tests the std::array::data function.
test(container_fixed_array, data)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Verify data matches the begin iterator.
    assertEqual(array.data(), array.begin());
}
/// \brief Tests the std::array::data const function.
test(container_fixed_array, data_const)
{
    // Create array.
    std::array<uint8_t,5> array;

    // Create a const copy of the array.
    const std::array<uint8_t,5> const_array(array);

    // Verify data matches the begin iterator.
    assertEqual(const_array.data(), const_array.cbegin());
}

// TESTS: OPERATIONS
/// \brief Tests the std::array::operator= function.
test(container_fixed_array, assignment_operator)
{
    // Create two arrays.
    std::array<uint8_t,5> array_a, array_b;

    // Populate A.
    populate_array(array_a.begin(), array_a.end());

    // Assign A to B.
    array_b = array_a;

    // Verify contents of B.
    uint8_t i = 0;
    for(auto entry = array_b.begin(); entry != array_b.end(); ++entry)
    {
        assertEqual(*entry, i++);
    }
}
/// \brief Tests the std::array::fill function.
test(container_fixed_array, fill)
{
    // Specify fill value.
    const uint8_t value = 0x12;

    // Create array.
    std::array<uint8_t,5> array;

    // Fill array.
    array.fill(value);

    // Verify contents of the array.
    for(auto entry = array.begin(); entry != array.end(); ++entry)
    {
        assertEqual(*entry, value);
    }
}
/// \brief Tests the std::array::swap function.
test(container_fixed_array, swap)
{
    // Specify array values.
    const uint8_t value_a = 0x12;
    const uint8_t value_b = 0x34;

    // Create two arrays.
    std::array<uint8_t,5> array_a, array_b;

    // Populate A starting from 0.
    populate_array(array_a.begin(), array_a.end(), 0);

    // Populate B starting from 100.
    populate_array(array_b.begin(), array_b.end(), 100);

    // Swap the two arrays.
    array_a.swap(array_b);

    // Verify contents of A.
    uint8_t i = 100;
    for(auto entry = array_a.begin(); entry != array_a.end(); ++entry)
    {
        assertEqual(*entry, i++);
    }

    // Verify contents of B.
    i = 0;
    for(auto entry = array_b.begin(); entry != array_b.end(); ++entry)
    {
        assertEqual(*entry, i++);
    }
}

}