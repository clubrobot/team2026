//
// Created by bapti on 04/02/2025.
//

#ifndef TEAM2025_TACHEEMPILER_H
#define TEAM2025_TACHEEMPILER_H

#include "decisions/Tache.h"

class TacheEmpiler: public Tache{
    float recul;
    bool execute(bool previous_success) override;
public:
    TacheEmpiler(float r):recul(r){
        set_max_score(8);
    }
    TacheEmpiler():recul(-1){
        set_max_score(8);
    }
};


#endif //TEAM2025_TACHEEMPILER_H
