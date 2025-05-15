//
// Created by bapti on 04/02/2025.
//

#include "TacheEmpiler.h"
#include "ListeActionneurs.h"

using namespace listeActionneur;

void TacheEmpiler::execute() {
    ouvre_milieu();
    poly_delay(500);
    papillion_ouvert();
    ouvre_centre();
    poly_delay(500);
    ferme_centre();
    set_pompe(HIGH);
    descend();
    poly_delay(500);
    pince_droite.move(limite_pince_droite.action_1);
    pince_gauche.move(limite_pince_gauche.action_1);

    ferme_milieu();
    poly_delay(1000);
    monte_un_peu_plus();
    poly_delay(500);
    papillion_ouvert();
    poly_delay(500);
    monte();
    poly_delay(50);
    papillion_ferme();
    set_pompe(LOW);
    poly_delay(500);
    ouvre_tout();
    poly_delay(500);
    papillion_ouvert();
}