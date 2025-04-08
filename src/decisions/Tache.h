
#ifndef TEAM2025_TACHE_H
#define TEAM2025_TACHE_H
#include <Odometry.h>


class Tache {
protected:
    int necessary_time;
    int max_score;
    int speed_approach;
    int speed_goto;
    Position pos_begin;
    Position pos_approach;
    Position pos_end;
public:
    const int get_necessary_time();
    const int get_max_score();
    virtual void execute() = 0;//code de la tâche
    virtual ~Tache() {}
    const Position* get_begin();
    const Position* get_approach();
    const Position* get_end();
    void set_max_score(int score);
    void set_necessary_time(int _necessary_time);
    void set_speed_approach(int speed);
    void set_speed_goto(int speed);
    void set_begin(Position* _pos_begin);
    void set_begin(float x, float y, float theta);
    void set_approach(Position* _pos_approach);
    void set_approach(float x, float y, float theta);
    void set_end(Position* _pos_end);
    void set_end(float x, float y, float theta);
};
//Todo: function move for each tache
class TacheGoto: public Tache{
    void execute() override;
public:
    TacheGoto(Position* _pos_begin, Position* _pos_approach, Position* _pos_end){
        set_max_score(0);
        set_necessary_time(0);
        set_begin(_pos_begin);
        set_approach(_pos_approach);
        set_end(_pos_end);
    }
};


#endif
