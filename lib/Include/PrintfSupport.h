//
// Created by boris on 23/01/2025.
//

#ifndef PRINTFSUPPORT_H
#define PRINTFSUPPORT_H

#include <Arduino.h>
#include <stdio.h>

#define PRINTF_SERIAL Serial
#define PRINTF_BAUD 115200

namespace PrintfSupport {
    void begin(uint baud);
}

inline void PrintfSupport::begin(uint baud) {
    PRINTF_SERIAL.begin(baud);
}


int __io_putchar(int ch){
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART1 and Loop until the end of transmission */
    PRINTF_SERIAL.write(ch);

    return ch;
}


#endif //PRINTFSUPPORT_H
