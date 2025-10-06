#ifndef TMC5160_CONTROLLER_H
#define TMC5160_CONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <TMCStepper.h>   // official TMC5160 library

class TMC5160Controller {
public:
    // Constructor
    TMC5160Controller(uint8_t csPins[4], uint8_t enPins[4], uint8_t inputPins[4], uint8_t outputPins[5]);

    // Setup and initialization
    void begin();

    // Motor control
    void enableMotor(uint8_t motor);
    void disableMotor(uint8_t motor);
    void moveMotor(uint8_t motor, int32_t velocity);
    void stopMotor(uint8_t motor);
    void setCurrent(uint8_t motor, uint16_t rms_current);
    void setMicrosteps(uint8_t motor, uint16_t microsteps);

    // I/O functions
    bool readInput(uint8_t index);
    void setOutput(uint8_t index, bool state);

private:
    uint8_t _csPins[4];
    uint8_t _enPins[4];
    uint8_t _inputPins[4];
    uint8_t _outputPins[5];

    // 4 motor driver objects
    TMC5160_SPI* drivers[4];
};

#endif
