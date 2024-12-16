//
// Created by boris on 01/12/2024.
//

#ifndef ACTIO_THREAD_H
#define ACTIO_THREAD_H

#include <STM32FreeRTOS.h>
#include <Actionneurs.h>

/**
* Actionneur  queue:
1- OPCODE
2- Tableau de param
3- pointeur val retour
*/

/**
 * Exemple:
 * int params[] = {500};
 * actio_type exAX12 = {
 *  PIMP_MON_ROBOT,
 *  (void*) params,
 *  NULL
 * }
*/
typedef struct {
    uint16_t opcode;        //Opcode de l'action
    void* ret_func_actio;
    void* param_tab;
}actio_type;

QueueHandle_t actio_queue;
actio_type current_actio;


void actio_setup();
void actio_loop(void *pvParameters);


#endif //ACTIO_THREAD_H
