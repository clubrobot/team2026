//
// Created by bapti on 04/02/2025.
//

#ifndef TEAM2025_TACHEBIPBIP_H
#define TEAM2025_TACHEBIPBIP_H
#include "decisions/Tache.h"

#include "TacheBipbip.h"
#include <Musique.h>

class TacheBipbip: public Tache{
//void execute();

    void execute() override{

        Musique myBeeper = Musique(PA6, 10);
        myBeeper.playSheetMusic(nokia);
    }

public:
    TacheBipbip(){
        set_max_score(-1);
    }
};


#endif //TEAM2025_TACHEBIPBIP_H
