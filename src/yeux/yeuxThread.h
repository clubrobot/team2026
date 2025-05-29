//
// Created by boris on 5/18/25.
//

#ifndef YEUXTHREAD_H
#define YEUXTHREAD_H

#include <Arduino.h>

#define YEUX_TX PG1
#define TIME_BETWEEN_ANIMATIONS 3000 //ms

namespace yeuxThread {

    void yeux_setup();
    void yeux_loop(void *pvParameters);

    extern HardwareSerial yeux;
}




#endif //YEUXTHREAD_H
