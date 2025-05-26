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
    limite_pince_gauche.compact = 298; // complétement fermé

    ////////////PINCE
    limite_servo_pince_droite.ferme = 75; ///FERME
    limite_servo_pince_droite.ouvert = 120; //OUVERT
    limite_servo_pince_droite.grand_ouvert = 180; //GRAND OUVERT

    limite_servo_pince_gauche.ferme = 155; ///FERME
    limite_servo_pince_gauche.ouvert = 110; ///OUVERT
    limite_servo_pince_gauche.grand_ouvert = 50; ///GRAND OUVERT

    ////////////AIMANTs
    limite_servo_pince_aimant_droit.ferme= 90; ///FERME OK
    limite_servo_pince_aimant_droit.ouvert= 75; ///OUVERT OK

    limite_servo_pince_aimant_gauche.ferme = 180; ///FERME
    limite_servo_pince_aimant_gauche.ouvert = 200; ///OUVERT


    /////BANDEROLE
    limite_banderole.non_deploye = 218; //En haut
    limite_banderole.deploye = 159; // En bas

    limite_servo_banderole.non_deploye = 39; //SERRRE
    limite_servo_banderole.deploye = 180; //OUVERT


    //INIT
    haut_banderole();
    poly_delay(20);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_droit, limite_servo_pince_aimant_droit.ferme);
    poly_delay(20);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_gauche, limite_servo_pince_aimant_gauche.ferme);
    poly_delay(20);
    //pince_compact();
    poly_delay(1000);
    asc_down();
    asc_mid();
    pinMode(POMPE_PIN, OUTPUT);

    return;
    poly_delay(1000);
    pince_pour_deplacer();
    poly_delay(1000);
    grab_conserve();
    poly_delay(5000);
    drop_conserve();
    for (;;){}
    poly_delay(1000);
    papOuvert();
    pinceOuvert();
    while (!ihm::etat_vert()){}
    asc_down();
    poly_delay(100);
    papFerme();
    poly_delay(200);
    pinceFerme();
    poly_delay(1000);
    papOuvert();
    poly_delay(100);
    //set_pompe(HIGH);
    poly_delay(100);
    asc_up();
    poly_delay(100);
    papFerme();
    poly_delay(500);
    pinceOuvert();
    poly_delay(1000);
    papOuvert();
    poly_delay(100);
    //set_pompe(LOW);


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

void listeActionneur::asc_up(){
    while (!ihm::etat_lim_haut()){
        ascenseur.turn(1023);
    }
    ascenseur.turn(0);
}

void listeActionneur::aimante_conserve(){
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_droit, limite_servo_pince_aimant_droit.ferme);
    ServosPCA9685::Write(listeActionneur::servo_pince_aimant_gauche, limite_servo_pince_aimant_gauche.ferme);
}

void listeActionneur::stop_aimant_conserve(){
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
    pinceOuvert();
    poly_delay(300);
    papOuvert();
    poly_delay(300);
    pinceFerme();
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
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.ouvert);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.ouvert);
    poly_delay(10);
    pince_gauche.move(limite_pince_gauche.compact, true);
    poly_delay(10);
    pince_droite.move(limite_pince_droite.compact, true);
}

void listeActionneur::papOuvert(){
    pince_gauche.moveSpeed(limite_pince_gauche.ouvert, 1023);
    poly_delay(10);
    pince_droite.moveSpeed(limite_pince_droite.ouvert, 1023,true);
}

void listeActionneur::papFerme(){
    pince_gauche.moveSpeed(limite_pince_gauche.ferme, 300);
    poly_delay(10);
    pince_droite.moveSpeed(limite_pince_droite.ferme, 300,true);
}

void listeActionneur::pinceGrandOuvert(){
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.grand_ouvert);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.grand_ouvert);
}


void listeActionneur::pinceOuvert(){
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.ouvert);
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_gauche, limite_servo_pince_gauche.ouvert);
}
void listeActionneur::pinceFerme(){
    poly_delay(5);
    ServosPCA9685::Write(listeActionneur::servo_pince_droite, limite_servo_pince_droite.ferme);
    poly_delay(5);
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