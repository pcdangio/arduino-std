// aunit
#include <AUnit.h>

// arduino
#include <Arduino.h>

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