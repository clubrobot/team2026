//
// Created by boris on 01/12/2024.
//

#include "actio_thread.h"
#include "actio_const.h"

void actio_setup() {
    actio_queue =  xQueueCreate(ACTIO_QUEUE_SIZE, sizeof(actio_type));

    if(actio_queue == NULL) {
        //Uh oh
    }

    vQueueAddToRegistry(actio_queue, "Queue actionneur");

}

void actio_loop(void *pvParameters) {
    //On attend de recevoir qqchose
    current_actio.opcode = NULL;
    xQueueReceive(actio_queue, &current_actio, portMAX_DELAY);

    //On traite la demande
    switch (current_actio.opcode) {
    case MONTE_ESCALATOR:
            Actionneur2025::monte_elevateur(current_actio.param_tab);
            break;
        default:
            //Nothing to do
            break;
    }
}
