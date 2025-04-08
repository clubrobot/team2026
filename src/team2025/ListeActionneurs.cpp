//
// Created by boris on 08/04/2025.
//

#include "ListeActionneurs.h"

namespace listeActionneur {
    AX12 ascenseur;
}

void listeActionneur::Init(){
    AX12::SerialBegin(AX12_BAUDRATE);

    ascenseur.attach(AX12_ASCENSEUR_ID);
}

