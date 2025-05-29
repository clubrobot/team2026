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
        nb_taches=14;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheMoveDelta(200,0);
        strat[2] = new TacheExe((void*)listeActionneur::pince_pour_deplacer);
        strat[3] = new TacheGoto((Position*)nullptr, &positions_match[garage4all], PurePursuit::FORWARD);
        strat[4] = new TacheTransport();
        strat[5] = new TacheGoto((Position*)nullptr, &positions_match[depot3], PurePursuit::FORWARD,false);
        strat[6] = new TacheEmpiler(500);
        strat[7] = new TacheExe((void*)listeActionneur::asc_set_mid);
        strat[8] = new TacheGotoWaypoints(PurePursuit::FORWARD, true, 3, &positions_match[check1], &positions_match[garage8all], &positions_match[depot2]);
        strat[9] = new TacheTransport();
        strat[10] = new TacheEmpiler(100);

        //FIN MATCH
        strat[11] = new TacheGoto((Position*)nullptr, &positions_match[check3], PurePursuit::BACKWARD, false);
        strat[12] = new TacheWait(&start_millis, 93*1000);
        strat[13] = new TacheGoto(nullptr, &positions_match[chgsta1], PurePursuit::BACKWARD, false);
    }else{
        ////////////////////// STRAT 1 BLEU ///////////////////
        positions_match=positions_bleu;
        start = &positions_match[start2];
        nb_taches=14;
        strat[0] = new TacheBanderole();
        strat[1] = new TacheMoveDelta(200,0);
        strat[2] = new TacheExe((void*)listeActionneur::pince_pour_deplacer);
        strat[3] = new TacheGoto((Position*)nullptr, &positions_match[garage5all], PurePursuit::FORWARD);
        strat[4] = new TacheTransport();
        strat[5] = new TacheGoto((Position*)nullptr, &positions_match[depot3], PurePursuit::FORWARD);
        strat[6] = new TacheEmpiler(500);
        strat[7] = new TacheGotoWaypoints(PurePursuit::FORWARD, true, 2, &positions_match[check1], &positions_match[garage9all]);
        strat[8] = new TacheTransport();
        strat[9] = new TacheGoto(nullptr, &positions_match[depot2], PurePursuit::FORWARD, false);
        strat[10] = new TacheEmpiler(150);

        //FIN MATCH
        strat[11] = new TacheGoto((Position*)nullptr, &positions_match[check3], PurePursuit::FORWARD, false);
        strat[12] = new TacheWait(&start_millis, 93*1000);
        strat[13] = new TacheGoto(nullptr, &positions_match[chgsta1], PurePursuit::FORWARD, false);

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
        strat[5] = new TacheEmpiler(300);
        //FIN MATCH

        strat[6] = new TacheGoto((Position*)nullptr, &positions_match[check3], PurePursuit::FORWARD, false);
        strat[7] = new TacheWait(&start_millis, 93*1000);
        strat[8] = new TacheGoto(nullptr, &positions_match[chgsta1], PurePursuit::FORWARD, false);
        strat[8]->set_max_score(10);

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
        strat[5] = new TacheEmpiler(300);
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
        strat[2] = new TacheEmpiler(300);
    }else{
        ////////////////////// STRAT 1 BLEU ///////////////////
        positions_match=positions_bleu;
        start = &positions_match[start2];
        nb_taches=5;
        strat[0] = new TacheExe((void*)listeActionneur::pince_pour_deplacer);
        strat[1] = new TacheMoveDelta(400,0);
        strat[2] = new TacheTransport();
        strat[3] = new TacheMoveDelta(-100,0);
        strat[4] = new TacheEmpiler(300);
    }
}
