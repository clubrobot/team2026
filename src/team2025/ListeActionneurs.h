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
    float ouvert;
    float ferme;
    float entre_deux;
    float compact;
    float grand_ouvert;
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
    void doNothing();
    void asc_down();///Ascensceur en bas
    void asc_mid();///Ascenseur qui monte 1sec depuis le bas
    void asc_up();///Ascenseur en haut

    void aimante_conserve();///Les 2 servos avant aimantes les conserves
    void stop_aimant_conserve();///Les 2 servos avant aimantes plus les conserves

    void pince_pour_deplacer();

    void deploie_banderole();
    void haut_banderole();
    void mise_banderole();
    void set_pompe(bool state);

    void grab_conserve();
    void drop_conserve();

    void pince_compact();
    void papOuvert();
    void papFerme();
    void pinceGrandOuvert();
    void pinceOuvert();
    void pinceFerme();

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
