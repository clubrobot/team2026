#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <Actionneurs.h>
#include <My_Clock.h>
#include <PrintfSupport.h>
#include <variables_globales.h>
#include <Musique.h>

#include "wheeledbase/wb_thread.h"
#include "actionneurs/actio_thread.h"
#include "decisions/Automate.h"


#define DEBUG 1
#define TEST_NO_FREERTOS false //Ignore le FreeRTOS et se comporte comme un arduino classique

#undef Error_Handler
#define Error_Handler() \
while (1) {\
    printf("ERREUR dans %s:%d \n", __FILE__, __LINE__);\
}//TODO: visual or beeper

void test_loop( void* paraam);

//Setup de base
void setup(){
    DWT_Init(); //Très important

    if(DEBUG) {
        PrintfSupport::begin(PRINTF_BAUD);
        printf("[INIT] Debug enabled at %d baud\n", PRINTF_BAUD);
    }

    Musique myBeeper = Musique(PA6, 10);
    myBeeper.playSheetMusic(nokia);

    wb_setup();
    actio_setup();
    Automate::init(TEAM_JAUNE);//TODO: team

    Wheeledbase::PRINT_PARAMS();
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PE1, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    if(TEST_NO_FREERTOS) {
        printf("[INIT] Not using FreeRTOS\n");
        return;
    }
    printf("[INIT] Using FreeRTOS\n");
    //Setup FreeRTOS

    TaskHandle_t  hl_wb = nullptr;
    BaseType_t ret_wb = xTaskCreate(
                wb_loop,       /* Function that implements the task. */
                "Wheeledbase loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                nullptr,    /* Parameter passed into the task. */
                5,//Prio max
                &hl_wb );      /* Used to pass out the created task's handle. */

    if(ret_wb!=pdPASS) {Error_Handler()}

    // TaskHandle_t  hl_actio = NULL;
    // BaseType_t ret_actio = xTaskCreate(
    //             actio_loop,       /* Function that implements the task. */
    //             "Actionneur loop",          /* Text name for the task. */
    //             10000,      /* Stack size in words, not bytes. */
    //             NULL,    /* Parameter passed into the task. */
    //             2,//Prio nulle à chier
    //             &hl_actio );      /* Used to pass out the created task's handle. */
    //
    // if(ret_actio!=pdPASS) {Error_Handler()}

    TaskHandle_t  hl_robot = nullptr;
    BaseType_t ret_robot = xTaskCreate(
                test_loop,       /* Function that implements the task. */
                "Robot loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                nullptr,    /* Parameter passed into the task. */
                5,//Prio un peu mieux
                &hl_robot );      /* Used to pass out the created task's handle. */

    if(ret_robot!=pdPASS) {Error_Handler()}

    Serial.println("Start");
    vTaskStartScheduler();//On commence FreeRTOS
    Serial.println("Not good");
    //On devrait pas être là; Uh oh
    Error_Handler(); //TODO: logger l'error handler
}

Position pos1 = Position(400,0,0);
Position pos2 = Position(0,0,0);
Position pos3 = Position(0,0,0);

void test_loop( void* paraam) {
    digitalWrite(PE1, HIGH);
    //Wheeledbase::START_TURNONTHESPOT(false, 3.14);
    //vTaskDelay(pdMS_TO_TICKS(10000));
    printf("Back to it again\n");
    for(;;) {
        Wheeledbase::GOTO_DELTA(400,0);
        while(Wheeledbase::POSITION_REACHED()!=0b01) {  }
        vTaskDelay(pdMS_TO_TICKS(2000));
        Wheeledbase::START_TURNONTHESPOT(0,-1.57);
        while(Wheeledbase::POSITION_REACHED()!=0b01) { }
        vTaskDelay(pdMS_TO_TICKS(2000));
        Wheeledbase::START_TURNONTHESPOT(0,0);
        while(Wheeledbase::POSITION_REACHED()!=0b01) { }
        vTaskDelay(pdMS_TO_TICKS(2000));
        Wheeledbase::GOTO_DELTA(-400,0);
        while(Wheeledbase::POSITION_REACHED()!=0b01) { }
        vTaskDelay(pdMS_TO_TICKS(2000));
      /* printf("debut 1\n");
        Wheeledbase::GOTO(&pos1, 0, 0);

        vTaskDelay(pdMS_TO_TICKS(1000));

        Wheeledbase::GOTO(&pos2, 0, 0);*/

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}


void loop() {
    //loop seuleuement accesssible quand TEST_NO_FREERTOS est à true



    //Wheeledbase::SET_OPENLOOP_VELOCITIES(100,0);
}
