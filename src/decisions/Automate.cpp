//
// Created by bapti on 04/11/2024.
//

#include "Automate.h"
#include "My_Clock.h"
#include <chrono>
#include <Wheeledbase.h>

#include "Geogebra.h"
#include "variables_globales.h"

#include "team2025/TacheBipbip.h"
#include "team2025/TacheEmpiler.h"

namespace Automate {
    Logger auto_logs = Logger("AUTOMATE");
    Tache* taches[100];//endroit de stockage des taches
    int color;//couleur de l'équipe
    int points;//points réalises pour l'instant
    int numberTaches;
}

Position pos_beg = Position(0,0,0);
Position pos_appr = Position(100,0,0);
Position pos_end = Position(200,0,0);

void Automate::init(int team) {
    color=team;
    if(team==TEAM_JAUNE){
        auto_logs.log(WARNING_LEVEL, "Automate init avec Jaune\n");
        //import geogebra.h jaune
        positions_match=positions_jaune;
        numberTaches=1;

        taches[0]=new TacheGoto(&pos_beg,&pos_appr, &pos_end);
    }else{
        auto_logs.log(INFO_LEVEL, "Automate init avec Bleu\n");
        //import geogebra.h bleu
        positions_match=positions_bleu;
    }
    //mettre les tâches a éxécuter ici.

}

void Automate::play_match(void *pvParameters){

    for(;;) {
        Wheeledbase::GOTO(&pos_appr, 0, 0);
        delay(500);
        Wheeledbase::GOTO(&pos_beg, 0, 0);
        delay(500);

    }
//cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans l'ordre ou elles ont été ajoutée.
//Seulement la fonction execute  et get_necessary_time doivent être implémentée.
    auto start_time = std::chrono::high_resolution_clock::now();
    points=0;
    for (int tache_id = 0; tache_id < numberTaches; ++tache_id) {
        auto_logs.log(INFO_LEVEL, "Tache n.%d\n", tache_id);
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        auto current = std::chrono::high_resolution_clock::now();
        auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        auto_logs.log(INFO_LEVEL, "delta_t %f  et %f\n", delta_t, 100000-taches[tache_id]->get_necessary_time());
        //if(delta_t>100000-taches[tache_id]->get_necessary_time())break;//on est deja a la fin du match faut s'arrêter la
        //execute la tâche.
        taches[tache_id]->execute();
        points+=taches[tache_id]->get_max_score();
    }

}