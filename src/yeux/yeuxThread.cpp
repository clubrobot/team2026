//
// Created by boris on 5/18/25.
//

#include "yeuxThread.h"
#include <Wire.h>

namespace yeuxThread {
    HardwareSerial yeux(YEUX_TX);
    const char* animations[7] = {
            "A0*500$30 points",
            "A1*500$30 points",
            "A2*500$30 points",
            "A3*500$30 points",
            "A4*500$30 points",
            "A5*500$30 points",
            "A6*500$30 points",
    };

    short animationsLength[] = {
            2,
            4,
            4,
            9,
            8,
            4,
            4,

    };

    unsigned long lastSwitch = 0;
    u_short lastAnimation = 0;

    void yeux_setup() {
        yeux.setTx(YEUX_TX);
        yeux.setHalfDuplex();
        yeux.begin(115200);
    }

    void yeux_loop(void *pvParameters) {
        lastSwitch = millis();
        for (;;){
            if (millis()-lastSwitch > animationsLength[lastAnimation] * 500 * 2) {
                lastSwitch = millis();
                lastAnimation += 1;
                lastAnimation %= 7;
                yeux.println(animations[lastAnimation]);
            }
        }
    }
}