//
// Created by boris on 30/10/2024.
//

#ifndef SENSORS_THREAD_H
#define SENSORS_THREAD_H

#include <Wire.h>
#include <vl53l5cx_class.h>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <cassert>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

namespace Sensors
{

    void Init();
}

#endif //SENSORS_THREAD_H
