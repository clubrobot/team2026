//
// Created by bapti on 04/02/2025.
//

#include "TacheBanderole.h"
#include "ListeActionneurs.h"

using namespace listeActionneur;

bool TacheBanderole::execute(bool success) {
    deploie_banderole();
    return true;
}