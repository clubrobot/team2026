#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <Actionneurs.h>
#include <My_Clock.h>
#include <variables_globales.h>

#include "wheeledbase/wb_thread.h"
#include "actionneurs/actio_thread.h"
#include "decisions/Automate.h"

#define TEST_NO_FREERTOS true //Ignore le FreeRTOS et se comporte comme un arduino classique

void setup(){
    DWT_Init(); //Très important
    //Setup de base
    Serial.begin(9600);

    wb_setup();
    actio_setup();
    Automate::init(TEAM_JAUNE);//TODO: team

    if(TEST_NO_FREERTOS) {
        return;
    }
    //Setup FreeRTOS

    TaskHandle_t  hl_wb = NULL;
    BaseType_t ret_wb = xTaskCreate(
                wb_loop,       /* Function that implements the task. */
                "Wheeledbase loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                NULL,    /* Parameter passed into the task. */
                6,//Prio max
                &hl_wb );      /* Used to pass out the created task's handle. */

    if(ret_wb!=pdPASS) {Error_Handler()}

    TaskHandle_t  hl_actio = NULL;
    BaseType_t ret_actio = xTaskCreate(
                actio_loop,       /* Function that implements the task. */
                "Actionneur loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                NULL,    /* Parameter passed into the task. */
                2,//Prio nulle à chier
                &hl_actio );      /* Used to pass out the created task's handle. */

    if(ret_actio!=pdPASS) {Error_Handler()}

    TaskHandle_t  hl_robot = NULL;
    BaseType_t ret_robot = xTaskCreate(
                Automate::play_match,       /* Function that implements the task. */
                "Actionneur loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                NULL,    /* Parameter passed into the task. */
                4,//Prio un peu mieux
                &hl_robot );      /* Used to pass out the created task's handle. */

    if(ret_robot!=pdPASS) {Error_Handler()}

    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    Error_Handler(); //TODO: logger l'error handler
}



long a,b;
float c,d, e;
Position *pos;
void loop() {
    //loop seuleuement accesssible quand TEST_NO_FREERTOS est à true
    a = leftCodewheel.getCounter();
    b = rightCodewheel.getCounter();
    c = leftCodewheel.getTraveledDistance();
    d = rightCodewheel.getTraveledDistance();
    leftWheel.setVelocity(100);
    rightWheel.setVelocity(100);
}
