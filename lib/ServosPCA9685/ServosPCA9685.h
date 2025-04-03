//
// Created by boris on 02/04/2025.
//

#ifndef SERVOSPCA9685_H
#define SERVOSPCA9685_H

#include <Wire.h>
#include <SPI.h>//Don't delete
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define PCA9685_I2C_ADDRESS 0x40

#define PCA9685_SDA_PIN PB7
#define PCA9685_SCL_PIN PB6

namespace ServosPCA9685 {
    void Init();
    void Write(uint8_t servo, uint16_t value);

};



#endif //SERVOSPCA9685_H
