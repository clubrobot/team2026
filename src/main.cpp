#include <Arduino.h>
#include <STM32FreeRTOS.h>

#include "wb_thread.h"
/**
 * DESCRIPTION DES TÂCHES:
 * wb_thread: s'occuppe de tout ce qui est base roulante: odométrie et velocityControl
 * sensors_thread: s'occupe de récup les données de la cam et du lidar périodiquement
 *
 */

#define TEST_NO_FREERTOS true //Ignore le FreeRTOS et se comporte comme un arduino classique

void setup(){
    //Setup de base
    Serial.begin(9600);
    //wb_setup();//Setup de la base roulante dans wb_thread
    if(TEST_NO_FREERTOS) return;
    //Setup FreeRTOS

    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    Error_Handler(); //TODO: logger l'error handler
}

void loop() {
    //loop seuleuement accesssible quand TEST_NO_FREERTOS est à true
}
