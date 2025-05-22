//
// Created by boris on 08/04/2025.
//

#ifndef LISTEACTIONNEURS_H
#define LISTEACTIONNEURS_H

#include "AX12.h"
#include "ServosPCA9685.h"
#include "ihm/ihm.h"

#define AX12_ASCENSEUR_ID 2 //OK
#define AX12_BANDEROLE_ID 4 //OK
#define AX12_PINCE_DROITE_ID 1 //OK
#define AX12_PINCE_GAUCHE_ID 3 //OK

#define SERVO_PINCE_DROITE_ID 11 //OK
#define SERVO_PINCE_GAUCHE_ID 12 //OK
#define SERVO_PINCE_MILIEU_DROIT_ID 3 //OK
#define SERVO_PINCE_MILIEU_GAUCHE_ID 7 //OK
#define SERVO_BANDEROLE_ID 15 //OK

#define POMPE_PIN PF9

typedef struct{
    float non_deploye;
    float mi_non_deploye;
    float mi_deploye;
    float deploye;
}limites_actionneurs;


inline limites_actionneurs limite_ascenseur;

inline limites_actionneurs limite_banderole;

inline limites_actionneurs limite_pince_droite;
inline limites_actionneurs limite_pince_gauche;

inline limites_actionneurs limite_servo_banderole;
inline limites_actionneurs limite_servo_pince_droite;
inline limites_actionneurs limite_servo_pince_gauche;
inline limites_actionneurs limite_servo_pince_aimant_droit;
inline limites_actionneurs limite_servo_pince_aimant_gauche;

namespace listeActionneur {
    void Init();

    void asc_down();
    void asc_up();
    void deploie_banderole();
    void haut_banderole();
    void mise_banderole();
    void set_pompe(bool state);

    extern AX12 ascenseur;
    extern AX12 pince_droite;
    extern AX12 pince_gauche;
    extern AX12 banderole;

    extern uint8_t servo_banderole;
    extern uint8_t servo_pince_droite;
    extern uint8_t servo_pince_gauche;
    extern uint8_t servo_pince_aimant_droit;
    extern uint8_t servo_pince_aimant_gauche;
} // listeActionneur

#endif //LISTEACTIONNEURS_H
