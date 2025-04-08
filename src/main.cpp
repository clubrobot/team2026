#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <My_Clock.h>
#include <PrintfSupport.h>
#include <variables_globales.h>
#include <Logger.h>
#include <Musique.h>

#include "wheeledbase/wb_thread.h"
#include "decisions/Automate.h"

#include "team2025/ListeActionneurs.h"

#define DEBUG 1
#define TEST_NO_FREERTOS false //Ignore le FreeRTOS et se comporte comme un arduino classique

Logger main_logs = Logger("MAIN");

//Setup de base
void setup(){
    DWT_Init(); //Très important

    if(DEBUG) {
        PrintfSupport::begin(PRINTF_BAUD);
        main_logs.log(INFO_LEVEL, "Debug enabled at %d baud\n", PRINTF_BAUD);
        main_logs.log(INFO_LEVEL, "Printing WheeledBase Params\n");
        Wheeledbase::PRINT_PARAMS();
    }

    Musique myBeeper = Musique(PA6, 2);
    //myBeeper.playSheetMusic(nokia);

    wb_setup();
    listeActionneur::Init();
    Automate::init(TEAM_JAUNE);//TODO: team

    if(TEST_NO_FREERTOS) {
        main_logs.log(WARNING_LEVEL,"Not using FreeRTOS\n");
        return;
    }
    main_logs.log(GOOD_LEVEL,"Using FreeRTOS\n");
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
    //             sensors,       /* Function that implements the task. */
    //             "Sensors loop",          /* Text name for the task. */
    //             10000,      /* Stack size in words, not bytes. */
    //             NULL,    /* Parameter passed into the task. */
    //             2,//Prio nulle à chier
    //             &hl_actio );      /* Used to pass out the created task's handle. */
    //
    // if(ret_actio!=pdPASS) {Error_Handler()}

    TaskHandle_t  hl_robot = nullptr;

    BaseType_t ret_robot = xTaskCreate(
                Automate::play_match,       /* Function that implements the task. */
                "Robot loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                nullptr,    /* Parameter passed into the task. */
                5,//Prio un peu mieux
                &hl_robot );      /* Used to pass out the created task's handle. */

    if(ret_robot!=pdPASS) {Error_Handler()}

    main_logs.log(GOOD_LEVEL,"Starting tasks\n");
    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    main_logs.log(ERROR_LEVEL,"Not good\n");
    Error_Handler();
}

void loop() {

}
