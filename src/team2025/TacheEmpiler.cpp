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
    float defaultMaxSpeed = Wheeledbase::GET_PARAMETER_VALUE(POSITIONCONTROL_LINVELMAX_ID);
    float defaltAcc = Wheeledbase::GET_PARAMETER_VALUE(VELOCITYCONTROL_MAXLINACC_ID);
    Wheeledbase::SET_PARAMETER_VALUE(VELOCITYCONTROL_MAXLINACC_ID, defaltAcc*0.2);
    Wheeledbase::SET_PARAMETER_VALUE(POSITIONCONTROL_LINVELMAX_ID, defaultMaxSpeed*0.2);
    Wheeledbase::GOTO_DELTA(-300,0);
    Wheeledbase::SET_PARAMETER_VALUE(POSITIONCONTROL_LINVELMAX_ID, defaultMaxSpeed);
    Wheeledbase::SET_PARAMETER_VALUE(VELOCITYCONTROL_MAXLINACC_ID, defaltAcc);
    aimante_conserve();
    asc_down();
    asc_mid();
    return true;
}