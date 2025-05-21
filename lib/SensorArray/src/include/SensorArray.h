//
// Created by romain on 5/18/25.
//

#ifndef SENSORARRAY_H
#define SENSORARRAY_H

#include <Arduino.h>
#include <Wire.h>

#include "Logger.h"
#include "uld/include/VL53L5CX.h"

#define SENSORARRAY_MAX 8
//Number of millis between two frames at 10Hz
#define SENSORARRAY_SENSOR_TIMEOUT (1/10*1000)c

//Todo enum this mode for 4x4 or 8x8

class SensorArray
{
public:
    struct SensorConfig
    {
        uint16_t addr;
        uint8_t pin;
    };

    struct SensorHandle
    {
        VL53L5CX* sensor;
        SensorConfig cfg;
        uint8_t is_alive;
    };

    SensorArray(i2c_t* i2c, uint32_t latch, uint32_t data, uint32_t clock);
    uint8_t addSensor(SensorConfig sensor_cfg);
    uint8_t Init();
    uint8_t Start();
    void Stop();

    uint8_t AquireRawData();
    uint8_t getNormalisedData();

    // get Raw Data²
    // normalise Data

private:
    uint8_t nb_sensors;
    std::array<SensorHandle, 8> sensors;
    int16_t raw_data[8][64] =  {};

    uint8_t power_config;

    uint32_t ds_pin;
    uint32_t shcp_pin;
    uint32_t stcp_pin;

    i2c_t* i2c_bus;

    Logger logs = Logger("Sensor Array");

    void ApplyPowerConfig() const;
};

#endif //SENSORARRAY_H
