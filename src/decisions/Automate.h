//
// Created by bapti on 04/11/2024.
//

#ifndef TEAM2025_AUTOMATE_H
#define TEAM2025_AUTOMATE_H
#include <Logger.h>
#include <vector>
#include "Tache.h"

namespace Automate{
        //cette classe réalise les tâches les unes après les autres dans l'ordre ou elles ont été données.
        extern Tache** taches;//endroit de stockage des taches
        extern int color;//couleur de l'équipe
        extern int current_points;//current_points réalises pour l'instant
        extern int numberTaches;
        void init(int team);//fonction d'init
        void play_match(void *pvParameters);//fonction a appeler au début du match
};

#endif //TEAM2025_AUTOMATE_H
