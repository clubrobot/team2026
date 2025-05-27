//
// Created by bapti on 04/11/2024.
//

#include "Automate.h"
#include "My_Clock.h"
#include <chrono>
#include <FreeRTOS.h>
#include <FreeRTOSConfig_Default.h>
#include <Wheeledbase.h>
#include <FreeRTOS/Source/include/task.h>
#include <team2025/ListeActionneurs.h>

#include "variables_globales.h"
#include "sensors/SensorsThread.h"

#include "team2025/TacheEmpiler.h"
#include "team2025/TacheBanderole.h"


#include <Teleplot.h>
#include <team2025/Strategies.h>
#include <team2025/TacheTransport.h>

namespace Automate {
    Logger auto_logs = Logger("AUTOMATE");
    Tache** taches;//endroit de stockage des taches
    int color;//couleur de l'équipe
    int points;//points réalises pour l'instant
    int numberTaches;
}

void Automate::init(int team) {
    color=team;
    if(team==TEAM_JAUNE){
        auto_logs.log(WARNING_LEVEL, "Automate init avec Jaune\n");
    }else{
        auto_logs.log(WARNING_LEVEL, "Automate init avec Bleu\n");
    }
    //Load strat
    Strategies::strat1(team);

    //Load taches
    Wheeledbase::SET_POSITION(Strategies::start);//&positions_match[start2]);
    numberTaches=Strategies::nb_taches;
    taches = Strategies::strat;

}

Position start = Position(1700,300,-1.57);
Position test = Position(1500,1250,-1.57);
Position test2 = Position(1300,300,-1.57);

void Automate::play_match(void *pvParameters){

    Position* startPos = new Position(0,0,0);
    Position* endPos = new Position(800,200,0);

    Wheeledbase::SET_POSITION(startPos);
    Wheeledbase::GOTO(endPos,false, PurePursuit::FORWARD, PI/2);

    for (;;){

    }

    /*Wheeledbase::SET_POSITION(&start);
    Wheeledbase::GOTO_WAYPOINTS(true, PurePursuit::FORWARD, 2, &test, &test2);

    for (;;){}*/
    auto *procedure_demarrage = (void (*)()) pvParameters;
    //cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans l'ordre ou elles ont été ajoutée.
    //Seulement la fonction execute  et get_necessary_time doivent être implémentée.
    //auto start_time = std::chrono::high_resolution_clock::now();
    procedure_demarrage();
    start_millis=millis();
    poly_delay(100);
    listeActionneur::pince_pour_deplacer();
    poly_delay(100);
    points=0;
    bool state=true;
    for (int tache_id = 0; tache_id < numberTaches; ++tache_id) {
        auto_logs.log(INFO_LEVEL, "Tache n.%d\n", tache_id);
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        //auto current = std::chrono::high_resolution_clock::now();
        //auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        //auto_logs.log(INFO_LEVEL, "delta_t %f  et %f\n", delta_t, 100000-taches[tache_id]->get_necessary_time());
        //if(delta_t>100000-taches[tache_id]->get_necessary_time())break;//on est deja a la fin du match faut s'arrêter la
        //execute la tâche.
        state=taches[tache_id]->execute(state);
        //points+=taches[tache_id]->get_max_score();
    }
    Wheeledbase::SET_PARAMETER_VALUE(RIGHTWHEEL_MAXPWM_ID, 0);
    Wheeledbase::SET_PARAMETER_VALUE(LEFTWHEEL_MAXPWM_ID, 0);
    for (;;){

    }
}