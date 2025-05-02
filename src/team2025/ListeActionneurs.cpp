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

    ascenseur.attach(AX12_ASCENSEUR_ID);
    pince_droite.attach(AX12_PINCE_DROITE_ID);
    pince_gauche.attach(AX12_PINCE_GAUCHE_ID);

    limite_pince_droite.limite_basse = 140; //ouvert
    limite_pince_droite.limite_haute = 80; //fermé

    limite_pince_gauche.limite_basse = 150; // ouvert
    limite_pince_gauche.limite_haute = 193; // fermé

    limite_ascenseur.limite_haute = 6;//6sec montée
    limite_ascenseur.limite_basse = 5.3;//
}

