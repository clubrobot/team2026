//
// Created by bapti on 30/05/2025.
//

#ifndef TEAM2025_TACHEDESCENDRERECULER_H
#define TEAM2025_TACHEDESCENDRERECULER_H
#include "decisions/Tache.h"

class TacheDescendreReculer :public Tache{
    float recul,recul_debut;
    bool execute(bool previous_success) override;
public:
    TacheDescendreReculer(float recul,float debut_descente):recul(recul),recul_debut(debut_descente){

    }
};


#endif //TEAM2025_TACHEDESCENDRERECULER_H
