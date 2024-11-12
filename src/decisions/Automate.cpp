//
// Created by bapti on 04/11/2024.
//

#include "Automate.h"
#include <chrono>
extern int TEAM_BLEU;
extern int TEAM_JAUNE;
void Automate::init(int team) {
    color=team;
    if(team==TEAM_JAUNE){
        //import geogebra.h jaune
    }else{
        //import geogebra.h bleu
    }
    //mettre les tâches a éxécuter ici.

}

void Automate::play_match(){
    auto start_time = std::chrono::high_resolution_clock::now();
    points=0;
    for (int tache_id = 0; tache_id < taches::size(); ++tache_id) {
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        auto current = std::chrono::high_resolution_clock::now();
        auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        if(delta_t>100000-taches[tache_id].get_necessary_time())break;//on est deja a la fin du match faut s'arrêter la
        //execute la tâche.
        taches[tache_id]::execute();
        points+=taches[tache_id]::get_max_score();
    }

}