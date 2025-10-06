#ifndef I2C_IO_EXPANDER_H
#define I2C_IO_EXPANDER_H

#include <Arduino.h>
#include <Wire.h>

class I2CIOExpander {
public:
    I2CIOExpander(uint8_t i2cAddress, uint8_t totalPins = 8, bool is16bit = false);

    void begin();
    void pinMode(uint8_t pin, uint8_t mode);
    bool readInput(uint8_t pin);
    void setOutput(uint8_t pin, bool state);

    void writeAll(uint16_t value);
    uint16_t readAll();

private:
    uint8_t _address;
    uint8_t _totalPins;
    bool _is16bit;
    uint16_t _pinState;
    uint16_t _pinMode;

    void writeRegister(uint8_t reg, uint16_t value);
    uint16_t readRegister(uint8_t reg);
};

#endif
