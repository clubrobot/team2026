//
// Created by bapti on 04/11/2024.
//

#ifndef TEAM2025_AUTOMATE_H
#define TEAM2025_AUTOMATE_H
#include <vector>
#include "Tache.h"
class Automate {
    //cette classe réalise les tâches les unes après les autres dans l'ordre ou elles ont été données.
private:
    std::vector<Tache> taches;//endroit de stockage des taches
    int color;//couleur de l'équipe
    int points;//points réalises pour l'instant
public:
    void init(int team);//fonction d'init
    void play_match();//fonction a appeller au début du match

};

#endif //TEAM2025_AUTOMATE_H
