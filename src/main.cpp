#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <HardwareTimer.h>

void setup() {
// write your initialization code here
    Serial.begin(9600);
}

/**
 * @brief Test
 */
void loop() {
    Serial.println("J'aime le Club Robot");
    delay(100);
}
