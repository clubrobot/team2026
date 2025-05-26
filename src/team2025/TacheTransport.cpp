//
// Created by boris on 5/26/25.
//

#include "TacheTransport.h"
#include "ListeActionneurs.h"

using namespace listeActionneur;


bool TacheTransport::execute(bool previous_success){
    asc_down();
    grab_conserve();
    aimante_conserve();
    return true;
}