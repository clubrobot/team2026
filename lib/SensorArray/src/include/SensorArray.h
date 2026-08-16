//
// Created by romain on 5/18/25.
//

#ifndef SENSORARRAY_H
#define SENSORARRAY_H

#include <Arduino.h>
#include <Wire.h>

#include "../../Wheeledbase/include/Components/Odometry.h"
#include "Logger.h"
#include "Types.h"
#include "Wheeledbase.h"
#include "uld/include/VL53L5CX.h"

#define MASTER_ADDRESS 0x01

#define SENSORARRAY_MAX 8
//Number of millis between two frames at 10Hz
#define SENSORARRAY_SENSOR_TIMEOUT (1/10*1000)c
#define SENSORARRAY_RESOLUTION VL53L5CX_RESOLUTION_8X8

#define X_FROM_1D(i) (uint8_t) floor(i / 8.00)
#define Y_FROM_1D(i) (uint8_t) (i % 8)

#define X_Y_FOR_LOOP uint8_t x = 0, y = 0; x < 8 && y < 8; y = (y + 1) % 8, x += y ? 0 : 1

//Sensors positions in the frame
#define SENSORARRAY_FRAME_RADIUS 38.2
#define SENSORARRAY_FRAME_Z 70.8
#define SENSORARRAY_ROOF_Z 340.0

#ifndef SENSORARRAY_STOP_DISTANCE_FORWARD
#define SENSORARRAY_STOP_DISTANCE_FORWARD 475
#endif

#ifndef SENSORARRAY_STOP_DISTANCE_BACKWARD
#define SENSORARRAY_STOP_DISTANCE_BACKWARD 400
#endif
#define SENSORARRAY_FUTURE_ORIGIN 1
#define SENSORARRAY_CURRENT_ORIGIN 0

static Logger logs = Logger("SensorArray");
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

    //Get new data
    uint8_t getNormalisedData(const Wheeledbase::WheeledBase& wheeledbase);
    void Print();
    bool isThereAnObstacle(float start, float end, float distance);

    std::vector<Point> points;
    bool isThereAnObstacleTerrain(bool interrupt, float velocity, float current_angle, float current_x, float current_y,
                                  float max_x, float max_y);

private:
    uint8_t nb_sensors;
    std::array<SensorHandle, 8> sensors;

    VL53L5CX_ResultsData raw_data[8] = {};
    Position origin_mesure[2][8];

    uint8_t power_config;

    uint32_t ds_pin;
    uint32_t shcp_pin;
    uint32_t stcp_pin;

    i2c_t* i2c_bus;


    void ApplyPowerConfig() const;
    uint8_t AquireRawData(const Wheeledbase::WheeledBase& wheeledbase);
    static void Mesurement_to_Point(uint16_t measure, uint8_t x, uint8_t y, Point* point);



};

#endif //SENSORARRAY_H
