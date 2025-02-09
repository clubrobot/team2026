//
// Created by boris on 27/01/2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "coloring.h"

/**
* TODO:
* Different type of loggers:
* 1: Print all to screen directly
* 2: Save prints to buffer then print to screen
* 3: file system ?
*/

#define MAX_NAME 50
#define ERROR_LEVEL 3
#define WARNING_LEVEL 2
#define GOOD_LEVEL 1
#define INFO_LEVEL 0

#undef Error_Handler
#define Error_Handler() \
while (1) {\
printf("ERREUR MAJEURE dans %s:%d \n", __FILE__, __LINE__);\
digitalWrite(LED_RED, HIGH);\
delay(500);\
digitalWrite(LED_RED, LOW);\
delay(500);\
}

class Logger {
public:
    Logger(const char* name);
    int log(uint8_t level, const char* format, ...);
private:
    char _name[50];
    static int log_static(uint8_t level,char* name, const char* format, va_list args);
}; // Logger

#endif //LOGGER_H
