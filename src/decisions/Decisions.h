//
// Created by bapti on 04/11/2024.
//

#ifndef TEAM2025_DECISIONS_H
#define TEAM2025_DECISIONS_H
#include <Arduino.h>
#include <vector>
#include "variables_globales.h"
#include "Tache.h"

class Decisions {
//Execute les tâches dans un ordre spécifique de facon à maximiser les current_points à la fin du match.
private:
    std::vector<Tache> taches;//liste des differentes taches
    std::vector<Tache> taches_temp;//liste permettant de stocker les taches pas encore réalisé pour déterminer la prochaine
    int point_marque;//current_points marque pour l'instant
    int color;
public:
    double estimation_temps_deplacement(int depart_x, int depart_y, int arrive_x, int arrive_y);//cette fonction estime le temps de déplacement entre deux current_points
    void init(int team);//fonction d'init
    //cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans un ordre choisi de facon a maximiser le nombre de current_points.
    //Toutes les fonctions doivent être implémentées
    void play_match();//fonction a appeller au début du match
    int get_optimal_tache(double remaining_time);
    double max_cost(double remaining_time, int pos_x,int pos_y);
    int TODO_pos();
};


#endif //TEAM2025_DECISIONS_H
