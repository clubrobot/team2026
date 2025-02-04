//
// Created by bapti on 04/11/2024.
//

#include "Automate.h"
#include "Clock.h"
#include <chrono>
#include "Geogebra.h"
#include "variables_globales.h"

#include "team2025/TacheBipbip.h"
#include "team2025/TacheEmpiler.h"

namespace Automate {
    Tache* taches[100];//endroit de stockage des taches
    int color;//couleur de l'équipe
    int points;//points réalises pour l'instant
    int numberTaches;
}

void Automate::init(int team) {
    color=team;
    if(team==TEAM_JAUNE){
        //import geogebra.h jaune
        positions_match=positions_jaune;
        numberTaches=2;
        taches[0]=new TacheBipbip();
        taches[1]=new TacheEmpiler();
    }else{
        //import geogebra.h bleu
        positions_match=positions_bleu;
    }
    //mettre les tâches a éxécuter ici.

}

void Automate::play_match(void *pvParameters){
//cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans l'ordre ou elles ont été ajoutée.
//Seulement la fonction execute  et get_necessary_time doivent être implémentée.
    auto start_time = std::chrono::high_resolution_clock::now();
    points=0;
    for (int tache_id = 0; tache_id < numberTaches; ++tache_id) {
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        auto current = std::chrono::high_resolution_clock::now();
        auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        if(delta_t>100000-taches[tache_id]->get_necessary_time())break;//on est deja a la fin du match faut s'arrêter la
        //execute la tâche.
        taches[tache_id]->execute();
        points+=taches[tache_id]->get_max_score();
    }
}