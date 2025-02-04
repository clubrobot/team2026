//
// Created by boris on 01/12/2024.
//

#include "actio_thread.h"
#include "actio_const.h"

QueueHandle_t actio_queue;
actio_type current_actio;

void actio_setup() {
    AX12::SerialBegin(AX12_BAUDRATE);

    actio_queue =  xQueueCreate(ACTIO_QUEUE_SIZE, sizeof(actio_type));

    if(actio_queue == NULL) {
        //Uh oh
    }

    vQueueAddToRegistry(actio_queue, "Queue actionneur");

}

void actio_loop(void *pvParameters) {
    return;
    //On attend de recevoir qqchose
    current_actio.opcode = NULL;
    xQueueReceive(actio_queue, &current_actio, portMAX_DELAY);

    //On traite la demande
    switch (current_actio.opcode) {
        case MONTE_ESCALATOR:

            break;
        default:
            //Nothing to do
            break;
    }
}
