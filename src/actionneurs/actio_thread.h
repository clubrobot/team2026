//
// Created by boris on 01/12/2024.
//

#ifndef ACTIO_THREAD_H
#define ACTIO_THREAD_H

#include <STM32FreeRTOS.h>


/**
* Actionneur  queue:
1- Type actionneur
2- Fonction de l'actionneur à déclencher
3- pointeur val retour
4- nb param
5- tab pointeurs param

*/

/**
 * Exemple AX12:
 * AX12 monAX12; (ptet extern à voir)
 *
 * actio_type exAX12 = {
 *  AX12,
 *  attach,
 *  NULL,
 *  2,
 *  monAX12,
 *  3
 * }
*/
typedef struct {
    uint16_t type_actio;        //Soit AX12, SERVO, MOTEUR
    TaskFunction_t func_actio;
    void* ret_func_actio;
    uint16_t nb_param;
    void* param_tab;
}actio_type;

QueueHandle_t actio_queue;
actio_type current_actio;


void actio_setup();
void actio_loop();


#endif //ACTIO_THREAD_H
