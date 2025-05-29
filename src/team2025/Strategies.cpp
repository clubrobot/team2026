//
// Created by boris on 5/26/25.
//

#include "Strategies.h"
#include <variables_globales.h>
#include "Geogebra.h"
#include "ListeActionneurs.h"

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
        nb_taches=10;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheGoto((Position*)nullptr, &positions_match[garage4all], PurePursuit::FORWARD);
        strat[2] = new TacheTransport();
        strat[3] = new TacheGoto((Position*)nullptr, &positions_match[depot3], PurePursuit::FORWARD);
        strat[4] = new TacheEmpiler();
        strat[5] = new TacheGoto(nullptr, &positions_match[check1], PurePursuit::BACKWARD, false);
        strat[6] = new TacheGoto(nullptr, &positions_match[garage8all], PurePursuit::FORWARD);
        strat[7] = new TacheTransport();
        strat[8] = new TacheGoto(nullptr, &positions_match[depot2], PurePursuit::FORWARD, false);
        strat[9] = new TacheEmpiler();

        //FIN MATCH
        strat[10] = new TacheGoto(nullptr, &positions_match[chgsta1], PurePursuit::FORWARD, false);
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

void Strategies::stratDeBase(int team){
    if (team==TEAM_JAUNE){
        ////////////////////// STRAT 1 JAUNE ///////////////////
        positions_match=positions_jaune;
        start = &positions_match[start2];
        nb_taches=9;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheExe((void*)listeActionneur::pince_pour_deplacer);
        strat[2] = new TacheGoto((Position*)nullptr, &positions_match[garage4all], PurePursuit::FORWARD);
        strat[3] = new TacheTransport();
        strat[4] = new TacheGoto((Position*)nullptr, &positions_match[depot3], PurePursuit::FORWARD, false);
        strat[5] = new TacheEmpiler();
        //FIN MATCH
        strat[6] = new TacheGoto((Position*)nullptr, &positions_match[check3], PurePursuit::FORWARD, false);
        strat[7] = new TacheWait(&start_millis, 93*1000);
        strat[8] = new TacheGoto(nullptr, &positions_match[chgsta1], PurePursuit::FORWARD, false);
    }else{
        ////////////////////// STRAT 1 BLEU ///////////////////
        positions_match=positions_bleu;
        start = &positions_match[start2];
        nb_taches=9;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheExe((void*)listeActionneur::pince_pour_deplacer);
        strat[2] = new TacheGoto((Position*)nullptr, &positions_match[garage5all], PurePursuit::FORWARD);
        strat[3] = new TacheTransport();
        strat[4] = new TacheGoto((Position*)nullptr, &positions_match[depot3], PurePursuit::FORWARD, false);
        strat[5] = new TacheEmpiler();
        //FIN MATCH
        strat[6] = new TacheGoto((Position*)nullptr, &positions_match[check3], PurePursuit::FORWARD, false);
        strat[7] = new TacheWait(&start_millis, 93*1000);
        strat[8] = new TacheGoto(nullptr, &positions_match[chgsta1], PurePursuit::FORWARD, false);
        strat[8]->set_max_score(10);

    }
}

void Strategies::stratHomo(int team){
    if (team==TEAM_JAUNE){
        ////////////////////// STRAT 1 JAUNE ///////////////////
        positions_match=positions_jaune;
        start = &positions_match[start2];
        nb_taches=2;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheGotoWaypoints(PurePursuit::FORWARD, false, 2, &positions_match[check2], &positions_match[chgsta1]);
    }else{
        ////////////////////// STRAT 1 BLEU ///////////////////
        positions_match=positions_bleu;
        start = &positions_match[start2];
        nb_taches=2;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheGotoWaypoints(PurePursuit::FORWARD, false, 2, &positions_match[check2], &positions_match[chgsta1]);
    }
}

void Strategies::stratTestEmpilement(int team){
    if (team==TEAM_JAUNE){
        ////////////////////// STRAT 1 JAUNE ///////////////////
        positions_match=positions_jaune;
        start = &positions_match[start2];
        nb_taches=3;
        strat[0] = new TacheExe((void*)listeActionneur::pince_pour_deplacer);
        //strat[1] = new TacheMoveDelta(200,0);
        strat[1] = new TacheTransport();
        //strat[3] = new TacheMoveDelta(-100,0);
        strat[2] = new TacheEmpiler();
    }else{
        ////////////////////// STRAT 1 BLEU ///////////////////
        positions_match=positions_bleu;
        start = &positions_match[start2];
        nb_taches=5;
        strat[0] = new TacheExe((void*)listeActionneur::pince_pour_deplacer);
        strat[1] = new TacheMoveDelta(400,0);
        strat[2] = new TacheTransport();
        strat[3] = new TacheMoveDelta(-100,0);
        strat[4] = new TacheEmpiler();
    }
}
