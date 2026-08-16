/**
 *  @file wb_const.h
 *  @ingroup wheeledbase
 *  @ingroup core
 *  @brief Diverses constantes concernant la base roulante
 */

#ifndef __WB_CONST_H__
#define __WB_CONST_H__

#include <Wheeledbase.h>

//Really traveled distance > thought traveled distance -> decrease codewheels radius
//Really rotated angle > thought rotated angle         -> increase axle track
//Turn right when thinking moving forward              -> increase left codewheel radius
//Turn left when thinking moving forward               -> increase right codewheel radius


inline Wheeledbase::WBConstants wb_consts = {
    .LEFTWHEEL_RADIUS = 23.8125,
    .LEFTWHEEL_CONSTANT = 0.209380534*2,
    .LEFTWHEEL_MAXPWM = 1.0,
    .RIGHTWHEEL_RADIUS = 23.8125,
    .RIGHTWHEEL_CONSTANT = 0.209380534*2,
    .RIGHTWHEEL_MAXPWM = 1.0,
    .LEFTCODEWHEEL_COUNTSPERREV = 5000,
    .RIGHTCODEWHEEL_COUNTSPERREV = 5000,
    .LEFTCODEWHEEL_RADIUS = 22.734851011,
    .RIGHTCODEWHEEL_RADIUS = 22.734851011,

    .ODOMETRY_AXLETRACK = 207.5496406,
    .ODOMETRY_SLIPPAGE = 0,

    .VELOCITYCONTROL_AXLETRACK = 125.0,//201.5
    .VELOCITYCONTROL_MAXLINACC = 300,
    .VELOCITYCONTROL_MAXLINDEC = 125,
    .VELOCITYCONTROL_MAXANGACC = PI/2,
    .VELOCITYCONTROL_MAXANGDEC = PI/2,
    .VELOCITYCONTROL_SPINSHUTDOWN = false,

    /*---- LINEAR VELOCITIES PID  ----*/

    .LINVELPID_KP = 1.4,
    .LINVELPID_KI = 2.2,
    .LINVELPID_KD = 0.01,

    /*
    .LINVELPID_KP = 1.4,
    .LINVELPID_KI = 3.2,
    .LINVELPID_KD = 0,*/

    .LINVELPID_MINOUTPUT = -350,
    .LINVELPID_MAXOUTPUT = 350,

    /*---- ANGULAR VELOCITIES PID ----*/
    .ANGVELPID_KP = 3, //.5 3  0.8,
    .ANGVELPID_KI = 3,//.1 1.5   0.5,
    .ANGVELPID_KD = 0,

    .ANGVELPID_MINOUTPUT = -2*PI/3,
    .ANGVELPID_MAXOUTPUT = 2*PI/3,

    /*---- POSITION PID ----*/
    .POSITIONCONTROL_LINVELKP = 1,
    .POSITIONCONTROL_ANGVELKP = 1,

    .POSITIONCONTROL_LINVELMAX = 350,
    .POSITIONCONTROL_ANGVELMAX = PI/2,
    .POSITIONCONTROL_LINPOSTHRESHOLD = 1,
    .POSITIONCONTROL_ANGPOSTHRESHOLD = 0.008,
    .PUREPURSUIT_LOOKAHEAD = 30.0,
    .PUREPURSUIT_LOOKAHEADBIS = 40.0,

    // Timesteps
    .ODOMETRY_TIMESTEP = 20e-3,
    .PID_CONTROLLERS_TIMESTEP = 20e-3,
    .POSITIONCONTROL_TIMESTEP = 20e-3,

    // DC motors driver
    .LEFT_MOTOR_EN = PD1,
    .LEFT_MOTOR_PWM = PC6,
    .LEFT_MOTOR_DIR = PD3,
    .RIGHT_MOTOR_EN = PD0,
    .RIGHT_MOTOR_PWM = PC7,
    .RIGHT_MOTOR_DIR = PD2,
    .DRIVER_RESET = PC11,
    .DRIVER_FAULT = PC12,
};

#endif // __WB_CONST_H__