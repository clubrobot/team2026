//
// Created by boris on 02/04/2025.
//

#include "ServosPCA9685.h"


static TwoWire twoWire;
static Adafruit_PWMServoDriver pwm;

void ServosPCA9685::Init() {
    twoWire = TwoWire(PCA9685_SDA_PIN, PCA9685_SCL_PIN);//SDA SCL
    pwm = Adafruit_PWMServoDriver(PCA9685_I2C_ADDRESS, twoWire);

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    delay(10);
}

void ServosPCA9685::Write(uint8_t servo, uint16_t angle) {
    uint16_t microsec = angle*11.1;
    if (microsec < USMIN)
        microsec=USMIN;
    else if (microsec > USMAX)
        microsec=USMAX;
    pwm.writeMicroseconds(servo, microsec);
}
