//
// Created by boris on 5/26/25.
//

#include "Strategies.h"
#include <variables_globales.h>
#include "Geogebra.h"

namespace Strategies{
    int nb_taches=0;
    Position* start;
    Tache* strat[100];

    void strat1(int team);

}

void Strategies::strat1(int team){
    if (team==TEAM_JAUNE){
        ////////////////////// STRAT 1 JAUNE ///////////////////
        positions_match=positions_jaune;
        start = &positions_match[start2];
        nb_taches=5;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheGoto((Position*)nullptr, nullptr, PurePursuit::FORWARD);
        strat[2] = new TacheTransport();
        strat[3] = new TacheGoto((Position*)nullptr, nullptr, PurePursuit::FORWARD);
        strat[4] = new TacheEmpiler();
    }else{
        ////////////////////// STRAT 1 BLEU ///////////////////
        positions_match=positions_bleu;
        start = &positions_match[start2];
        nb_taches=5;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheGoto((Position*)nullptr, nullptr, PurePursuit::FORWARD);
        strat[2] = new TacheTransport();
        strat[3] = new TacheGoto((Position*)nullptr, nullptr, PurePursuit::FORWARD);
        strat[4] = new TacheEmpiler();
    }
}

