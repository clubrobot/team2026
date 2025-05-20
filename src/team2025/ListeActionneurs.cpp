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
    uint8_t servo_pince_milieu_droit=SERVO_PINCE_MILIEU_DROIT_ID;
    uint8_t servo_pince_milieu_gauche=SERVO_PINCE_MILIEU_GAUCHE_ID;
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

    limite_servo_pince_gauche.non_deploye = 167; ///FERME
    limite_servo_pince_gauche.deploye = 100; ///OUVERT

    limite_servo_pince_milieu_droit.non_deploye = 70; ///FERME
    limite_servo_pince_milieu_droit.deploye = 150; ///OUVERT

    limite_servo_pince_milieu_gauche.non_deploye = 165; ///FERME
    limite_servo_pince_milieu_gauche.deploye = 100; ///OUVERT

    pinMode(POMPE_PIN, OUTPUT);

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