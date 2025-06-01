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
#include "yeux/yeuxThread.h"
namespace Automate {
    Logger auto_logs = Logger("AUTOMATE");
    Tache** taches;//endroit de stockage des taches
    int color;//couleur de l'équipe
    int current_points;//current_points réalises pour l'instant
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
    //Strategies::stratDeBase(team) ;
    Strategies::strat1(team) ;
    //Strategies::stratTestEmpilement(team);
    //Load taches
    Wheeledbase::SET_POSITION(Strategies::start);//&positions_match[start2]);
    numberTaches=Strategies::nb_taches;
    taches = Strategies::strat;
    current_points=0;
}

Position start = Position(1700,300,-1.57);
Position test = Position(1500,1250,-1.57);
Position test2 = Position(1300,300,-1.57);

void Automate::play_match(void *pvParameters){
    auto *procedure_demarrage = (void (*)()) pvParameters;
    //cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans l'ordre ou elles ont été ajoutée.
    //Seulement la fonction execute  et get_necessary_time doivent être implémentée.
    //auto start_time = std::chrono::high_resolution_clock::now();
    procedure_demarrage();
    start_millis=millis();

    current_points=0;
    bool state=true;
    match_started=true;
    for (int tache_id = 0; tache_id < numberTaches; ++tache_id) {
        auto_logs.log(INFO_LEVEL, "Tache n.%d\n", tache_id);
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        //auto current = std::chrono::high_resolution_clock::now();
        //auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        //auto_logs.log(INFO_LEVEL, "delta_t %f  et %f\n", delta_t, 100000-taches[tache_id]->get_necessary_time());
        //if(delta_t>100000-taches[tache_id]->get_necessary_time())break;//on est deja a la fin du match faut s'arrêter la
        //execute la tâche.
        state=taches[tache_id]->execute(state);
        if(state){
            current_points+=taches[tache_id]->get_max_score();
            char phrase[50];
            sprintf(phrase,"SMERCI AISPRID  *75$score 54");
            printf("%s\n",phrase);
            yeuxThread::yeux.println(phrase);
        }
    }
    Wheeledbase::SET_PARAMETER_VALUE(RIGHTWHEEL_MAXPWM_ID, 0);
    Wheeledbase::SET_PARAMETER_VALUE(LEFTWHEEL_MAXPWM_ID, 0);
    for (;;){

    }
}