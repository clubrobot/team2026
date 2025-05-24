//
// Created by boris on 30/10/2024.
//

#ifndef SENSORS_THREAD_H
#define SENSORS_THREAD_H

#include <FreeRTOS.h>

#include "include/SensorArray.h"

namespace SensorsThread
{

    void Init();


    inline i2c_t i2c2 = {.sda = PF_0, .scl = PF_1, .isMaster = 1, .generalCall = false, .NoStretchMode = false};
    inline SensorArray sensors = SensorArray(&i2c2, PE2, PD1, PE3);;

    void Thread(void *pvParameters);

}

#endif //SENSORS_THREAD_H
