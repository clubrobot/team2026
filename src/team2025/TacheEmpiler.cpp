//
// Created by bapti on 04/02/2025.
//

#include "TacheEmpiler.h"

#include <Wheeledbase.h>

#include "ListeActionneurs.h"

using namespace listeActionneur;


bool TacheEmpiler::execute(bool previous_success){
    asc_down();
    poly_delay(50);
    set_pompe(HIGH);
    asc_up();
    poly_delay(50);
    drop_conserve();
    set_pompe(LOW);
    stop_aimant_conserve();
    Wheeledbase::GOTO_DELTA(-100,0);
    aimante_conserve();
    asc_down();
    asc_mid();
    return true;
}