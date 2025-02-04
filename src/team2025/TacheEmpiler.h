//
// Created by bapti on 04/02/2025.
//

#ifndef TEAM2025_TACHEEMPILER_H
#define TEAM2025_TACHEEMPILER_H
#include "decisions/Tache.h"

#include "Wheeledbase.h"
#include <STM32FreeRTOS.h>

class TacheEmpiler: public Tache{

    void execute() {

        Wheeledbase::GOTO_DELTA(400,0);
        while(Wheeledbase::POSITION_REACHED()!=0b01) {  }
        vTaskDelay(pdMS_TO_TICKS(2000));
        Wheeledbase::START_TURNONTHESPOT(0,-1.57);
        while(Wheeledbase::POSITION_REACHED()!=0b01) { }
        vTaskDelay(pdMS_TO_TICKS(2000));
        Wheeledbase::START_TURNONTHESPOT(0,0);
        while(Wheeledbase::POSITION_REACHED()!=0b01) { }
        vTaskDelay(pdMS_TO_TICKS(2000));
        Wheeledbase::GOTO_DELTA(-400,0);
        while(Wheeledbase::POSITION_REACHED()!=0b01) { }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }

public:
    TacheEmpiler(){
        set_max_score(911);
    }
};


#endif //TEAM2025_TACHEEMPILER_H
