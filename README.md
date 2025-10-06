# TMC5160Controller + I2C I/O Expander for ESP32-S3

This project provides an easy-to-use C++ Arduino library for controlling up to **4 TMC5160 stepper motor drivers via SPI** along with **extended I/O control via I2C expanders** such as MCP23017 or PCF8574.

---

## 🧩 Features

### Motor Control (TMC5160)
- 4 independent stepper motors
- SPI communication
- Enable/Disable control pins
- Adjustable current and microstepping
- Simple high-level commands (`moveMotor()`, `stopMotor()`)

### I2C I/O Expansion
- Supports 8/16-bit expanders
- Read inputs and set outputs easily
- Multiple devices supported via unique I2C addresses

---

## 📁 Folder Structure
```
TMC5160Controller/
├── lib/
│ ├── TMC5160Controller/
│ └── I2CIOExpander/
├──
│ └── main.cpp

---

## 🧠 Example Usage

```cpp
#include "TMC5160Controller.h"
#include "I2CIOExpander.h"

// Pins for ESP32-S3 board
uint8_t csPins[4] = {10, 11, 12, 13};
uint8_t enPins[4] = {4, 5, 6, 7};
uint8_t inputPins[4] = {8, 9, 14, 15};
uint8_t outputPins[5] = {16, 17, 18, 19, 20};

TMC5160Controller motors(csPins, enPins, inputPins, outputPins);
I2CIOExpander i2cio(0x20, 16, true); // Example MCP23017 at 0x20

void setup() {
    Serial.begin(115200);
    motors.begin();
    i2cio.begin();
    for (int i = 0; i < 8; i++) i2cio.pinMode(i, INPUT);
    for (int i = 8; i < 16; i++) i2cio.pinMode(i, OUTPUT);
    motors.enableMotor(0);
}

void loop() {
    if (i2cio.readInput(2)) {
        motors.moveMotor(0, 20000);
        i2cio.setOutput(10, HIGH);
    } else {
        motors.stopMotor(0);
        i2cio.setOutput(10, LOW);
    }
    delay(100);
}
---

## 🧰 Dependencies

Install these libraries in your Arduino/PlatformIO environment:
- [TMCStepper](https://github.com/teemuatlut/TMCStepper)
- [Arduino Core for ESP32](https://github.com/espressif/arduino-esp32)


