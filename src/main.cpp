#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <My_Clock.h>
#include <PrintfSupport.h>
#include <variables_globales.h>
#include <Logger.h>
#include <Musique.h>

#include "ihm/ihm.h"
#include "wheeledbase/wb_thread.h"
#include "decisions/Automate.h"

#include "team2025/ListeActionneurs.h"

#define DEBUG 1
#define TEST_NO_FREERTOS true //Ignore le FreeRTOS et se comporte comme un arduino classique

Logger main_logs = Logger("MAIN");

void procedure_demarrage(){
    main_logs.log(INFO_LEVEL, "Sélectionez une équipe\n");
    ihm::led_jaune(HIGH);
    ihm::led_bleu(HIGH);
    while (1){
        if (!ihm::etat_jaune()){
            main_logs.log(GOOD_LEVEL,"Equipe Jaune !\n");
            ihm::led_bleu(LOW);
            Automate::init(TEAM_JAUNE);
            break;
        }
        if (!ihm::etat_bleu()){
            main_logs.log(GOOD_LEVEL,"Equipe Bleu!\n");
            ihm::led_jaune(LOW);
            Automate::init(TEAM_BLEU);
            break;
        }
    }

    main_logs.log(INFO_LEVEL,"Veuillez mettre le robot en place et appuyer sur vert\n");
    while (ihm::etat_vert()){
        int prev = millis();
        if (millis() - prev > 100){
            prev = millis();
            ihm::led_vert();
        }
    };
    ihm::led_vert(LOW);
    main_logs.log(WARNING_LEVEL,"Le robot est armé!\n");
}

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
    main_logs.log(GOOD_LEVEL,"Wheeledbase & Actionneurs initied\n");
    procedure_demarrage();

    //listeActionneur::ascenseur.setEndlessMode(true);
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
 //listeActionneur::ascenseur.turn(1023);

}
