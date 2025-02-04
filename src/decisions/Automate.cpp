//
// Created by bapti on 04/11/2024.
//

#include "Automate.h"
#include "Clock.h"
#include <chrono>
#include "Geogebra.h"
#include "variables_globales.h"

namespace Automate {
    std::vector<Tache> taches;//endroit de stockage des taches
    int color;//couleur de l'équipe
    int points;//points réalises pour l'instant
}

void Automate::init(int team) {
    color=team;
    if(team==TEAM_JAUNE){
        //import geogebra.h jaune
        positions_match=positions_jaune;
    }else{
        //import geogebra.h bleu
        positions_match=positions_bleu;
    }
    //mettre les tâches a éxécuter ici.

}

<<<<<<< Updated upstream
void Automate::play_match(void *pvParameters){
    //TODO: wait for event
=======
//cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans l'ordre ou elles ont été ajoutée.
//Seulement la fonction execute  et get_necessary_time doivent être implémentée.
void Automate::play_match(){
>>>>>>> Stashed changes
    auto start_time = std::chrono::high_resolution_clock::now();
    points=0;
    for (int tache_id = 0; tache_id < taches.size(); ++tache_id) {
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        auto current = std::chrono::high_resolution_clock::now();
        auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        if(delta_t>100000-taches[tache_id].get_necessary_time())break;//on est deja a la fin du match faut s'arrêter la
        //execute la tâche.
        taches[tache_id].execute();
        points+=taches[tache_id].get_max_score();
    }
}