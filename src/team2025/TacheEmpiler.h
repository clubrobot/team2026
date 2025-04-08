//
// Created by bapti on 04/02/2025.
//

#ifndef TEAM2025_TACHEEMPILER_H
#define TEAM2025_TACHEEMPILER_H

#include "decisions/Tache.h"
#include "ListeActionneurs.h"

class TacheEmpiler: public Tache{
    void execute() override;
public:
    TacheEmpiler(){
        set_max_score(911);
    }
};


#endif //TEAM2025_TACHEEMPILER_H
