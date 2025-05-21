//
// Created by bapti on 04/02/2025.
//

#ifndef TEAM2025_TACHEEMPILER_H
#define TEAM2025_TACHEEMPILER_H

#include "decisions/Tache.h"

class TacheEmpiler: public Tache{
    bool execute(bool previous_success) override;
public:
    TacheEmpiler(){
        set_max_score(911);
    }
};


#endif //TEAM2025_TACHEEMPILER_H
