
#ifndef TEAM2025_TACHE_H
#define TEAM2025_TACHE_H


class Tache {
private:
    int necessary_time;
    int max_score;
    int pos_begin_x,pos_begin_y;
    int pos_end_x,pos_end_y;
public:
    const int get_necessary_time();
    const int get_max_score();
    virtual void execute()=0;//code de la tâche
    const int get_begin_x();
    const int get_begin_y();
    const int get_end_x();
    const int get_end_y();
};

#endif
