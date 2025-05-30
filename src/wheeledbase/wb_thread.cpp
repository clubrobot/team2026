#include <Arduino.h>
#include "wb_thread.h"

//Declare all modules
DCMotorsDriver driver;
DCMotor leftWheel;
DCMotor rightWheel;

TIM_HandleTypeDef htim23;//Right
TIM_HandleTypeDef htim24;//Left

Codewheel leftCodewheel(&htim23);
Codewheel rightCodewheel(&htim24);

Odometry odometry;

VelocityController velocityControl;
#if ENABLE_VELOCITYCONTROLLER_LOGS
VelocityControllerLogs controllerLogs;
#endif // ENABLE_VELOCITYCONTROLLER_LOGS

PID linVelPID;
PID angVelPID;

PositionController positionControl;

PurePursuit purePursuit;
TurnOnTheSpot turnOnTheSpot;

void write_default_params() {
    leftWheel.setWheelRadius(LEFTWHEEL_RADIUS_VALUE);
    leftWheel.setConstant(LEFTWHEEL_CONSTANT_VALUE);
    leftWheel.setMaxPWM(LEFTWHEEL_MAXPWM_VALUE);
    rightWheel.setWheelRadius(RIGHTWHEEL_RADIUS_VALUE);
    rightWheel.setConstant(RIGHTWHEEL_CONSTANT_VALUE);
    rightWheel.setMaxPWM(RIGHTWHEEL_MAXPWM_VALUE);

    leftCodewheel.setWheelRadius(LEFTCODEWHEEL_RADIUS_VALUE);
    leftCodewheel.setCountsPerRev(LEFTCODEWHEEL_COUNTSPERREV_VALUE);
    rightCodewheel.setWheelRadius(RIGHTCODEWHEEL_RADIUS_VALUE);
    rightCodewheel.setCountsPerRev(RIGHTCODEWHEEL_COUNTSPERREV_VALUE);

    odometry.setAxleTrack(ODOMETRY_AXLETRACK_VALUE);
    odometry.setSlippage(ODOMETRY_SPLIPPAGE_VALUE);

    velocityControl.setAxleTrack(VELOCITYCONTROL_AXLETRACK_VALUE);
    velocityControl.setMaxLinAcc(VELOCITYCONTROL_MAXLINACC_VALUE);
    velocityControl.setMaxLinDec(VELOCITYCONTROL_MAXLINDEC_VALUE);
    velocityControl.setMaxAngAcc(VELOCITYCONTROL_MAXANGACC_VALUE);
    velocityControl.setMaxAngDec(VELOCITYCONTROL_MAXANGDEC_VALUE);
    velocityControl.setSpinShutdown(VELOCITYCONTROL_SPINSHUTDOWN_VALUE);

    linVelPID.setTunings(LINVELPID_KP_VALUE, LINVELPID_KI_VALUE, LINVELPID_KD_VALUE);
    linVelPID.setOutputLimits(LINVELPID_MINOUTPUT_VALUE, LINVELPID_MAXOUTPUT_VALUE);

    angVelPID.setTunings(ANGVELPID_KP_VALUE, ANGVELPID_KI_VALUE, ANGVELPID_KD_VALUE);
    angVelPID.setOutputLimits(ANGVELPID_MINOUTPUT_VALUE, ANGVELPID_MAXOUTPUT_VALUE);

    positionControl.setVelLimits(POSITIONCONTROL_LINVELMAX_VALUE, POSITIONCONTROL_ANGVELMAX_VALUE);
    positionControl.setPosThresholds(POSITIONCONTROL_LINPOSTHRESHOLD_VALUE, POSITIONCONTROL_ANGPOSTHRESHOLD_VALUE);
    purePursuit.setLookAhead(PUREPURSUIT_LOOKAHEAD_VALUE);
    purePursuit.setLookAheadBis(PUREPURSUIT_LOOKAHEADBIS_VALUE);
}


