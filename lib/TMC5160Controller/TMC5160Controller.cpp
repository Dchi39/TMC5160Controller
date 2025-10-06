#include "TMC5160Controller.h"

TMC5160Controller::TMC5160Controller(uint8_t csPins[4], uint8_t enPins[4], uint8_t inputPins[4], uint8_t outputPins[5]) {
    memcpy(_csPins, csPins, 4);
    memcpy(_enPins, enPins, 4);
    memcpy(_inputPins, inputPins, 4);
    memcpy(_outputPins, outputPins, 5);
}

void TMC5160Controller::begin() {
    SPI.begin();
    for (int i = 0; i < 4; i++) {
        pinMode(_csPins[i], OUTPUT);
        pinMode(_enPins[i], OUTPUT);
        digitalWrite(_enPins[i], HIGH); // disable motors initially
        drivers[i] = new TMC5160_SPI(_csPins[i], SPI);
        drivers[i]->begin();
        drivers[i]->rms_current(800); // Default 800mA
        drivers[i]->microsteps(16);
        drivers[i]->toff(5);
    }

    for (int i = 0; i < 4; i++) pinMode(_inputPins[i], INPUT_PULLUP);
    for (int i = 0; i < 5; i++) {
        pinMode(_outputPins[i], OUTPUT);
        digitalWrite(_outputPins[i], LOW);
    }
}

void TMC5160Controller::enableMotor(uint8_t motor) {
    if (motor < 4) digitalWrite(_enPins[motor], LOW);
}

void TMC5160Controller::disableMotor(uint8_t motor) {
    if (motor < 4) digitalWrite(_enPins[motor], HIGH);
}

void TMC5160Controller::moveMotor(uint8_t motor, int32_t velocity) {
    if (motor < 4) drivers[motor]->VMAX(velocity);
}

void TMC5160Controller::stopMotor(uint8_t motor) {
    if (motor < 4) drivers[motor]->VMAX(0);
}

void TMC5160Controller::setCurrent(uint8_t motor, uint16_t rms_current) {
    if (motor < 4) drivers[motor]->rms_current(rms_current);
}

void TMC5160Controller::setMicrosteps(uint8_t motor, uint16_t microsteps) {
    if (motor < 4) drivers[motor]->microsteps(microsteps);
}

bool TMC5160Controller::readInput(uint8_t index) {
    if (index < 4) return digitalRead(_inputPins[index]);
    return false;
}

void TMC5160Controller::setOutput(uint8_t index, bool state) {
    if (index < 5) digitalWrite(_outputPins[index], state);
}
