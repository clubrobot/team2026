#include <Arduino.h>
#include <STM32FreeRTOS.h>

#include "wheeledbase/wb_thread.h"


#define TEST_NO_FREERTOS true //Ignore le FreeRTOS et se comporte comme un arduino classique

void setup(){
    //Setup de base
    Serial.begin(9600);

    wb_setup();//Setup de la base roulante dans wb_thread

    if(TEST_NO_FREERTOS) {
        return;
    }
    //Setup FreeRTOS

    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    Error_Handler(); //TODO: logger l'error handler
}
long a,b,c,d;

void loop() {
    //loop seuleuement accesssible quand TEST_NO_FREERTOS est à true
    a = leftCodewheel.getCounter();
    b = rightCodewheel.getCounter();
    c = leftCodewheel.getTraveledDistance();
    d = rightCodewheel.getTraveledDistance();
    Serial.print("LEFT: ");
    Serial.print(a);
    Serial.print(" ");
    Serial.print(b);
    Serial.print(" | RIGHT ");
    Serial.print(c);
    Serial.print(" ");
    Serial.println(d);

    wb_loop();
}
