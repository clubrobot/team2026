#ifndef __WB_CONST_H__
#define __WB_CONST_H__

#include <Arduino.h>

// Timesteps
#define ODOMETRY_TIMESTEP         20e-3 // s
#define PID_CONTROLLERS_TIMESTEP  20e-3 // s
#define POSITIONCONTROL_TIMESTEP  50e-3 // s

// DC motors driver
//TODO: Redo pinout
#define LEFT_MOTOR_EN    6
#define LEFT_MOTOR_PWM   3
#define LEFT_MOTOR_DIR   5
#define RIGHT_MOTOR_EN   9
#define RIGHT_MOTOR_PWM 11
#define RIGHT_MOTOR_DIR 10
#define DRIVER_RESET    12
#define DRIVER_FAULT    A7

// Codewheel
//Voir le setup des encoedeurs pour les constantes

#endif // __WB_CONST_H__
