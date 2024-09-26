// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_FUNCTIONAL_FUNCTION

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::functional::function {

// UTILITY
/// \brief A global function for testing the std::function.
/// \param[in] value The value to output.
/// \return A copy of the value argument.
uint8_t test_function(uint8_t value)
{
    return value;
}
/// \brief A class for testing the std::function.
class test_class
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new test_class instance.
    test_class()
        : captured_value(0)
    {}

    // FUNCTIONS
    /// \brief A member function for testing the member callable.
    /// \param[in] value The value to store and output.
    /// \return A copy of the value argument.
    uint8_t test_function(uint8_t value)
    {
        // Capture value.
        test_class::captured_value = value;

        // Return value.
        return value;
    }

    // TRACKERS
    /// \brief Captures the last value passed to the test_function function.
    uint8_t captured_value;
};

// TESTS: CONSTRUCTORS
/// \brief Tests the std::function default constructor.
test(functional_function, constructor_default)
{
    // Default-construct an std::function.
    std::function<void()> function;

    // Verify function is not valid.
    assertFalse(function);
}
/// \brief Tests the std::function global-function constructor.
test(functional_function, constructor_global)
{
    // Construct an std::function with a global function pointer.
    std::function<uint8_t(uint8_t)> function(&test_function);

    // Verify function is valid.
    assertTrue(function);
}
/// \brief Tests the std::function member-function constructor.
test(functional_function, constructor_member)
{
    // Create a test_class instance.
    test_class class_instance;

    // Construct an std::function with a member function pointer.
    std::function<uint8_t(uint8_t)> function(&test_class::test_function, &class_instance);

    // Verify function is valid.
    assertTrue(function);
}
/// \brief Tests the std::function copy constructor.
test(functional_function, constructor_copy)
{
    // Construct an std::function with a global function pointer.
    std::function<uint8_t(uint8_t)> function_a(&test_function);

    // Copy-construct a second std::function.
    std::function<uint8_t(uint8_t)> function_b(function_a);

    // Verify function_b is valid.
    assertTrue(function_b);
}
/// \brief Tests the std::function copy constructor with a null function.
test(functional_function, constructor_copy_null)
{
    // Construct an empty std::function.
    std::function<uint8_t(uint8_t)> function_a;

    // Copy-construct a second std::function.
    std::function<uint8_t(uint8_t)> function_b(function_a);

    // Verify function_b is invalid.
    assertFalse(function_b);
}
/// \brief Tests the std::function move constructor.
test(functional_function, constructor_move)
{
    // Construct an std::function with a global function pointer.
    std::function<uint8_t(uint8_t)> function_a(&test_function);

    // Move-construct a second std::function.
    std::function<uint8_t(uint8_t)> function_b(std::move(function_a));

    // Verify function_b is valid.
    assertTrue(function_b);

    // Verify function_a is invalid.
    assertFalse(function_a);
}

// TESTS: MODIFIERS
/// \brief Tests the std::function::swap function.
test(functional_function, swap)
{
    // Construct an empty function.
    std::function<uint8_t(uint8_t)> function_a;

    // Construct an std::function with a global function pointer.
    std::function<uint8_t(uint8_t)> function_b(&test_function);

    // Swap the two functions.
    function_a.swap(function_b);

    // Verify function_a is now valid.
    assertTrue(function_a);

    // Verify function_b is now invalid.
    assertFalse(function_b);
}
/// \brief Tests the std::function::operator= copy function.
test(functional_function, operator_assign_copy)
{
    // Construct an std::function with a global function pointer.
    std::function<uint8_t(uint8_t)> function_a(&test_function);

    // Construct an empty function.
    std::function<uint8_t(uint8_t)> function_b;

    // Copy assign function_a to function_b.
    function_b = function_a;

    // Verify function_a is valid.
    assertTrue(function_a);

    // Verify function_b is now valid.
    assertTrue(function_b);
}
/// \brief Tests the std::function::operator= copy function with an empty function.
test(functional_function, operator_assign_copy_empty)
{
    // Construct an empty function.
    std::function<uint8_t(uint8_t)> function_a;

    // Construct an std::function with a global function pointer.
    std::function<uint8_t(uint8_t)> function_b(&test_function);

    // Copy assign function_a to function_b.
    function_b = function_a;

    // Verify function_a is invalid.
    assertFalse(function_a);

    // Verify function_b is now invalid.
    assertFalse(function_b);
}
/// \brief Tests the std::function::operator= move function.
test(functional_function, operator_assign_move)
{
    // Construct an std::function with a global function pointer.
    std::function<uint8_t(uint8_t)> function_a(&test_function);

    // Construct an empty function.
    std::function<uint8_t(uint8_t)> function_b;

    // Move assign function_a to function_b.
    function_b = std::move(function_a);

    // Verify function_a is now invalid.
    assertFalse(function_a);

    // Verify function_b is now valid.
    assertTrue(function_b);
}

// TESTS: INVOKE
/// \brief Tests the std::function::operator() function with a global callable.
test(functional_function, operator_invoke_global)
{
    // Create a global callback instance with the test_function.
    std::function<uint8_t(uint8_t)> function(&test_function);

    // Create an expected argument/return value:
    const uint8_t value = 0x12;

    // Invoke the function and capture the output.
    const uint8_t output = function(value);

    // Verify output.
    assertEqual(output, value);
}
/// \brief Tests the std::function::operator() function with a member callable.
test(functional_function, operator_invoke_member)
{
    // Create a test_class instance.
    test_class class_instance;

    // Construct an std::function with a member function pointer.
    std::function<uint8_t(uint8_t)> function(&test_class::test_function, &class_instance);

    // Create an expected argument/return value:
    const uint8_t value = 0x12;

    // Invoke the function and capture the output.
    const uint8_t output = function(value);

    // Verify output.
    assertEqual(output, value);

    // Verify value was captured in class_instance.
    assertEqual(class_instance.captured_value, value);
}

// TESTS: COMPARISON
/// \brief Tests the std::function::operator_bool function.
test(functional_function, operator_bool)
{
    // Create an empty function.
    std::function<void()> function_empty(nullptr);

    // Verify operator_bool returns false with empty function.
    assertFalse(function_empty);

    // Create a function instance with the test_function.
    std::function<uint8_t(uint8_t)> function_valid(&test_function);

    // Verify operator_bool returns true with valid function.
    assertTrue(function_valid);
}

}

#endif