//
// Created by boris on 30/10/2024.
//

#include "SensorsThread.h"
#include <Logger.h>

#include "My_Clock.h"
#include "Wheeledbase.h"
#include "include/SensorArray.h"
#include "Constant.h"
#include "Wire.h"
Logger sensors_logs = Logger("SENSORS");

void SensorsThread::Init(){

    //i2c_custom_init(&i2c2, 1000000, I2C_ADDRESSINGMODE_7BIT, MASTER_ADDRESS);
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
        auto position=Wheeledbase::GET_POSITION();
        velocityControl.set_stop(false);
        //if (sensors.isThereAnObstacle(lin))
/*
        if (sensors.isThereAnObstacle(lin))
        {
            sensors_logs.log(ERROR_LEVEL, "STOPPPP\n");
            velocityControl.set_stop(true);
            //Wait until no obstacle
            while (sensors.isThereAnObstacle(lin))
            {
                sensors.getNormalisedData();
            }
            sensors_logs.log(GOOD_LEVEL, "REPRISE\n");
            velocityControl.set_stop(false);
        }

*/
    }
}
