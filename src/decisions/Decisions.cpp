//
// Created by bapti on 04/11/2024.

#include "Decisions.h"
#include <iostream>
#include <chrono>
#include "Geogebra.h"
void Decisions::init(int team){
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
void Decisions::play_match(){
    auto start_time = std::chrono::high_resolution_clock::now();
    point_marque=0;
    while (taches.size()>0) {
        auto current = std::chrono::high_resolution_clock::now();
        auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        if(delta_t>100000)break;//on est deja a la fin du match faut s'arrêter la

        int tache_id = get_optimal_tache((100000.0-delta_t)/1000.0);
        if(tache_id==-1){
            std::cout << "Fin des tâches à réaliser. IMPLEMENTER RETOUR A LA BASE DE FIN."  << std::endl;

            break;
        }
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        //execute la tâche.
        taches[tache_id].execute();
        point_marque+=taches[tache_id].get_max_score();
    }
}

void TODO_pos(){
    std::cout << "ALTERTE METHODE RECUPERATION DE LA POSITION DU ROBOT NON IMPLEM DANS DECISIONS.CPP"  << std::endl;
}

int Decisions::get_optimal_tache(double remaining_time){
    /*On ca chercher la prochaine tâche qui permet de maximiser le nombre points obtenus à la fin du match.
     * Pour cela on explore toutes les combinaisons de tâches possibles dans le temps imparti. (l'algo à donc une compléxitée au pire de n!).
     * Cette méthode teste appelle la fonction max_cost pour chaque tâches afin d'evaluer le score maximum si
     * la prochaine tache est celle ci et retourne l'id de celle donnant le score maximal.
     * Input: remaining_time: temps restant en secondes
     * Output: l'identifiant (dans le vector tâche) de la prochaine tâche a réaliser ou -1 si il n'y a plus
     *         assez de temps pr réaliser une tâche.
     *
     * Amelioration:
     * - Pour que cette fonction soit intelligente il faut que le nomrbe de points soit adapté dynamiquement
     *  (par exemple si l'autre équipe réalise l'action alors, alors elle ne rapporte plus de points et on ne l'executera pas)
     *  Cela nécéssite un code supplémentaire et de la communication avec la caméra pas encore réalise (fin 2024).
     * - Il serait aussi possible de changer l'estimation du temps de trajet en prenant en compte le vrai trajet à la place de la ligne droit actuelle
     * - Il serait possible de diviser les tâches en sous-tâches. Par exemple au lieu d'avoir une seule tâche pr recup
     *      un objet et aller le déposer à un autre endroit il y aurait deux tâches une pour récupérer et l'autre pour déposer.
     *      Seulement la seconde donnerait des points mais elle requiererait la prmeière pour pouvoir être effectuée.
     *      Ont pourrait donc réduire le temps d'execution des tâches en les subdivisants.
     *      Cela necessiterait d'ajouter des conditions de réalisations dependant des tâches précédentes deja réalisée.
     */

    taches_temp.clear();
    //on init taches_temp avec toutes les tâches restantes à faire.
    for (int index = 0; index < taches.size(); ++index) {
        taches_temp.push_back(taches[index]);
    }
    double best_score=-1;
    int best_id=-1;

    //on va tester toute les tâches une à une.
    for (int index = 0; index < taches.size(); ++index) {
        Tache current = taches_temp[index];
        taches_temp.erase(taches_temp.begin() + index);
        //temps nécéssaire à réaliser la tâche.
        double time=current.get_necessary_time()+this->estimation_temps_deplacement(TODO_pos(),TODO_pos(),current.get_begin_x(),current.get_begin_y());
        if(remaining_time-time<=0)continue;//plus de temps pour réaliser cette tâche.

        //evalue le cout max de tout les autres tâches
        int sc = max_cost(remaining_time-time,current.get_begin_x(),current.get_begin_y());
        if(sc>best_score){
            best_score=sc;
            best_id=index;
        }
        taches_temp.insert(taches_temp.begin() + index,taches[index]);
    }
    return best_id;
}
double Decisions::max_cost(double remaining_time, int pos_x,int pos_y){
    /*Cette fonction recursive calcule le cout maximal qu'il est possible d'atteindre avec
     * les tâches restante dans la liste taches_temps dans le temps imparti.
     * On suppose que le robot est positionné en (pos_x, pos_y) au debut.
     * Il va tester toute les tâches et s'appeler recursivement pour trouver la valeur optimale.
     */
    /*Amélioration possible:
     * Il est possible d'accéler l'algo en arretant egalement on sait que dans le temps restant on ne pourra pas
     * améliorer le score assez pour qu'il soit plus grand que la plus grande solution trouvé jusqu à maintenant
     * Si S est le meilleur score trouve maintenant A le score actuel, T le temps restant et M le maximum
     * de score_tache/temps_tache de toutes les tâches
     * Alors si (S-A)/T<M alors on peut arrêter d'explorer les autres tâches et on aura toujours le résultat optimal.
     */
    double best_score=0;
    for (int index = 0; index < taches_temp.size(); ++index) {
        Tache current = taches_temp[index];
        taches_temp.erase(taches_temp.begin() + index);
        //temps nécéssaire à réaliser la tâche.
        double time=current.get_necessary_time()+this->estimation_temps_deplacement(pos_x, pos_y, current.get_begin_x(),current.get_begin_y());
        if(remaining_time-time<=0)continue;//plus de temps pour réaliser cette tâche.
        //evalue le cout max de tout les autres tâches
        int sc = max_cost(remaining_time-time,current.get_begin_x(),current.get_begin_y());

        if(sc>best_score)
            best_score=sc;

        taches_temp.insert(taches_temp.begin() + index,taches[index]);
    }
    return best_score;
}

double Decisions::estimation_temps_deplacement(int depart_x, int depart_y, int arrive_x, int arrive_y){
    /* Cette méthode utilise une loi trapèze pour estimer le temps de trajet du robot.
     * Elle considère que le trajet est réalise en ligne droite.
     *
     */

    double half_distance=sqrt((depart_x-arrive_x)*(depart_x-arrive_x)+(depart_y-arrive_y)*(depart_y-arrive_y))/2;
    double max_acc=0.5;//a modifier
    double max_vit=0.5;//a modifier 
    //utilise une loi trapeze (symmetrique par rapport au milieu) pr approximer le temps de trajet.
    //d_acc=0.5*max_acc*t^2
    double t_acc=sqrt(2*half_distance/max_acc);
    //on check si un fois arrive au milieu il est a sa vitesse max et si non on a directement le temps d'arrive.
    if(t_acc<max_vit/max_acc){
        return t_acc*2;
    }
    //si oui il faut calculer le temps qu'il a passe a max vitesse;
    double dist_restante=half_distance-0.5*max_acc*(max_vit/max_acc*max_vit/max_acc);
    return (max_vit/max_acc+dist_restante/max_vit)*2;
}
