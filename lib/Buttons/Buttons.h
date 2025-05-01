//
// Created by boris on 03/01/2025.
//

#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>


class Buttons {
    public:
        Buttons(uint32_t pin, uint32_t inMode);
        Buttons(uint32_t pin, uint32_t inMode, callback_function_t onPress, uint32_t mode=RISING);

        bool getState();
    private:
        uint32_t _pin;
        bool isIT;
};


class LedButton: public Buttons {
    public:
        LedButton(uint32_t Btnpin, uint32_t inMode, uint32_t Ledpin);
        LedButton(uint32_t Btnpin, uint32_t inMode, uint32_t Ledpin, callback_function_t onPress, uint32_t mode=RISING);

        void setLedState(bool state);
        bool getLedState();
        void toggleLedState();
    private:
        uint32_t _ledPin;
        bool _ledState;
};


#endif //BUTTONS_H
