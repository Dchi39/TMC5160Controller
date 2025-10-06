#include <Arduino.h>
#include "TMC5160Controller.h"
#include "I2CIOExpander.h"

// Motor driver pins
uint8_t csPins[4] = {10, 11, 12, 13};
uint8_t enPins[4] = {4, 5, 6, 7};
uint8_t inputPins[4] = {8, 9, 14, 15};
uint8_t outputPins[5] = {16, 17, 18, 19, 20};

// Initialize libraries
TMC5160Controller motors(csPins, enPins, inputPins, outputPins);
I2CIOExpander i2cio(0x20, 16, true);  // Example: MCP23017 at address 0x20

void setup() {
    Serial.begin(115200);
    motors.begin();
    i2cio.begin();

    // Configure expander pins
    for (int i = 0; i < 8; i++) i2cio.pinMode(i, INPUT);     // first 8 as input
    for (int i = 8; i < 16; i++) i2cio.pinMode(i, OUTPUT);   // last 8 as output

    Serial.println("System initialized");
    motors.enableMotor(0);
    i2cio.setOutput(8, HIGH);
}

void loop() {
    // Read extended input
    if (i2cio.readInput(2)) {
        motors.moveMotor(0, 10000);
        i2cio.setOutput(10, HIGH);
    } else {
        motors.stopMotor(0);
        i2cio.setOutput(10, LOW);
    }
    delay(100);
}
