//
// Created by bapti on 04/02/2025.
//

#include "TacheEmpiler.h"


void TacheEmpiler::execute() {
    listeActionneur::ouvre_milieu();
    poly_delay(500);
    listeActionneur::papillion_ouvert();
    listeActionneur::ouvre_centre();
    poly_delay(500);
    listeActionneur::ferme_centre();
    ihm::set_pompe(HIGH);
    listeActionneur::descend();
    poly_delay(500);
    listeActionneur::pince_droite.move(limite_pince_droite.action_1);
    listeActionneur::pince_gauche.move(limite_pince_gauche.action_1);

    listeActionneur::ferme_milieu();
    poly_delay(1000);
    listeActionneur::monte_un_peu_plus();
    poly_delay(500);
    listeActionneur::papillion_ouvert();
    poly_delay(500);
    listeActionneur::monte();
    poly_delay(50);
    listeActionneur::papillion_ferme();
    ihm::set_pompe(LOW);
    poly_delay(500);
    listeActionneur::ouvre_tout();
    poly_delay(500);
    listeActionneur::papillion_ouvert();
}