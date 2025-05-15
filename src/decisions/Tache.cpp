#include "Tache.h"

#include <Wheeledbase.h>
#include "sensors/sensors_thread.h"
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
    if (_pos_begin==nullptr){

        pos_begin.x = Wheeledbase::GET_POSITION()->x;
        pos_begin.y =Wheeledbase::GET_POSITION()->y;
        pos_begin.theta =Wheeledbase::GET_POSITION()->theta;
    }
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
    if (_pos_approach==nullptr){
        pos_begin.x =0;
        pos_begin.y =0;
        pos_begin.theta =0;
    }
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
    if (pos_approach.x != 0){
        //Calculation approche
        /*if (Position::compare(&pos_approach,&pos_end)){
            Position diff;
            diff.x = pos_begin.x - pos_approach.x;
            diff.y = pos_begin.y - pos_approach.y;
            float length = sqrt(pow(diff.x,2)+pow(diff.y,2));
            pos_approach.x = diff.x/length*(length-radius) + pos_end.x;
            pos_approach.y = diff.y/length*(length-radius) + pos_end.y;
            float ang = acos(diff.x/length);
            if (diff.y<0) ang *=-1;
        }*/
        Wheeledbase::GOTO(&pos_end, arriere, pos_end.theta);

    }else{
        Wheeledbase::GOTO(&pos_end, arriere, pos_end.theta);
    }

}

void TacheMoveDelta::setDelta(float vel, uint32_t temps){
    _vel =vel;
    _temps =temps;
}

void TacheMoveDelta::execute(){
    portENTER_CRITICAL();

        Wheeledbase::SET_VELOCITIES(_vel, 0);
        poly_delay(_temps);
    for (int i=0; i<255; i++)    Wheeledbase::SET_VELOCITIES(0, 0);
    portEXIT_CRITICAL();


}

void TacheSTOP::execute(){
    for (;;){
        Wheeledbase::SET_VELOCITIES(0,0);
    }


}