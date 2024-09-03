// test_configuration
#include "test_configuration.hpp"

// Compile only if this test is selected.
#ifdef TEST_FUNCTIONAL_CALLABLE_MEMBER

// aunit
#include <AUnit.h>

// std
#include <std.hpp>

namespace test::functional::callable::member {

// UTILITY
/// \brief A class for testing the member callable.
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
/// \brief Tests the std::functional::callable::member constructor.
test(functional_callable_member, constructor)
{
    // Create a test_class instance.
    test_class class_instance;

    // Create a member callback instance with the test_function.
    std::functional::callable::member<test_class, uint8_t,uint8_t> member(&test_class::test_function, &class_instance);

    // Verify that a valid function is stored.
    assertTrue(member);
}

// TESTS: INVOKE
/// \brief Tests the std::functional::callable::member::operator() function.
test(functional_callable_member, operator_invoke)
{
    // Create a test_class instance.
    test_class class_instance;

    // Create a member callback instance with the test_function.
    std::functional::callable::member<test_class, uint8_t,uint8_t> member(&test_class::test_function, &class_instance);

    // Create an expected argument/return value:
    const uint8_t value = 0x12;

    // Invoke the member and capture the output.
    const uint8_t output = member(value);

    // Verify output.
    assertEqual(output, value);

    // Verify class instance captured value.
    assertEqual(class_instance.captured_value, value);
}

// TESTS: PROPERTIES
/// \brief Tests the std::functional::callable::member::operator_bool function.
test(functional_callable_member, operator_bool)
{
    // Create an empty member.
    std::functional::callable::member<test_class, uint8_t,uint8_t> member_empty(nullptr, nullptr);

    // Verify operator_bool returns false with empty member.
    assertFalse(member_empty);

    // Create a test_class instance.
    test_class class_instance;

    // Create a member callback instance with the test_function.
    std::functional::callable::member<test_class, uint8_t,uint8_t> member_valid(&test_class::test_function, &class_instance);

    // Verify operator_bool returns true with valid member.
    assertTrue(member_valid);
}

}

#endif