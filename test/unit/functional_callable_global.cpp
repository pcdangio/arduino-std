// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_FUNCTIONAL_CALLABLE_GLOBAL

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::functional::callable::global {

// UTILITY
/// \brief A global function for testing the global callable.
/// \param[in] value The value to output.
/// \return A copy of the value argument.
uint8_t test_function(uint8_t value)
{
    return value;
}

// TESTS: CONSTRUCTORS
/// \brief Tests the std::functional::callable::global constructor.
test(functional_callable_global, constructor)
{
    // Create a global callback instance with the test_function.
    std::functional::callable::global<uint8_t,uint8_t> global(&test_function);

    // Verify that a valid function is stored.
    assertTrue(global);
}

// TESTS: INVOKE
/// \brief Tests the std::functional::callable::global::operator() function.
test(functional_callable_global, operator_invoke)
{
    // Create a global callback instance with the test_function.
    std::functional::callable::global<uint8_t,uint8_t> global(&test_function);

    // Create an expected argument/return value:
    const uint8_t value = 0x12;

    // Invoke the global and capture the output.
    const uint8_t output = global(value);

    // Verify output.
    assertEqual(output, value);
}

// TESTS: COMPARISON
/// \brief Tests the std::functional::callable::global::operator_bool function.
test(functional_callable_global, operator_bool)
{
    // Create an empty global.
    std::functional::callable::global<uint8_t,uint8_t> global_empty(nullptr);

    // Verify operator_bool returns false with empty global.
    assertFalse(global_empty);

    // Create a global callback instance with the test_function.
    std::functional::callable::global<uint8_t,uint8_t> global_valid(&test_function);

    // Verify operator_bool returns true with valid global.
    assertTrue(global_valid);
}

// TESTS: CLONE
/// \brief Tests the std::functional::callable::global::clone function.
test(functional_callable_global, clone)
{
    // Create a global callback instance with the test_function.
    std::functional::callable::global<uint8_t,uint8_t> global(&test_function);

    // Clone the global into a new base callable pointer:
    std::functional::callable::base<uint8_t,uint8_t>* clone = global.clone();

    // Create an expected argument/return value:
    const uint8_t value = 0x12;

    // Invoke the clone and capture the output.
    const uint8_t output = clone->operator()(value);

    // Verify output.
    assertEqual(output, value);
}

}

#endif