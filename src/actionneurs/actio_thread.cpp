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
        case SERVO:
            break;
        case MOTEUR:
            break;
        default:
            //Nothing to do
            break;
    }
}
//permet d'envoyer une commande pour faire tourner le moteur id jusqu'à l'angle angle_final
void tourner_moteur(uint16_t id,float angle_final){
    //test que la queue existe
    if( actio_queue != 0 ) {
        actio_type msg;
        msg.type_actio=MOTEUR;
        msg.angle=angle_final;
        msg.id_actionneur=id;
        xQueueSend( actio_queue,( void * ) &msg,( TickType_t ) 10 );
    }
}
//permet d'envoyer une commande pour faire tourner le servo-moteur id jusqu'à l'angle angle_final
void tourner_servo(int id,float angle_final){
    if( actio_queue != 0 ) {
        actio_type msg;
        msg.type_actio=SERVO;
        msg.angle=angle_final;
        msg.id_actionneur=id;
        xQueueSend( actio_queue,( void * ) &msg,( TickType_t ) 10 );
    }
}
