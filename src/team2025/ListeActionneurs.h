//
// Created by boris on 08/04/2025.
//

#ifndef LISTEACTIONNEURS_H
#define LISTEACTIONNEURS_H

#include "AX12.h"
#include "ServosPCA9685.h"

#define AX12_ASCENSEUR_ID 1
#define AX12_PINCE_DROITE_ID 2
#define AX12_PINCE_GAUCHE_ID 3

#define SERVO_PINCE_DROITE_ID 1
#define SERVO_PINCE_GAUCHE_ID 2
#define SERVO_PINCE_MILIEU_DROIT_ID 3
#define SERVO_PINCE_MILIEU_GAUCHE_ID 4

typedef struct{
    uint8_t limite_basse;
    uint8_t action_1;
    uint8_t action_2;
    uint8_t limite_haute;
}limites_actionneurs;


limites_actionneurs limite_pince_droite;
limites_actionneurs limite_pince_gauche;
limites_actionneurs limite_servo_pince_droite;
limites_actionneurs limite_servo_pince_gauche;
limites_actionneurs limite_servo_pince_milieu_droit;
limites_actionneurs limite_servo_pince_milieu_gauche;

namespace listeActionneur {
    void Init();

    extern AX12 ascenseur;
    extern AX12 pince_droite;
    extern AX12 pince_gauche;
    extern uint8_t servo_pince_droite;
    extern uint8_t servo_pince_gauche;
    extern uint8_t servo_pince_milieu_droit;
    extern uint8_t servo_pince_milieu_gauche;
} // listeActionneur

#endif //LISTEACTIONNEURS_H
