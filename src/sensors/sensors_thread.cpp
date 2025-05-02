//
// Created by boris on 30/10/2024.
//

#include "sensors_thread.h"

TwoWire i2c_bus;

VL53L5CX sensors[] = {
    (VL53L5CX(&i2c_bus,PD1)),
    (VL53L5CX(&i2c_bus,PE2)),
    (VL53L5CX(&i2c_bus,PE3)),
    (VL53L5CX(&i2c_bus,PE4)),
    (VL53L5CX(&i2c_bus,PE5)),
    (VL53L5CX(&i2c_bus,PG0)),
    (VL53L5CX(&i2c_bus,PG1)),
    (VL53L5CX(&i2c_bus,PD3)),
  };

uint16_t sensors_addr[] = {0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52};

void Sensors::Init(){

    i2c_bus = TwoWire(PF0,PF1);

    //Shutdown every i2c connection
    for (auto sensor: sensors) {
        sensor.begin();
        sensor.vl53l5cx_off();
    }

    delay(1000);

    // Initialize every vl53l5cx according to config
    uint8_t sensor_number = 0;
    for (auto sensor: sensors) {
        printf("Starting VL53L5CX %d for address : 0x%02x \n", sensor_number, sensors_addr[sensor_number]);

        //For each sensor activate the i2c connection and change the i2c address
        sensor.vl53l5cx_on();
        uint8_t status = sensor.init_sensor(sensors_addr[sensor_number]);

        if (status != VL53L5CX_STATUS_OK) {
            printf(COLOR_RED "Failed to initialize VL53L5CX %d, status : %d\n" COLOR_RESET, sensor_number, status);
        }else{
            printf(COLOR_GREEN "VL53L5CX %d initialized successfully !\n" COLOR_RESET, sensor_number);
        }
        sensor_number++;
    }

}

void sensorThread(void *pvParameters){

}
