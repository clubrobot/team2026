#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <Actionneurs.h>
#include <My_Clock.h>
#include <variables_globales.h>

#include "wheeledbase/wb_thread.h"
#include "actionneurs/actio_thread.h"
#include "decisions/Automate.h"

#define TEST_NO_FREERTOS false //Ignore le FreeRTOS et se comporte comme un arduino classique
void test_loop( void* paraam);
//HardwareSerial Serial6(PC7, PC6);
AX12 test;
void setup(){
    DWT_Init(); //Très important
    //Setup de base
    Serial.begin(115200);

    wb_setup();
    actio_setup();
    Automate::init(TEAM_JAUNE);//TODO: team

    Wheeledbase::PRINT_PARAMS();
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PE1, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

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
                4,//Prio max
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
                "Actionneur loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                NULL,    /* Parameter passed into the task. */
                4,//Prio un peu mieux
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

    test = AX12();
    test.attach(254);
    test.setID(1);
    test.attach(1);
    test.turn(200);
    //Wheeledbase::ADD_PUREPURSUIT_WAYPOINT(100,0);
    for(;;) {
        //Wheeledbase::START_PUREPURSUIT(0, 0);
        Serial.println(test.readPosition());
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
