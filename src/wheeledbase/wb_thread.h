/**
 * @file wb_thread.h
 * @ingroup wheeledbase
 * @ingroup core
 * @brief Contient les fonctions et variables nécessaires pour gérer le thread de base roulante
 */

#ifndef WB_THREAD_H
#define WB_THREAD_H
#include "Wheeledbase.h"
#include "wb_const.h"
#include "STM32HALTimer.h"

/**
 * @defgroup codewheel_hardware_timers
 * @ingroup wheeledbase
 * @ingroup core
 * @ingroup globals
 * @{
 */
extern TIM_HandleTypeDef htim23;//Right
extern TIM_HandleTypeDef htim24;//Left
///@}

/**
 * Créé et initialise la base roulante
 * @return La Base roulante
 */
Wheeledbase::WheeledBase wb_setup();

/**
 * Boucle principale de la tâche FreeRTOS
 * @param pvParameters Les paramètres de la tâche tels que demandé par les tâches FreeRTOS
 */
[[noreturn]] void wb_loop(void *pvParameters);

#endif //WB_THREAD_H
