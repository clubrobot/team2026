//
// Created by bapti on 04/02/2025.
//

#include "TacheEmpiler.h"


void TacheEmpiler::execute() {
    listeActionneur::ascenseur.turn(200);

    listeActionneur::pince_droite.move(limite_pince_droite.limite_basse);
}