void codewheels_setup(){
    //--------TIM23
    TIM_Encoder_InitTypeDef sConfig23 = {0};
    TIM_MasterConfigTypeDef sMasterConfig23 = {0};
    GPIO_InitTypeDef GPIO_InitStruct23 = {0};
    __HAL_RCC_TIM23_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**TIM23 GPIO Configuration
    PF6     ------> TIM23_CH1
    PF7     ------> TIM23_CH2
    */
    GPIO_InitStruct23.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct23.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct23.Pull = GPIO_NOPULL;
    GPIO_InitStruct23.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct23.Alternate = GPIO_AF13_TIM23;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct23);

    htim23.Instance = TIM23;
    htim23.Init.Prescaler = 0;
    htim23.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim23.Init.Period = 4294967295;
    htim23.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim23.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    sConfig23.EncoderMode = TIM_ENCODERMODE_TI1;
    sConfig23.IC1Polarity = TIM_ICPOLARITY_RISING;
    sConfig23.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig23.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig23.IC1Filter = 0;
    sConfig23.IC2Polarity = TIM_ICPOLARITY_RISING;
    sConfig23.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig23.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig23.IC2Filter = 0;

    if (HAL_TIM_Encoder_Init(&htim23, &sConfig23) != HAL_OK){
        Error_Handler();//Not good
    }
    sMasterConfig23.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig23.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim23, &sMasterConfig23) != HAL_OK){
        Error_Handler();//Not good
    }

    HAL_TIM_Encoder_Start_IT(&htim23, TIM_CHANNEL_ALL);

    //--------TIM24
    TIM_Encoder_InitTypeDef sConfig24 = {0};
    TIM_MasterConfigTypeDef sMasterConfig24 = {0};
    GPIO_InitTypeDef GPIO_InitStruct24 = {0};
    __HAL_RCC_TIM24_CLK_ENABLE();
    //__HAL_RCC_GPIOF_CLK_ENABLE(); Already enabled
    /**TIM24 GPIO Configuration
    PF11     ------> TIM24_CH1
    PF12     ------> TIM24_CH2
    */
    GPIO_InitStruct24.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct24.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct24.Pull = GPIO_NOPULL;
    GPIO_InitStruct24.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct24.Alternate = GPIO_AF14_TIM24;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct24);

    htim24.Instance = TIM24;
    htim24.Init.Prescaler = 0;
    htim24.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim24.Init.Period = 4294967295;
    htim24.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim24.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    sConfig24.EncoderMode = TIM_ENCODERMODE_TI1;
    sConfig24.IC1Polarity = TIM_ICPOLARITY_RISING;
    sConfig24.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig24.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig24.IC1Filter = 0;
    sConfig24.IC2Polarity = TIM_ICPOLARITY_RISING;
    sConfig24.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig24.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig24.IC2Filter = 0;

    if (HAL_TIM_Encoder_Init(&htim24, &sConfig24) != HAL_OK){
        Error_Handler();//Not good
    }
    sMasterConfig24.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig24.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim24, &sMasterConfig24) != HAL_OK){
        Error_Handler();//Not good
    }

    HAL_TIM_Encoder_Start_IT(&htim24, TIM_CHANNEL_ALL);

    rightCodewheel.m_htim = &htim23;
    rightCodewheel.m_tim = TIM23;
    leftCodewheel.m_htim = &htim24;
    leftCodewheel.m_tim = TIM24;
}

// Setup
void wb_setup(){
    //TODO once
    write_default_params();
    // DC motors wheels
    driver.attach(DRIVER_RESET, DRIVER_FAULT);
    driver.reset();

    leftWheel.attach(LEFT_MOTOR_EN, LEFT_MOTOR_PWM, LEFT_MOTOR_DIR);
    rightWheel.attach(RIGHT_MOTOR_EN, RIGHT_MOTOR_PWM, RIGHT_MOTOR_DIR);

    // Codewheels
    codewheels_setup();

    leftCodewheel.reset();
    rightCodewheel.reset();

    // Odometry
    odometry.setCodewheels(leftCodewheel, rightCodewheel);
    odometry.setTimestep(ODOMETRY_TIMESTEP);
    odometry.enable();

    // Engineering control
    velocityControl.setWheels(leftWheel, rightWheel);
    velocityControl.setPID(linVelPID, angVelPID);
    velocityControl.disable();

    // const float maxLinVel = min(leftWheel.getMaxVelocity(), rightWheel.getMaxVelocity());
    //const float maxAngVel = min(leftWheel.getMaxVelocity(), rightWheel.getMaxVelocity()) * 2 / VELOCITYCONTROL_AXLETRACK_VALUE;

    //linVelPID.setOutputLimits(-maxLinVel, maxLinVel);
    //angVelPID.setOutputLimits(-maxAngVel, maxAngVel);

#if ENABLE_VELOCITYCONTROLLER_LOGS
    controllerLogs.setController(velocityControl);
    controllerLogs.setTimestep(VELOCITYCONTROLLER_LOGS_TIMESTEP);
    controllerLogs.enable();
#endif // VELOCITYENABLE_CONTROLLER_LOGS

    // Position control
    positionControl.setTimestep(POSITIONCONTROL_TIMESTEP);
    positionControl.disable();

    //purePursuit.load(PUREPURSUIT_ADDRESS);
}

void wb_loop(void *pvParameters){
for(;;) {
    // Update odometry
    if (odometry.update()){
        positionControl.setPosInput(*odometry.getPosition());
        velocityControl.setInputs(odometry.getLinVel(), odometry.getAngVel());
    }
    // Compute trajectory
    if (positionControl.update())
    {
        float linVelSetpoint = positionControl.getLinVelSetpoint();
        float angVelSetpoint = positionControl.getAngVelSetpoint();
        velocityControl.setSetpoints(linVelSetpoint, angVelSetpoint);
    }
        // Integrate engineering control
#if ENABLE_VELOCITYCONTROLLER_LOGS
        if (velocityControl.update())
            controllerLogs.update();
#else
        velocityControl.update();
#endif // ENABLE_VELOCITYCONTROLLER_LOGS
}
}
