#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <Actionneurs.h>
#include <My_Clock.h>
#include <PrintfSupport.h>
#include <variables_globales.h>

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

    TaskHandle_t  hl_wb = NULL;
    BaseType_t ret_wb = xTaskCreate(
                wb_loop,       /* Function that implements the task. */
                "Wheeledbase loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                NULL,    /* Parameter passed into the task. */
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

    TaskHandle_t  hl_robot = NULL;
    BaseType_t ret_robot = xTaskCreate(
                test_loop,       /* Function that implements the task. */
                "Robot loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                NULL,    /* Parameter passed into the task. */
                5,//Prio un peu mieux
                &hl_robot );      /* Used to pass out the created task's handle. */

    if(ret_robot!=pdPASS) {Error_Handler()}

    Serial.println("Start");
    vTaskStartScheduler();//On commence FreeRTOS
    Serial.println("Not good");
    //On devrait pas être là; Uh oh
    Error_Handler(); //TODO: logger l'error handler
}

long a,b;
float c,d, e;
int aa = 0;
const Position *pos;

void test_loop( void* paraam) {
    //Serial.begin(115200);
    digitalWrite(PE1, HIGH);

    for(;;) {
        //purePursuit.reset();
        //positionControl.disable();
        //Wheeledbase::SET_VELOCITIES(100,0);
        Position pos=Position(0,300,0);
        Wheeledbase::GOTO(&pos, purePursuit.FORWARD, 0);
        printf("Goto finished\n");
        pos.x = 300;
        Wheeledbase::GOTO(&pos, purePursuit.FORWARD, 0);
        vTaskDelay(pdMS_TO_TICKS(10000));
        printf("Back to it again\n");

        /*a = leftCodewheel.getCounter();
        b = rightCodewheel.getCounter();
        pos = Wheeledbase::GET_POSITION();
        Wheeledbase::GET_VELOCITIES(&c, &d);
        Serial.print(a);
        Serial.print(" ");
        Serial.print(b);
        Serial.print(" ");
        Serial.print(c);
        Serial.print(" ");
        Serial.print(d);
        Serial.print(" ");
        Serial.print(pos->x);
        Serial.print(" ");
        Serial.println(pos->y);
        Serial.flush();*/
    }

}


void loop() {
    //loop seuleuement accesssible quand TEST_NO_FREERTOS est à true

    //wb_loop(nullptr);


    //Wheeledbase::SET_OPENLOOP_VELOCITIES(100,0);
}
