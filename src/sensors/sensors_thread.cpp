//
// Created by boris on 30/10/2024.
//

#include "sensors_thread.h"
#include <Logger.h>
#include <FreeRTOS/Source/include/task.h>

TwoWire i2c_bus;
Logger sensors_logs = Logger("SENSORS");

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
#define TRIG1 PD1
#define ECHO1 PE2
#define TRIG2 PE3
#define ECHO2 PE4

void Sensors::Init(){

    pinMode(TRIG1, OUTPUT);
    pinMode(ECHO1,  INPUT);
    pinMode(TRIG2, OUTPUT);
    pinMode(ECHO2,  INPUT);

    /*i2c_bus = TwoWire(PF0,PF1);
    i2c_bus.begin();
    sensors[0].begin();
    sensors[0].init_sensor();
    sensors[0].vl53l5cx_start_ranging();
    for (;;){
        static uint8_t loop_count = 0;
        VL53L5CX_ResultsData Results;
        uint8_t NewDataReady = 0;
        char report[64];
        uint8_t status;

        if (loop_count < 10) {

            do {
                status = sensors[0].vl53l5cx_check_data_ready(&NewDataReady);
            } while (!NewDataReady);

            if ((!status) && (NewDataReady != 0)) {
                status = sensors[0].vl53l5cx_get_ranging_data(&Results);

                // As the sensor is set in 4x4 mode by default, we have a total
                //of 16 zones to print.
                //

                snprintf(report, sizeof(report), "Print data no : %3u\r\n", sensors[0].get_stream_count());
                printf(report);
                for (int i = 0; i < 16; i++) {
                    snprintf(report, sizeof(report), "Zone : %3d, Status : %3u, Distance : %4d mm\r\n",
                             i,
                             Results.target_status[VL53L5CX_NB_TARGET_PER_ZONE * i],
                             Results.distance_mm[VL53L5CX_NB_TARGET_PER_ZONE * i]);
                    printf(report);
                }
                printf("\n");
                loop_count++;
            }

        } else if (loop_count == 10) {
           //Stop measurements
            status = sensors[0].vl53l5cx_stop_ranging();
            if (status) {
                snprintf(report, sizeof(report), "vl53l5cx_stop_ranging failed, status %u\r\n", status);
                printf("\n");
                Error_Handler();
            }

            loop_count++;
            // End of the demo
            printf("End of ULD demo\n");
        } else {
            delay(1000);
        }
    }
    //Shutdown every i2c connection
    for (auto sensor: sensors) {
        sensor.begin();
        sensor.vl53l5cx_off();
    }

    delay(1000);

    // Initialize every vl53l5cx according to config
    uint8_t sensor_number = 0;
    for (auto sensor: sensors) {
        sensors_logs.log(INFO_LEVEL, "Starting VL53L5CX %d for address : 0x%02x \n", sensor_number, sensors_addr[sensor_number]);

        //For each sensor activate the i2c connection and change the i2c address
        sensor.vl53l5cx_on();
        uint8_t status = sensor.init_sensor(sensors_addr[sensor_number]);

        if (status != VL53L5CX_STATUS_OK) {
            sensors_logs.log(ERROR_LEVEL, "Failed to initialize VL53L5CX %d, status : %d\n", sensor_number, status);
        }else{
            sensors_logs.log(GOOD_LEVEL, "VL53L5CX %d initialized successfully !\n", sensor_number);
        }
        sensor_number++;
    }*/

}
float dist1, dist2;
void sensorThread(void *pvParameters){
    for (;;){

    }
    for (;;){
        vTaskSuspendAll();
        digitalWrite(TRIG1, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG1, HIGH); // On met la broche TRIG a "1" pendant 10μS //
        delayMicroseconds(10);
        digitalWrite(TRIG1, LOW); // On remet la broche TRIG a "0" //
        long duree1 = pulseIn(ECHO1, HIGH);
        dist1= duree1*0.034/2; // *** voir explications apres l'exemple de code

        digitalWrite(TRIG2, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG2, HIGH); // On met la broche TRIG a "1" pendant 10μS //
        delayMicroseconds(10);
        digitalWrite(TRIG2, LOW); // On remet la broche TRIG a "0" //
        long duree2 = pulseIn(ECHO2, HIGH);
        dist2= duree2*0.034/2; // *** voir explications apres l'exemple de code
        xTaskResumeAll();
        vTaskDelay(pdMS_TO_TICKS(2));
    }
}
