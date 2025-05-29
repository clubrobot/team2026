//
// Created by boris on 5/26/25.
//

#ifndef TACHETRANSPORT_H
#define TACHETRANSPORT_H



#include "decisions/Tache.h"

class TacheTransport: public Tache{
    bool execute(bool previous_success) override;
public:
    TacheTransport(){
        set_max_score(0);
    }
};



#endif //TACHETRANSPORT_H
