//
// Created by boris on 27/01/2025.
//

#include "Logger.h"


Logger::Logger(const char* name) {
    strncpy(_name, name, MAX_NAME);
}

int Logger::log(uint8_t level, const char* format, ...) {
    va_list args;
    int nbcharprinted;
    va_start(args, format);
    log_static(level, _name, format, args);
    va_end(args);
    return nbcharprinted;
}

int Logger::log_static(uint8_t level,char* name, const char* format, va_list args) {

    switch (level) {
    case ERROR_LEVEL:
        printf(COLOR_RED);
        break;
    case WARNING_LEVEL:
        printf(COLOR_YELLOW);
        break;
    case INFO_LEVEL:
        printf(COLOR_NORMAL);
        break;
    case GOOD_LEVEL:
        printf(COLOR_GREEN);
        break;
    default:
        printf(COLOR_NORMAL);
        break;
    }
    printf("[%s] ", name);
    int nbcharprinted = vprintf(format, args);
    printf(COLOR_NORMAL);
    return nbcharprinted;
}