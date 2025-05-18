//
// Created by romain on 5/17/25.
//

#include "include/SensorArray.h"

#include "../../Include/My_Clock.h"
#include "uld/include/VL53L5CX.h"

SensorArray::SensorArray(TwoWire *i2c, uint32_t latch, uint32_t data, uint32_t clock)
{
    this->power_config = 0b00000000;

    //Define pins
    this->ds_pin = data;
    this->shcp_pin = clock;
    this->stcp_pin = latch;

    this->i2c_bus = i2c;

    this->nb_sensors = 0;
}

uint8_t SensorArray::addSensor(const SensorConfig sensor_cfg)
{
    //Check if the i2c address is not already used
    for (int i = 0; i < this->nb_sensors; ++i)
    {
        if (sensor_cfg.addr == sensors[i].cfg.addr)
        {
            logs.log(ERROR_LEVEL, "Sensor %d and sensor %d have the same address : 0x%02x\n", sensor_cfg.pin, sensors[i].cfg.pin, sensor_cfg.addr);
            return 1;
        }
    }
    if (this->nb_sensors < SENSORARRAY_MAX)
    {
        this->sensors[nb_sensors] =  {.sensor = new VL53L5CX(this->i2c_bus), .cfg = sensor_cfg};
        ++nb_sensors;
        return 0;
    }
    logs.log(ERROR_LEVEL, "The sensor array as already 8 sensors\n");
    return 1;
}

/*
 * Waring : The sensors must be shut down before initialization with a new address
 */

uint8_t SensorArray::Init()
{
    int started_sensors = 0;

    //Init the pins
    pinMode(stcp_pin, OUTPUT);
    pinMode(shcp_pin, OUTPUT);
    pinMode(ds_pin, OUTPUT);

    this->power_config = 0;
    this->ApplyPowerConfig();

    for (int i = 0; i < this->nb_sensors; ++i)
    {
        SensorHandle handle = sensors[i];
        logs.log(INFO_LEVEL, "Starting VL53L5CX %d for address : 0x%02x \n", handle.cfg.pin, handle.cfg.addr);

        //Power this sensor to change its address
        this->power_config += 1 << handle.cfg.pin - 1;
        this->ApplyPowerConfig();

        this->i2c_bus->begin();

        poly_delay(1000);

        //Ne fonctionne pas avec handle.sensor->init_sensor
        uint8_t status = handle.sensor->init_sensor(handle.cfg.addr);

        uint8_t alive = 0;
        handle.sensor->vl53l5cx_is_alive(&alive);

        if (alive)
        {
            logs.log(GOOD_LEVEL, "VL53L5CX %d has already been initialized !\n", handle.cfg.pin);
            ++started_sensors;
            continue;
        }

        if (status != VL53L5CX_STATUS_OK) {
            this->power_config = this->power_config & ~(1 << (handle.cfg.pin - 1));
            logs.log(ERROR_LEVEL, "Failed to initialize VL53L5CX %d, status : %d\n", handle.cfg.pin, status);
        }else{
            logs.log(GOOD_LEVEL, "VL53L5CX %d initialized successfully !\n", handle.cfg.pin);
            ++started_sensors;
        }
    }

    this->ApplyPowerConfig();

    logs.log(started_sensors != this->nb_sensors ? ERROR_LEVEL : GOOD_LEVEL, "Started %d/%d sensors\n", started_sensors, this->nb_sensors);

    return started_sensors != this->nb_sensors;
}

void SensorArray::ApplyPowerConfig() const
{
    digitalWrite(ds_pin, 0);
    digitalWrite(stcp_pin, 0);
    digitalWrite(shcp_pin, 0);

    for (int i = SENSORARRAY_MAX - 1; i >= 0; i--)
    {
        delay(1);
        digitalWrite(shcp_pin, 0);

        //Sets the pin to HIGH or LOW depending on bits of the power config
        digitalWrite(ds_pin, power_config & (1<<i));

        //Register shifts bits on upstroke of clock pin
        digitalWrite(shcp_pin, 1);

        //Clear the data pin after shift to prevent bleed through
        digitalWrite(ds_pin, 0);

    }

    //Stop shifting
    digitalWrite(shcp_pin, 0);
    digitalWrite(stcp_pin, 1);
}

uint8_t SensorArray::getData(Output* out)
{
    return 0;
}


void SensorArray::task()
{

}


void SensorArray::Stop()
{
    for (int i = 0; i < this->nb_sensors; ++i)
    {
        delete sensors[i].sensor;
    }
}

