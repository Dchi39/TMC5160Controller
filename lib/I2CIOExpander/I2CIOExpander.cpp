#include "I2CIOExpander.h"

// Generic 8/16-bit I2C expander (works with MCP23017, PCF8574, etc.)

I2CIOExpander::I2CIOExpander(uint8_t i2cAddress, uint8_t totalPins, bool is16bit)
    : _address(i2cAddress), _totalPins(totalPins), _is16bit(is16bit), _pinState(0), _pinMode(0xFFFF) {}

void I2CIOExpander::begin() {
    Wire.begin();
    delay(50);
}

void I2CIOExpander::pinMode(uint8_t pin, uint8_t mode) {
    if (pin >= _totalPins) return;
    if (mode == OUTPUT)
        _pinMode &= ~(1 << pin);
    else
        _pinMode |= (1 << pin);
}

bool I2CIOExpander::readInput(uint8_t pin) {
    if (pin >= _totalPins) return false;
    uint16_t val = readAll();
    return (val >> pin) & 0x01;
}

void I2CIOExpander::setOutput(uint8_t pin, bool state) {
    if (pin >= _totalPins) return;
    if (state)
        _pinState |= (1 << pin);
    else
        _pinState &= ~(1 << pin);
    writeAll(_pinState);
}

void I2CIOExpander::writeAll(uint16_t value) {
    _pinState = value;
    Wire.beginTransmission(_address);
    if (_is16bit) {
        Wire.write((uint8_t)(value & 0xFF));
        Wire.write((uint8_t)(value >> 8));
    } else {
        Wire.write((uint8_t)(value & 0xFF));
    }
    Wire.endTransmission();
}

uint16_t I2CIOExpander::readAll() {
    uint16_t value = 0;
    Wire.requestFrom(_address, (uint8_t)(_is16bit ? 2 : 1));
    if (_is16bit && Wire.available() >= 2) {
        value = Wire.read();
        value |= (Wire.read() << 8);
    } else if (Wire.available() >= 1) {
        value = Wire.read();
    }
    return value;
}

void I2CIOExpander::writeRegister(uint8_t reg, uint16_t value) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value & 0xFF);
    if (_is16bit) Wire.write(value >> 8);
    Wire.endTransmission();
}

uint16_t I2CIOExpander::readRegister(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_address, (uint8_t)(_is16bit ? 2 : 1));

    uint16_t val = 0;
    if (_is16bit && Wire.available() >= 2) {
        val = Wire.read();
        val |= (Wire.read() << 8);
    } else if (Wire.available() >= 1) {
        val = Wire.read();
    }
    return val;
}
