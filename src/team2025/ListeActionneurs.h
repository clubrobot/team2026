//
// Created by boris on 08/04/2025.
//

#ifndef LISTEACTIONNEURS_H
#define LISTEACTIONNEURS_H

#include "AX12.h"
#include "ServosPCA9685.h"
#include "ihm/ihm.h"

#define AX12_ASCENSEUR_ID 2 //OK
#define AX12_PINCE_DROITE_ID 1 //OK
#define AX12_PINCE_GAUCHE_ID 3 //OK

#define SERVO_PINCE_DROITE_ID 15
#define SERVO_PINCE_GAUCHE_ID 2
#define SERVO_PINCE_MILIEU_DROIT_ID 1
#define SERVO_PINCE_MILIEU_GAUCHE_ID 0

typedef struct{
    float limite_basse;
    float action_1;
    float action_2;
    float limite_haute;
}limites_actionneurs;


inline limites_actionneurs limite_pince_droite;
inline limites_actionneurs limite_pince_gauche;
inline limites_actionneurs limite_ascenseur;
inline limites_actionneurs limite_servo_pince_droite;
inline limites_actionneurs limite_servo_pince_gauche;
inline limites_actionneurs limite_servo_pince_milieu_droit;
inline limites_actionneurs limite_servo_pince_milieu_gauche;

namespace listeActionneur {
    void Init();
    void ferme_milieu();
    void ouvre_milieu();
    void ferme_centre();
    void ouvre_centre();
    void ferme_tout();
    void ouvre_tout();

    void monte();
    void monte_un_peu();
    void monte_un_peu_plus();
    void descend();

    void papillion_ouvert();
    void papillion_ferme();

    extern AX12 ascenseur;
    extern AX12 pince_droite;
    extern AX12 pince_gauche;
    extern uint8_t servo_pince_droite;
    extern uint8_t servo_pince_gauche;
    extern uint8_t servo_pince_milieu_droit;
    extern uint8_t servo_pince_milieu_gauche;
} // listeActionneur

#endif //LISTEACTIONNEURS_H
