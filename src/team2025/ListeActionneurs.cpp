//
// Created by boris on 08/04/2025.
//

#include "ListeActionneurs.h"

#include <My_Clock.h>

namespace listeActionneur {
    AX12 ascenseur;
    AX12 banderole;
    AX12 pince_droite;
    AX12 pince_gauche;
    uint8_t servo_banderole=SERVO_BANDEROLE_ID;
    uint8_t servo_pince_droite=SERVO_PINCE_DROITE_ID;
    uint8_t servo_pince_gauche=SERVO_PINCE_GAUCHE_ID;
    uint8_t servo_pince_aimant_droit=SERVO_PINCE_MILIEU_DROIT_ID;
    uint8_t servo_pince_aimant_gauche=SERVO_PINCE_MILIEU_GAUCHE_ID;
}



void listeActionneur::Init(){
    AX12::SerialBegin(AX12_BAUDRATE);
    ServosPCA9685::Init();

    ascenseur.attach(AX12_ASCENSEUR_ID);
    banderole.attach(AX12_BANDEROLE_ID);
    pince_droite.attach(AX12_PINCE_DROITE_ID);
    pince_gauche.attach(AX12_PINCE_GAUCHE_ID);

    limite_pince_droite.deploye = 219;  //ouvert
    limite_pince_droite.mi_non_deploye = 130; //fermé
    limite_pince_droite.non_deploye = 69; //complétement fermé

    limite_pince_gauche.deploye = 151; // ouvert
    limite_pince_gauche.mi_non_deploye = 238; // fermé
    limite_pince_gauche.non_deploye = 298; // complétement fermé

    limite_ascenseur.deploye = 6.5;//6sec montée
    limite_ascenseur.non_deploye = 1;//
    limite_ascenseur.mi_non_deploye = 1.5;//

    limite_servo_pince_droite.non_deploye = 80; ///FERME
    limite_servo_pince_droite.deploye = 150; //OUVERT

    limite_servo_pince_gauche.non_deploye = 205; ///FERME OK
    limite_servo_pince_gauche.deploye = 180; ///OUVERT OK

    //ServosPCA9685::Write(listeActionneur::servo_pince_aimant_droit, 0);
    limite_servo_pince_aimant_droit.non_deploye = 60; ///FERME
    limite_servo_pince_aimant_droit.deploye = 150; ///OUVERT

    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_gauche, 180);
    limite_servo_pince_aimant_gauche.non_deploye = 180; ///FERME
    limite_servo_pince_aimant_gauche.deploye = 190; ///OUVERT

    pinMode(POMPE_PIN, OUTPUT);

}

void listeActionneur::asc_down(){
    while (!ihm::etat_lim_bas()){
        ascenseur.turn(-1023);
    }
    ascenseur.turn(0);
}

void listeActionneur::asc_up(){
    while (!ihm::etat_lim_haut()){
        ascenseur.turn(1023);
    }
    ascenseur.turn(0);
}

void listeActionneur::set_pompe(bool state){
    if (state==HIGH){
        portENTER_CRITICAL();
        for (int i=0; i<1023; i++){
            analogWrite(POMPE_PIN, i);
            poly_delay(1);
        }
        portEXIT_CRITICAL();
    }else{
        analogWrite(POMPE_PIN, 0);
    }
}