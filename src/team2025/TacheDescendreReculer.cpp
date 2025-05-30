//
// Created by bapti on 30/05/2025.
//

#include "TacheDescendreReculer.h"
#include "ListeActionneurs.h"

using namespace listeActionneur;
bool TacheDescendreReculer::execute(bool previous_success){
    listeActionneur::recul_ascenseur_mid(recul,recul_debut);
    return true;
}