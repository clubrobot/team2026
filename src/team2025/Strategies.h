//
// Created by boris on 5/26/25.
//

#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "../decisions/Tache.h"
#include "TacheBanderole.h"
#include "TacheEmpiler.h"
#include "TacheTransport.h"

namespace Strategies{
    extern int nb_taches;
    extern Position* start;
    extern Tache* strat[100];

    void strat1(int team);
    void stratDeBase(int team);
    void stratHomo(int team);
}


#endif //STRATEGIES_H
