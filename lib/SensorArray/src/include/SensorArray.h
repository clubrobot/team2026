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

class SensorArray
{
public:
    struct SensorConfig
    {
        uint32_t addr;
        uint8_t pin;
    };

    struct SensorHandle
    {
        VL53L5CX* sensor;
        SensorConfig cfg;
    };

    struct Output
    {

    };

    SensorArray(TwoWire* i2c, uint32_t latch, uint32_t data, uint32_t clock);
    uint8_t addSensor(SensorConfig sensor_cfg);
    uint8_t Init();
    uint8_t getData(Output* out);
    void task();
    void Stop();

private:
    uint8_t nb_sensors;
    std::array<SensorHandle, 8> sensors;

    uint8_t power_config;

    uint32_t ds_pin;
    uint32_t shcp_pin;
    uint32_t stcp_pin;

    TwoWire* i2c_bus;

    Logger logs = Logger("Sensor Array");

    void ApplyPowerConfig() const;
};

#endif //SENSORARRAY_H
