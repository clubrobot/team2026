#include "Tache.h"

#include <Wheeledbase.h>
#include "sensors/SensorsThread.h"


long start_millis;

const int Tache::get_max_score() {
    return max_score;
}
void Tache::set_max_score(int score) {
    max_score=score;
}

const int Tache::get_necessary_time(){
    return necessary_time;
}
void Tache::set_necessary_time(int _necessary_time){
    necessary_time = _necessary_time;
}

bool Tache::execute(bool succ){
    return false;
}


bool TacheGoto::execute(bool previous_success) {
    Wheeledbase::GOTO(_pos_end, _appr, arriere, _pos_end->theta);
    return true;
}

bool TacheTurnOnTheSpot::execute(bool previous_success){
    Wheeledbase::START_TURNONTHESPOT_DIR(_dir, _theta);
}


bool TacheGotoWithFunct::execute(bool previous_success) {
    Wheeledbase::GOTO_FUNCT(_pos_end, _duringFunct, _approachFunct,true, arriere, _pos_end->theta);
    return true;
}

bool TacheGotoWaypoints::execute(bool previous_success){
    Wheeledbase::GOTO_WAYPOINTS_ARRAY(_posistions, _appr, arriere, _nb_waypoints);
    return true;
}

bool TacheMoveDelta::execute(bool previous_success){
    Wheeledbase::GOTO_DELTA(_dx, _dy);
    return true;
}

bool TacheExe::execute(bool previous_success){
    _funct();
    return true;
}


bool TacheWait::execute(bool previous_success){
    while (millis()-*_start_val<=_waitTime){

    }
    return true;
}


bool TacheSTOP::execute(bool previous_success){
    Wheeledbase::SET_VELOCITIES(0,0);
    return true;
}

bool TacheSwitch::execute(bool previous_success){
   if(previous_success){
       return succ_tache.execute(previous_success);
   }else{
       return fail_tache.execute(previous_success);
   }

    return true;
}