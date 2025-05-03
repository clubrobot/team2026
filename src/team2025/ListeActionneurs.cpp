//
// Created by boris on 08/04/2025.
//

#include "ListeActionneurs.h"

namespace listeActionneur {
    AX12 ascenseur;
    AX12 pince_droite;
    AX12 pince_gauche;
    uint8_t servo_pince_droite=SERVO_PINCE_DROITE_ID;
    uint8_t servo_pince_gauche=SERVO_PINCE_GAUCHE_ID;
    uint8_t servo_pince_milieu_droit=SERVO_PINCE_MILIEU_DROIT_ID;
    uint8_t servo_pince_milieu_gauche=SERVO_PINCE_MILIEU_GAUCHE_ID;
}



void listeActionneur::Init(){
    AX12::SerialBegin(AX12_BAUDRATE);
    ServosPCA9685::Init();

    ascenseur.attach(AX12_ASCENSEUR_ID);
    pince_droite.attach(AX12_PINCE_DROITE_ID);
    pince_gauche.attach(AX12_PINCE_GAUCHE_ID);

    limite_pince_droite.limite_basse = 140; //ouvert
    limite_pince_droite.limite_haute = 80; //fermé

    limite_pince_gauche.limite_basse = 150; // ouvert
    limite_pince_gauche.limite_haute = 193; // fermé

    limite_ascenseur.limite_haute = 6;//6sec montée
    limite_ascenseur.limite_basse = 5.3;//

    limite_servo_pince_droite.action_1 = 80; ///FERME
    limite_servo_pince_droite.action_2 = 150; //OUVERT
    limite_servo_pince_gauche.action_1 = 167; ///FERME
    limite_servo_pince_gauche.action_2 = 100; ///FERME
    limite_servo_pince_milieu_droit.action_1 = 70; ///FERME
    limite_servo_pince_milieu_droit.action_2 = 150; ///OUVERT
    limite_servo_pince_milieu_gauche.action_1 = 165; ///FERME
    limite_servo_pince_milieu_gauche.action_2 = 100; ///FERME
}

void listeActionneur::ouvre_centre(){
    ServosPCA9685::Write(servo_pince_milieu_droit, limite_servo_pince_milieu_droit.action_2);
    ServosPCA9685::Write(servo_pince_milieu_gauche, limite_servo_pince_milieu_gauche.action_2);
}

void listeActionneur::ferme_centre(){
    ServosPCA9685::Write(servo_pince_milieu_droit, limite_servo_pince_milieu_droit.action_1);
    ServosPCA9685::Write(servo_pince_milieu_gauche, limite_servo_pince_milieu_gauche.action_1);
}

void listeActionneur::ouvre_milieu(){
    ServosPCA9685::Write(servo_pince_droite, limite_servo_pince_droite.action_2);
    ServosPCA9685::Write(servo_pince_gauche, limite_servo_pince_gauche.action_2);
}

void listeActionneur::ferme_milieu(){
    ServosPCA9685::Write(servo_pince_droite, limite_servo_pince_droite.action_1);
    ServosPCA9685::Write(servo_pince_gauche, limite_servo_pince_gauche.action_1);
}

void listeActionneur::ouvre_tout(){
    ouvre_milieu();
    ouvre_centre();
}


void listeActionneur::ferme_tout(){
    ferme_centre();
    ferme_milieu();
}

void listeActionneur::monte(){
    listeActionneur::ascenseur.turn(1023);
    delay(limite_ascenseur.limite_haute);
}

void listeActionneur::descend(){
    listeActionneur::ascenseur.turn(-1023);
    while (ihm::etat_lim_bas()){

    }
    listeActionneur::ascenseur.turn(0);
}

void listeActionneur::papillion_ferme(){
    listeActionneur::pince_droite.move(limite_pince_droite.limite_haute);
    listeActionneur::pince_gauche.move(limite_pince_gauche.limite_haute);
}

void listeActionneur::papillion_ouvert(){
    listeActionneur::pince_droite.move(limite_pince_droite.limite_basse);
    listeActionneur::pince_gauche.move(limite_pince_gauche.limite_basse);
}

