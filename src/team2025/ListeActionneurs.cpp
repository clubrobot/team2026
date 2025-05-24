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
    banderole.setEndlessMode(false);
    pince_droite.attach(AX12_PINCE_DROITE_ID);
    pince_gauche.attach(AX12_PINCE_GAUCHE_ID);


    limite_pince_droite.deploye = 219;  //ouvert
    limite_pince_droite.mi_non_deploye = 130; //fermé
    limite_pince_droite.non_deploye = 69; //complétement fermé

    limite_pince_gauche.deploye = 151; // ouvert
    limite_pince_gauche.mi_non_deploye = 238; // fermé
    limite_pince_gauche.non_deploye = 298; // complétement fermé

    ////////////PINCE
    limite_servo_pince_droite.non_deploye = 75; ///FERME
    limite_servo_pince_droite.deploye = 120; //OUVERT

    limite_servo_pince_gauche.non_deploye = 155; ///FERME
    limite_servo_pince_gauche.deploye = 110; ///OUVERT

    ////////////AIMANTs
    limite_servo_pince_aimant_droit.non_deploye = 90; ///FERME OK
    limite_servo_pince_aimant_droit.deploye = 75; ///OUVERT OK

    limite_servo_pince_aimant_gauche.non_deploye = 180; ///FERME
    limite_servo_pince_aimant_gauche.deploye = 200; ///OUVERT


    /////BANDEROLE
    limite_banderole.non_deploye = 218; //En haut
    limite_banderole.deploye = 159; // En bas

    limite_servo_banderole.non_deploye = 39; //SERRRE
    limite_servo_banderole.deploye = 180; //OUVERT


    //INIT
    haut_banderole();
    poly_delay(20);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_droit, limite_servo_pince_aimant_droit.non_deploye);
    poly_delay(20);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_gauche, limite_servo_pince_aimant_gauche.non_deploye);
    poly_delay(20);
    pince_compact();
    asc_up();
    pinMode(POMPE_PIN, OUTPUT);
/*
    papOuvert();
    pinceOuvert();
    poly_delay(1000);
    papFerme();
    poly_delay(500);
    pinceFerme();*/

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

void listeActionneur::deploie_banderole(){
    banderole.move(limite_banderole.deploye);
    poly_delay(300);
    ServosPCA9685::Write(servo_banderole, limite_servo_banderole.deploye);
}
void listeActionneur::haut_banderole(){
    banderole.move(limite_banderole.non_deploye);
    ServosPCA9685::Write(servo_banderole, limite_servo_banderole.non_deploye);
}
void listeActionneur::mise_banderole(){
    banderole.move(limite_banderole.non_deploye);
    ServosPCA9685::Write(servo_banderole, limite_servo_banderole.deploye);
}

void listeActionneur::pince_compact(){
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.deploye);
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.deploye);
    poly_delay(5);
    pince_gauche.move(limite_pince_gauche.non_deploye);
    poly_delay(5);
    pince_droite.move(limite_pince_droite.non_deploye);
}

void listeActionneur::papOuvert(){
    poly_delay(10);
    pince_gauche.move(limite_pince_gauche.deploye);
    poly_delay(10);
    pince_droite.move(limite_pince_droite.deploye);
}

void listeActionneur::papFerme(){
    poly_delay(10);
    pince_gauche.move(limite_pince_gauche.mi_non_deploye);
    poly_delay(10);
    pince_droite.move(limite_pince_droite.mi_non_deploye);
}

void listeActionneur::pinceOuvert(){
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.deploye);
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.deploye);
}
void listeActionneur::pinceFerme(){
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.non_deploye);
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.non_deploye);
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