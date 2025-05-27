//
// Created by boris on 30/10/2024.
//

#include "SensorsThread.h"
#include <Logger.h>

#include "My_Clock.h"
#include "Wheeledbase.h"
#include "include/SensorArray.h"

Logger sensors_logs = Logger("SENSORS");

void SensorsThread::Init(){

    i2c_init(&i2c2, 1000000, MASTER_ADDRESS);

    poly_delay(1000);

    sensors.addSensor({.addr = 0x55, 8});
    sensors.addSensor({.addr = 0x60, 7});
    sensors.addSensor({.addr = 0x45, 6});
    sensors.addSensor({.addr = 0x40, 5});
    sensors.addSensor({.addr = 0x35, 4});
    sensors.addSensor({.addr = 0x30, 3});
    sensors.addSensor({.addr = 0x25, 2});
    sensors.addSensor({.addr = 0x20, 1});

    sensors.Init();
}


void SensorsThread::Thread(void *pvParameters){

    for (;;){
        //getNormalisedData is REQUIRED to later work with sensors
        sensors.getNormalisedData();

        float lin, ang = 0;
        Wheeledbase::GET_VELOCITIES(&lin,&ang);

        if (sensors.isThereAnObstacle(lin))
        {
            sensors_logs.log(ERROR_LEVEL, "STOPPPP\n");
            Wheeledbase::SET_PARAMETER_VALUE(RIGHTWHEEL_MAXPWM_ID, 0);
            Wheeledbase::SET_PARAMETER_VALUE(LEFTWHEEL_MAXPWM_ID, 0);

            //Wait until no obstacle
            while (sensors.isThereAnObstacle(lin))
            {
                sensors.getNormalisedData();
            }

            Wheeledbase::SET_PARAMETER_VALUE(RIGHTWHEEL_MAXPWM_ID, 1);
            Wheeledbase::SET_PARAMETER_VALUE(LEFTWHEEL_MAXPWM_ID, 1);
        }


    }
}
