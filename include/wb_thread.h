#ifndef WB_THREAD_H
#define WB_THREAD_H

#include "wb_const.h"

#include "DCMotor.h"
#include "Codewheel.h"
#include "Odometry.h"
#include "PID.h"
#include "VelocityController.h"
#include "PositionController.h"
#include "PurePursuit.h"
#include "TurnOnTheSpot.h"
#include "mathutils.h"

// Load the different modules

extern DCMotorsDriver driver;
extern DCMotor leftWheel;
extern DCMotor rightWheel;

extern TIM_HandleTypeDef htim23;//Right
extern TIM_HandleTypeDef htim24;//Left

extern Codewheel leftCodewheel;
extern Codewheel rightCodewheel;

extern Odometry odometry;

extern VelocityController velocityControl;
#if ENABLE_VELOCITYCONTROLLER_LOGS
extern VelocityControllerLogs controllerLogs;
#endif // ENABLE_VELOCITYCONTROLLER_LOGS

extern PID linVelPID;
extern PID angVelPID;

extern PositionController positionControl;

extern PurePursuit purePursuit;
extern TurnOnTheSpot turnOnTheSpot;

void wb_setup();
void wb_loop();

#endif //WB_THREAD_H
