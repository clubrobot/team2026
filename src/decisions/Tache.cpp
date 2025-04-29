#include "Tache.h"

#include <Wheeledbase.h>

const int Tache::get_max_score() {
    return max_score;
}
void Tache::set_max_score(int score) {
    max_score=score;
}
void Tache::set_speed_approach(int speed) {
    speed_approach = speed;
}

void Tache::set_speed_goto(int speed) {
    speed_goto = speed;
}

const int Tache::get_necessary_time(){
    return necessary_time;
}
void Tache::set_necessary_time(int _necessary_time){
    necessary_time = _necessary_time;
}
const Position* Tache::get_begin() {
    return &pos_begin;
}
const Position* Tache::get_approach() {
    return &pos_approach;
}
const Position* Tache::get_end() {
    return  &pos_end;
}

void Tache::set_begin(Position* _pos_begin) {
    pos_begin.x = _pos_begin->x;
    pos_begin.y = _pos_begin->y;
    pos_begin.theta = _pos_begin->theta;
}

void Tache::set_begin(float x, float y, float theta) {
    pos_begin.x = x;
    pos_begin.y = y;
    pos_begin.theta = theta;
}

void Tache::set_approach(Position* _pos_approach) {
    pos_approach.x = _pos_approach->x;
    pos_approach.y = _pos_approach->y;
    pos_approach.theta = _pos_approach->theta;
}

void Tache::set_approach(float x, float y, float theta) {
    pos_approach.x = x;
    pos_approach.y = y;
    pos_approach.theta = theta;
}
void Tache::set_end(Position* _pos_end) {
    pos_end.x = _pos_end->x;
    pos_end.y = _pos_end->y;
    pos_end.theta = _pos_end->theta;
}
void Tache::set_end(float x, float y, float theta) {
    pos_end.x = x;
    pos_end.y = y;
    pos_end.theta = theta;
}

void TacheGoto::execute() {
    int old_speed = Wheeledbase::GET_PARAMETER_VALUE(LINVELPID_MAXOUTPUT_ID);
    Wheeledbase::SET_PARAMETER_VALUE(LINVELPID_MAXOUTPUT_ID, old_speed*0.5);
    Wheeledbase::GOTO(&pos_approach, PurePursuit::FORWARD, pos_approach.theta);
    Wheeledbase::SET_PARAMETER_VALUE(LINVELPID_MAXOUTPUT_ID, old_speed);
    Wheeledbase::GOTO(&pos_end, PurePursuit::FORWARD, pos_end.theta);
}
