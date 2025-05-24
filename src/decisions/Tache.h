
#ifndef TEAM2025_TACHE_H
#define TEAM2025_TACHE_H
#include <Odometry.h>
#include <PurePursuit.h>


class Tache {
protected:
    int necessary_time;
    int max_score;

public:
    const int get_necessary_time();
    const int get_max_score();
    virtual bool execute(bool previous_success);//code de la tâche
    virtual ~Tache() {}
    void set_max_score(int score);
    void set_necessary_time(int _necessary_time);

};

class TacheGoto: public Tache{
    bool execute(bool previous_success) override;
protected:
    Position* _pos_approach;
    Position* _pos_end;
public:
    int arriere =PurePursuit::NONE;
    TacheGoto(Position* pos_approach, Position* pos_end, int marche_arriere=PurePursuit::NONE){
        set_max_score(0);
        set_necessary_time(0);
        _pos_approach = pos_approach;
        _pos_end = pos_end;
        arriere=marche_arriere;
    }
};

class TacheGotoWithFunct: public TacheGoto{
    bool execute(bool previous_succes) override;
    void* _duringFunct;
    void* _approachFunct;
public:
    TacheGotoWithFunct(Position* pos_approach, Position* pos_end, void* duringFunct, void* approachFunct,int marche_arriere=PurePursuit::NONE) : TacheGoto(pos_approach, pos_end, marche_arriere){
        set_max_score(0);
        set_necessary_time(0);
        _duringFunct = duringFunct;
        _approachFunct = approachFunct;
    }
};

class TacheMoveDelta: public Tache{
    bool execute(bool previous_success) override;
    float _dx, _dy;
public:
    TacheMoveDelta(float dx, float dy){
        set_max_score(0);
        set_necessary_time(0);
        _dx=dx;
        _dy=dy;
    }
};

class TacheSwitch: public Tache{
    bool execute(bool previous_success) override;
    Tache succ_tache,fail_tache;
public:
    TacheSwitch(Tache success,Tache fail): succ_tache(success), fail_tache(fail){
        set_max_score(0);
        set_necessary_time(0);
    }
};

class TacheSTOP: public Tache{
    bool execute(bool previous_success) override;

public:
    TacheSTOP(){
        set_max_score(0);
        set_necessary_time(0);
    }
};



#endif
