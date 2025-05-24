//
// Created by boris on 5/15/25.
//

#ifndef TACHEBANDEROLE_H
#define TACHEBANDEROLE_H

#include "decisions/Tache.h"

class TacheBanderole: public Tache{
    bool execute(bool previous_success) override;
public:
    TacheBanderole(){
        set_max_score(6969);
    }
};



#endif //TACHEBANDEROLE_H
