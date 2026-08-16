#include <Arduino.h>
#include "wb_thread.h"

#include "DRV8844.h"
#include "Components/Codewheel.h"
#include "Controller/VelocityController.h"
#include "Controller/PositionController.h"

TIM_HandleTypeDef htim23; //Right
TIM_HandleTypeDef htim24; //Left

void codewheels_setup()
{
    //--------TIM23
    TIM_Encoder_InitTypeDef sConfig23 = {0};
    TIM_MasterConfigTypeDef sMasterConfig23 = {0};
    GPIO_InitTypeDef GPIO_InitStruct23 = {0};
    __HAL_RCC_TIM23_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStruct23.Pin = GPIO_PIN_6;
    GPIO_InitStruct23.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct23.Pull = GPIO_NOPULL;
    GPIO_InitStruct23.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct23.Alternate = GPIO_AF13_TIM23;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct23);

    GPIO_InitStruct23.Pin = GPIO_PIN_13;
    GPIO_InitStruct23.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct23.Pull = GPIO_NOPULL;
    GPIO_InitStruct23.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct23.Alternate = GPIO_AF13_TIM23;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct23);

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

    if (HAL_TIM_Encoder_Init(&htim23, &sConfig23) != HAL_OK)
    {
        Error_Handler(); //Not good
    }
    sMasterConfig23.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig23.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim23, &sMasterConfig23) != HAL_OK)
    {
        Error_Handler(); //Not good
    }

    HAL_TIM_Encoder_Start_IT(&htim23, TIM_CHANNEL_ALL);

    //--------TIM24
    TIM_Encoder_InitTypeDef sConfig24 = {0};
    TIM_MasterConfigTypeDef sMasterConfig24 = {0};
    GPIO_InitTypeDef GPIO_InitStruct24 = {0};
    __HAL_RCC_TIM24_CLK_ENABLE();

    GPIO_InitStruct24.Pin = GPIO_PIN_11 | GPIO_PIN_12;
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
    sConfig24.IC1Polarity = TIM_ICPOLARITY_FALLING;
    sConfig24.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig24.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig24.IC1Filter = 0;
    sConfig24.IC2Polarity = TIM_ICPOLARITY_RISING;
    sConfig24.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig24.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig24.IC2Filter = 0;

    if (HAL_TIM_Encoder_Init(&htim24, &sConfig24) != HAL_OK)
    {
        Error_Handler(); //Not good
    }
    sMasterConfig24.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig24.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim24, &sMasterConfig24) != HAL_OK)
    {
        Error_Handler(); //Not good
    }

    HAL_TIM_Encoder_Start_IT(&htim24, TIM_CHANNEL_ALL);

}

// Setup
Wheeledbase::WheeledBase wb_setup()
{
    auto driver = std::make_unique<DRV8844>(wb_consts.LEFT_MOTOR_EN, wb_consts.LEFT_MOTOR_DIR, wb_consts.LEFT_MOTOR_PWM, wb_consts.RIGHT_MOTOR_EN,
               wb_consts.RIGHT_MOTOR_DIR, wb_consts.RIGHT_MOTOR_PWM, wb_consts.DRIVER_FAULT, wb_consts.DRIVER_RESET);
    auto leftWheel = std::make_unique<WheelMotor>();
    auto rightWheel = std::make_unique<WheelMotor>();

    auto leftTimer = std::make_unique<STM32HALTimer>(&htim24);
    auto rightTimer = std::make_unique<STM32HALTimer>(&htim23);

    auto leftCodewheel = std::make_unique<Codewheel>(std::move(leftTimer));
    auto rightCodewheel = std::make_unique<Codewheel>(std::move(rightTimer));

    auto odometry = std::make_unique<Odometry>();

    auto velocityControl = std::make_unique<VelocityController>();
    auto positionControl = std::make_unique<PositionController>();

    auto linPID = std::make_unique<PID>();
    auto angPID = std::make_unique<PID>();

    Wheeledbase::WheeledBase wb = Wheeledbase::WheeledBase(
        std::move(driver),
        std::move(leftWheel),
        std::move(rightWheel),
        std::move(leftCodewheel),
        std::move(rightCodewheel),
        std::move(odometry),
        std::move(velocityControl),
        std::move(positionControl),
        std::move(linPID),
        std::move(angPID),
        wb_consts,
        [&]() { codewheels_setup(); }
    );
    return wb;
}

#define SMOOTHING_FACTOR 0.2

float smoothLinVel = 0;
float smoothAngVel = 0;

void wb_loop(void *pvParameters){
    auto *wb = static_cast<Wheeledbase::WheeledBase*>(pvParameters);
    Wheeledbase::run(wb, []() {
        vTaskDelay(pdMS_TO_TICKS(10));
    });

}
