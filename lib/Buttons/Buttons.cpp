//
// Created by boris on 03/01/2025.
//

#include "Buttons.h"

Buttons::Buttons(uint32_t pin, uint32_t inMode) {
    pinMode(pin, inMode);
    this->_pin = pin;
    this->isIT = false;
}

Buttons::Buttons(uint32_t pin, uint32_t inMode, callback_function_t onPress, uint32_t mode) {
    pinMode(pin, inMode);
    this->_pin = pin;
    attachInterrupt(digitalPinToInterrupt(this->_pin), onPress, mode);
    this->isIT = true;
}

bool Buttons::getState() {
    return digitalRead(this->_pin);
}

LedButton::LedButton(uint32_t Btnpin, uint32_t inMode, uint32_t Ledpin): Buttons(Btnpin, inMode) {
    pinMode(Ledpin, OUTPUT);
    this->_ledPin = Ledpin;
    this->_ledState = false;
}

LedButton::LedButton(uint32_t Btnpin, uint32_t inMode, uint32_t Ledpin, callback_function_t onPress, uint32_t mode): Buttons(Btnpin, inMode, onPress, mode) {
    pinMode(Ledpin, OUTPUT);
    this->_ledPin = Ledpin;
    this->_ledState = false;
}

void LedButton::setLedState(bool state) {
    this->_ledState = state;
    digitalWrite(this->_ledPin, state);
}

bool LedButton::getLedState() {
    return this->_ledState;
}

void LedButton::toggleLedState() {
    this->_ledState = !this->_ledState;
    digitalWrite(this->_ledPin, this->_ledState);
}
