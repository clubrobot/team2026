#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>
#include <Clock.h>

#include "wheeledbase/wb_thread.h"


#define TEST_NO_FREERTOS true //Ignore le FreeRTOS et se comporte comme un arduino classique

void setup(){
    DWT_Init(); //Très important
    //Setup de base
    Serial.begin(9600);

    wb_setup();
    if(TEST_NO_FREERTOS) {
        return;
    }
    //Setup FreeRTOS

    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    Error_Handler(); //TODO: logger l'error handler
}
long a,b;
float c,d, e;

void loop() {
    //loop seuleuement accesssible quand TEST_NO_FREERTOS est à true

    a = leftCodewheel.getCounter();
    b = rightCodewheel.getCounter();
    c = leftCodewheel.getTraveledDistance();
    d = rightCodewheel.getTraveledDistance();

    Wheeledbase::GET_POSITION(&c, &d, &e);
    Serial.print(c);
    Serial.print(" ");
    Serial.print(d);
    Serial.print(" ");
    Serial.println(e);
    /*Serial.print(a);
    Serial.print(" ");
    Serial.print(c);
    Serial.print(" ");
    Serial.print(b);
    Serial.print(" ");
    Serial.println(d);*/
    wb_loop();
}
