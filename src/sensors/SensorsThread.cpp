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
#include "variables_globales.h"
Logger sensors_logs = Logger("SENSORS");


void SensorsThread::Init(){

    //i2c_custom_init(&i2c2, 1000000, I2C_ADDRESSINGMODE_7BIT, MASTER_ADDRESS);
    i2c_init(&i2c2, 1000000, MASTER_ADDRESS);

    poly_delay(1000);

    sensors.addSensor({.addr = 0x55, .pin = 8});
    sensors.addSensor({.addr = 0x60, .pin = 7});
    sensors.addSensor({.addr = 0x45, .pin = 6});
    sensors.addSensor({.addr = 0x40, .pin = 5});
    sensors.addSensor({.addr = 0x35, .pin = 4});
    sensors.addSensor({.addr = 0x30, .pin = 3});
    sensors.addSensor({.addr = 0x25, .pin = 2});
    sensors.addSensor({.addr = 0x20, .pin = 1});

    sensors.Init();
}



void SensorsThread::Thread(void *pvParameters){
    auto *wb = static_cast<Wheeledbase::WheeledBase*>(pvParameters);

    for (;;){
        //getNormalisedData is REQUIRED to later work with sensors
        sensors.getNormalisedData(*wb);
        bool obstacle = false;
        obstacle = sensors.isThereAnObstacle(-PI/4, PI/4, 400);
        obstacle |= sensors.isThereAnObstacle(PI/4, -PI/4, 300);

        wb->velocityControl->set_stop(obstacle);
    }
}
