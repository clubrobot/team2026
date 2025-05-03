//
// Created by boris on 30/10/2024.
//

#ifndef SENSORS_THREAD_H
#define SENSORS_THREAD_H

#include <FreeRTOS.h>

#include <Wire.h>
#include <vl53l5cx_class.h>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <cassert>

namespace Sensors
{

    void Init();
}
extern float dist1;
extern float dist2;

void sensorThread(void *pvParameters);
#endif //SENSORS_THREAD_H
