#include <Arduino.h>
#include <list>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <My_Clock.h>
#include <PrintfSupport.h>
#include <variables_globales.h>
#include <Logger.h>
#include <Musique.h>
#include <Teleplot.h>
#include <team2025/TacheBanderole.h>

#include "ihm/ihm.h"
#include "wheeledbase/wb_thread.h"
#include "sensors/SensorsThread.h"
#include "decisions/Automate.h"
#include "include/SensorArray.h"

#include "team2025/ListeActionneurs.h"

#define DEBUG 1
#define TEST_NO_FREERTOS false //Ignore le FreeRTOS et se comporte comme un arduino classique

#define SENSORARRAY_STOP_DISTANCE 250

Logger main_logs = Logger("MAIN");
using namespace ihm;
void procedure_demarrage(){
    main_logs.log(INFO_LEVEL, "Mise à zero des actionneurs\n");
    //TODO

    main_logs.log(INFO_LEVEL, "Sélectionez une équipe\n");
    led_jaune(HIGH);
    led_bleu(HIGH);
    while (true){
        if (etat_jaune()){
            main_logs.log(GOOD_LEVEL,"Equipe Jaune !\n");
            led_bleu(LOW);
            Automate::init(TEAM_JAUNE);
            break;
        }
        if (etat_bleu()){
            main_logs.log(GOOD_LEVEL,"Equipe Bleu!\n");
            led_jaune(LOW);
            Automate::init(TEAM_BLEU);
            break;
        }
    }

    main_logs.log(INFO_LEVEL,"Veuillez mettre le robot en place et appuyer sur vert; rouge pour mettre la banderole!\n");

    unsigned int prev_vert = millis();
    unsigned int prev_rouge = millis();

    while (!etat_vert()){
        unsigned int curr_time = millis();
        if (curr_time-prev_vert > 500){
            prev_vert = curr_time;
            led_vert();
        }
        if(curr_time-prev_rouge>100){
            prev_rouge = curr_time;
            led_rouge();
        }

        if(etat_rouge()){
            listeActionneur::mise_banderole();
        }else{
            listeActionneur::haut_banderole();
        }
    }
    led_vert(LOW);
    main_logs.log(WARNING_LEVEL,"Le robot est armé!\n");

    //Detect tirette
    while(etat_tirette()==1){}
    main_logs.log(WARNING_LEVEL,"tirette mise (dans le trou de Boris) !\n");
    while (etat_tirette()==0){}
    main_logs.log(WARNING_LEVEL,"tirette enlevée (du trou de Boris) !\n");

}


/**
TODO:
Valeurs servo limites  OK
Régler PID/Accel => Logger OK
Procédure démarrage Preque OK
Tache empiler
Tache banderole OK
check reset if vl53 are flshed !!!!!!!!!!!!!!
*/

#define YEUX_TX PG1
HardwareSerial yeux(YEUX_TX);

//Setup de base
void setup(){
    DWT_Init(); //Très important

#if DEBUG
    PrintfSupport::begin(PRINTF_BAUD);
    main_logs.log(WARNING_LEVEL, "Debug enabled at %d baud\n", PRINTF_BAUD);
    //main_logs.log(INFO_LEVEL, "Printing WheeledBase Params\n");
    //Wheeledbase::PRINT_PARAMS();
#endif
    //Musique myBeeper = Musique(PA6, 10);
    //myBeeper.playSheetMusic(cantina);


    listeActionneur::Init();
    //SensorsThread::Init();
    wb_setup();

    yeux.setTx(YEUX_TX);
    yeux.setHalfDuplex();
    yeux.begin(115200);

    main_logs.log(GOOD_LEVEL,"Wheeledbase & Actionneurs & Sensors & IHM initied\n");
    //procedure_demarrage();
    //listeActionneur::ascenseur.setEndlessMode(true);

#if TEST_NO_FREERTOS
    main_logs.log(WARNING_LEVEL,"Not using FreeRTOS\n");
    return;
#endif
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

    // TaskHandle_t  hl_sens = nullptr;
    // BaseType_t ret_sens= xTaskCreate(
    //             SensorsThread::Thread,       /* Function that implements the task. */
    //             "Sensors loop",          /* Text name for thedi task. */
    //             10000,      /* Stack size in words, not bytes. */
    //             nullptr,    /* Parameter passed into the task. */
    //             5,//Prio nulle à chier
    //             &hl_sens );      /* Used to pass out the created task's handle. */

    // if(ret_sens!=pdPASS) {Error_Handler()}

    TaskHandle_t  hl_robot = nullptr;

    BaseType_t ret_robot = xTaskCreate(
                Automate::play_match,       /* Function that implements the task. */
                "Robot loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                (void *) procedure_demarrage,    /* Parameter passed into the task. */
                5,//Prio un peu mieux
                &hl_robot );      /* Used to pass out the created task's handle. */

    if(ret_robot!=pdPASS) {Error_Handler()}

    TaskHandle_t  hl_yeux= nullptr;

    //BaseType_t ret_yeux = xTaskCreate(
    //        wb_loop,       /* Function that implements the task. */
    //        "UwU",          /* Text name for the task. */
    //        10000,      /* Stack size in words, not bytes. */
    //        NULL,    /* Parameter passed into the task. */
    //        5,//Prio un peu mieux
    //        &hl_yeux );      /* Used to pass out the created task's handle. */

    //if(ret_yeux!=pdPASS) {Error_Handler()}

    main_logs.log(GOOD_LEVEL,"Starting tasks\n");
    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    main_logs.log(ERROR_LEVEL,"FreeRTOS crashed\n");
    Error_Handler();
}
float i=0;
void loop(){
    return;
    i=i+0.01;
    teleplot.add_variable_float_2decimal("sin", sin(i));
    if (i>=2*PI) i=0;
    //printf("Pince Droite %f\tPince Gauche %f\t Banderole %f\t\n", listeActionneur::pince_droite.readPosition(), listeActionneur::pince_gauche.readPosition(), listeActionneur::banderole.readPosition());
}
