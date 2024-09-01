// aunit
#include <AUnit.h>

// NOTE: Use test_configuration.hpp to define which tests will be compiled/run.

// Execute setup tasks.
void setup()
{
    // Open serial port.
    Serial.begin(115200);

    // Wait for board initialization to settle.
    delay(1000);
}

// Execute continuous tasks.
void loop()
{
    // Execute unit tests.
    aunit::TestRunner::run();
}