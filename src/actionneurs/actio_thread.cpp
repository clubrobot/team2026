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

void actio_loop() {
    current_actio.type_actio = NULL;
    xQueueReceive(actio_queue, &current_actio, portMAX_DELAY);

    switch (current_actio.type_actio) {
        case AX12:
            break;
        case SERVO:
            break;
        case MOTEUR:
            break;
        default:
            //Nothing to do
            break;
    }
}
