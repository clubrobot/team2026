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

    void pincePresqueOuvert();
}



void listeActionneur::Init(){
    poly_delay(100);
    AX12::SerialBegin(AX12_BAUDRATE);
    poly_delay(100);
    ServosPCA9685::Init();

    ascenseur.attach(AX12_ASCENSEUR_ID);
    ascenseur.setEndlessMode(true);
    banderole.attach(AX12_BANDEROLE_ID);
    banderole.setEndlessMode(false);
    pince_droite.attach(AX12_PINCE_DROITE_ID);
    pince_gauche.attach(AX12_PINCE_GAUCHE_ID);


    limite_pince_droite.ouvert = 219;  //ouvert
    limite_pince_droite.ferme = 130; //fermé
    limite_pince_droite.compact = 69; //complétement fermé

    limite_pince_gauche.ouvert = 151; // ouvert
    limite_pince_gauche.ferme = 238; // fermé
    limite_pince_gauche.presque_ferme = 230;
    limite_pince_gauche.compact = 298; // complétement fermé

    ////////////PINCE
    limite_servo_pince_droite.ferme = 67;
    limite_servo_pince_droite.presque_ferme = 90;///FERME
    limite_servo_pince_droite.ouvert = 120; //OUVERT
    limite_servo_pince_droite.grand_ouvert = 180; //GRAND OUVERT

    limite_servo_pince_gauche.ferme = 170; ///FERME
    limite_servo_pince_gauche.presque_ferme = 140; ///FERME
    limite_servo_pince_gauche.ouvert = 110; ///OUVERT
    limite_servo_pince_gauche.grand_ouvert = 50; ///GRAND OUVERT

    ////////////AIMANTs
    limite_servo_pince_aimant_droit.ferme= 92; ///FERME OK
    limite_servo_pince_aimant_droit.ferme= 87; ///FERME OK
    limite_servo_pince_aimant_droit.ouvert= 75; ///OUVERT OK

    limite_servo_pince_aimant_gauche.ferme = 177; ///FERME
    limite_servo_pince_aimant_gauche.ferme = 182; ///FERME
    limite_servo_pince_aimant_gauche.ouvert = 200; ///OUVERT


    /////BANDEROLE
    limite_banderole.non_deploye = 126; //En haut
    limite_banderole.deploye = 53; // En bas

    limite_servo_banderole.non_deploye = 39; //SERRRE
    limite_servo_banderole.deploye = 180; //OUVERT
    //INIT
    haut_banderole();
    poly_delay(50);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_droit, limite_servo_pince_aimant_droit.ferme);
    poly_delay(50);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_gauche, limite_servo_pince_aimant_gauche.ferme);
    poly_delay(50);
    pince_compact();
    poly_delay(1000);


    asc_down();
    asc_mid();

    pinMode(POMPE_PIN, OUTPUT);

    return;



}

void listeActionneur::doNothing(){
    return;
}

void listeActionneur::pince_accueil(){
    papFerme();
    pinceGrandOuvert();
}


void listeActionneur::asc_down(){
    while (!ihm::etat_lim_bas()){
        ascenseur.turn(-1023);
    }
    ascenseur.turn(0);
}

void listeActionneur::asc_mid(){
    if (ihm::etat_lim_haut() || !ihm::etat_lim_bas())return;
    ascenseur.turn(1023);
    poly_delay(600);
    ascenseur.turn(0);
}

void listeActionneur::asc_set_mid(){
    asc_down();
    asc_mid();
}


void listeActionneur::asc_secoue(){
    if (ihm::etat_lim_bas())return;
    for (int i=0; i<1; i++){
        ascenseur.turn(-1023);
        poly_delay(700);
        ascenseur.turn(0);
        poly_delay(10);
    }
}

void listeActionneur::asc_up(){

    while (!ihm::etat_lim_haut()){
        ascenseur.turn(1023);
    }
    ascenseur.turn(0);
}

void listeActionneur::aimante_conserve(){
    //portENTER_CRITICAL();
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_droit, limite_servo_pince_aimant_droit.ferme);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_gauche, limite_servo_pince_aimant_gauche.ferme);
    
}

void listeActionneur::stop_aimant_conserve(){
    //portENTER_CRITICAL();
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_droit, limite_servo_pince_aimant_droit.ouvert);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_gauche, limite_servo_pince_aimant_gauche.ouvert);
    
}

void listeActionneur::pince_pour_deplacer(){
    papOuvert();
    pinceFerme();
}

void listeActionneur::grab_conserve(){
    pinceOuvert();
    poly_delay(300);
    papFerme();
    poly_delay(300);
    pinceFerme();
    poly_delay(300);
    papOuvert();
}

void listeActionneur::drop_conserve(){
    papFerme();
    poly_delay(300);
    pincePresqueFerme();
    poly_delay(300);
    asc_secoue();
    poly_delay(100);
    pinceOuvert();
    poly_delay(300);
    papOuvert();
    poly_delay(300);
    pinceFerme();
}


void listeActionneur::deploie_banderole(){
    banderole.move(limite_banderole.deploye);
    poly_delay(500);
    //portENTER_CRITICAL();
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
    poly_delay(50);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.ouvert);
    poly_delay(50);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.ouvert);
    
    poly_delay(50);
    pince_gauche.move(limite_pince_gauche.compact);
    poly_delay(50);
    pince_droite.move(limite_pince_droite.compact, true);
}

void listeActionneur::papOuvert(){
    pince_gauche.moveSpeed(limite_pince_gauche.ouvert, 1023);
    poly_delay(5);
    pince_droite.moveSpeed(limite_pince_droite.ouvert, 1023,true);
}

void listeActionneur::papFerme(){
    pince_gauche.moveSpeed(limite_pince_gauche.ferme, 300);
    poly_delay(10);
    pince_droite.moveSpeed(limite_pince_droite.ferme, 300,true);
}

void listeActionneur::pinceGrandOuvert(){
    //portENTER_CRITICAL();
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.grand_ouvert);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.grand_ouvert);
    
}


void listeActionneur::pinceOuvert(){
    //portENTER_CRITICAL();
    poly_delay(25);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.ouvert);
    poly_delay(25);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.ouvert);
    
}
void listeActionneur::pincePresqueFerme(){
    //portENTER_CRITICAL();
    poly_delay(25);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.presque_ferme);
    poly_delay(25);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.presque_ferme);

}
void listeActionneur::pinceFerme(){
    //portENTER_CRITICAL();
    poly_delay(25);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.ferme);
    poly_delay(25);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.ferme);
    
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