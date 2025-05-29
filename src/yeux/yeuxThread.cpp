//
// Created by boris on 5/18/25.
//

#include "yeuxThread.h"
#include <Wire.h>

namespace yeuxThread {

    const char* animations[7] = {
            "A0*500$",
            "A1*500$",
            "A2*500$",
            "A3*500$",
            "A4*500$",
            "A5*500$",
            "A6*500$",
    };

    int lastSwitch = 0;
    u_short lastAnimation = 0;

    void yeux_setup() {
        yeux.setTx(YEUX_TX);
        yeux.setHalfDuplex();
        yeux.begin(115200);
    }

    void yeux_loop(void *pvParameters) {
        if (lastAnimation - millis() > TIME_BETWEEN_ANIMATIONS) {
            lastSwitch = millis();
            lastAnimation += 1;
            lastAnimation %= 7;
            yeux.println(animations[lastAnimation]);
        }
    }
}