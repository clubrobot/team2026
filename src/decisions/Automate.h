//
// Created by bapti on 04/11/2024.
//

#ifndef TEAM2025_AUTOMATE_H
#define TEAM2025_AUTOMATE_H
#include <vector>
#include "Tache.h"
<<<<<<< Updated upstream

namespace Automate{
        //cette classe réalise les tâches les unes après les autres dans l'ordre ou elles ont été données.
        extern std::vector<Tache> taches;//endroit de stockage des taches
        extern int color;//couleur de l'équipe
        extern int points;//points réalises pour l'instant

        void init(int team);//fonction d'init
        void play_match(void *pvParameters);//fonction a appeler au début du match
=======
class Automate {
    //
    //cette classe réalise les tâches les unes après les autres dans l'ordre ou elles ont été données.
private:
    std::vector<Tache> taches;//endroit de stockage des taches
    int color;//couleur de l'équipe
    int points;//points réalises pour l'instant
public:
    //cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans l'ordre ou elles ont été ajoutée.
    //Seulement la fonction execute  et get_necessary_time doivent être implémentée.
    void init(int team);//fonction d'init
    void play_match();//fonction a appeler au début du match
>>>>>>> Stashed changes

};

#endif //TEAM2025_AUTOMATE_H
