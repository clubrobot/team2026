//
// Created by boris on 08/04/2025.
//

#ifndef LISTEACTIONNEURS_H
#define LISTEACTIONNEURS_H

#include "AX12.h"
#include "ServosPCA9685.h"

#define AX12_ASCENSEUR_ID 1
#define SERVO_PINCE_DROITE_ID 2
#define SERVO_PINCE_GAUCHE_ID 3
#define SERVO_PINCE_MDROITE_ID 4
#define SERVO_PINCE_MGAUCHE_ID 5

namespace listeActionneur {
    void Init();

    extern AX12 ascenseur;
} // listeActionneur

#endif //LISTEACTIONNEURS_H
