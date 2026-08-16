/**
 *  @file main.cpp
 *  @ingroup core
 *  @brief Contient le code principal du robot.
 *
 *  %Point d'entrée du programme, contient notamment les fonctions d'initialisation (hal, freeRTOS). Une fois que tout est
 *  initialisé, lance les différents threads et passe le contrôle à FreeRTOS.
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "Wheeledbase.h"

#include <My_Clock.h>
#include <PrintfSupport.h>
#include <Logger.h>

#include "BournsACEncoder.h"
#include "DCMotor.h"
#include "DRV8876.h"
#include "Elevator.h"
#include "HazelnutGripper.h"
#include "variables_globales.h"
#include "LiquidCrystal.h"
#include "cerveau/Automate.h"
#include "ihm/ihm.h"
#include "wheeledbase/wb_thread.h"
#include "sensors/SensorsThread.h"



static LiquidCrystal lcd(PG15, PB4, PB8, PB5, PB9, PF3);

#define DEBUG 1

#if DEBUG && configUSE_TRACE_FACILITY
#include "trcRecorder.h"
#endif

#if not configUSE_TRACE_FACILITY && DEBUG
#ifndef ALREADY_WARNED
#define ALREADY_WARNED
#warning FreeRTOS config does not allow Trace Recording
#endif
#endif

#define TEST_NO_FREERTOS false //Ignore le FreeRTOS et se comporte comme un arduino classique

Logger main_logs = Logger("MAIN");
using namespace ihm;



/* TODO:
Valeurs servo limites  OK
Régler PID/Accel => Logger OK
Procédure démarrage Preque OK
Tache empiler
Tache banderole OK
check reset if vl53 are flshed !!!!!!!!!!!!!!
*/


//Setup de base



// Fonction d'initialisation des horloges
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {};

  // Supply configuration update enable
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  // Configure the main internal regulator output voltage
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /*
   * Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  // Initializes the CPU, AHB and APB buses clocks
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }
  // Initializes the peripherals clock
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_SDMMC | RCC_PERIPHCLK_ADC
                                             | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_USART16
                                             | RCC_PERIPHCLK_USART234578 | RCC_PERIPHCLK_I2C123
                                             | RCC_PERIPHCLK_SPI123 | RCC_PERIPHCLK_SPI45
                                             | RCC_PERIPHCLK_SPI6;
  PeriphClkInitStruct.PLL2.PLL2M = 4;
  PeriphClkInitStruct.PLL2.PLL2N = 10;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0.0;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
  PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_D3PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Spi6ClockSelection = RCC_SPI6CLKSOURCE_D3PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }
}


static HazelnutGripper::BournsACEncoder encoder(PA4, PB13, PB12, PE12, PC4, PA7, PA6, PA5);
static DRV8876 drv8876(PA9,PC8);
static DCMotor motor;
static PID pid;

void setup(){

    SystemClock_Config();  // Configuration de l'horloge

    DWT_Init(); //Très important

#if configUSE_TRACE_FACILITY && DEBUG
    xTraceEnable(TRC_START);
#endif
#if DEBUG
    PrintfSupport::begin(PRINTF_BAUD);
    main_logs.log(WARNING_LEVEL, "Debug enabled at %d baud\n", PRINTF_BAUD);

    main_logs.log(INFO_LEVEL, "Printing WheeledBase Params\n");
    //Wheeledbase::PRINT_PARAMS();
#endif
    match_started= true;
    auto wheeledbase = wb_setup();

#if TEST_NO_FREERTOS
    main_logs.log(WARNING_LEVEL,"Not using FreeRTOS\n");
    return;
#endif
  lcd.begin(20, 4);
  lcd.print("Hello Club Robot !");
  Logger::setLcdOutput(lcd);
  lcd.clear();

  SensorsThread::Init();


  drv8876.init();
  drv8876.attach(&motor);


  HazelnutGripper::Gripper::init();

  HazelnutGripper::GripperWire.begin();

  HazelnutGripper::Gripper::closeAll();

  HazelnutGripper::Gripper::setRotationAll(0);

  HazelnutGripper::Gripper::spreadFingers(0);

  /*
  delay(5000);

  HazelnutGripper::Gripper::closeAll();

  delay(5000);*/


  //pid a vide pid.setTunings(0.022,0.016,0.001);
  pid.setTunings(0.022,0.0,0.0);
  pid.setOutputLimits(-0.90,0.90);

  HazelnutGripper::Elevator::setPID(pid);

  encoder.init();

  HazelnutGripper::Elevator::init(&motor,&encoder);

  HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::HAUT);



  BaseType_t ret_gripper = xTaskCreate(
              &HazelnutGripper::Elevator::task,
              "Elevator",
              10000,
              nullptr,
              5,//Prio max
              &gripper_handle );
  if(ret_gripper!=pdPASS) {Error_Handler()}


/*

  HazelnutGripper::Gripper::init();

  HazelnutGripper::GripperWire.begin();

  HazelnutGripper::Gripper::closeAll();

  HazelnutGripper::Gripper::setRotationAll(0);
  delay(2000);


  HazelnutGripper::Gripper::openAll();

  delay(5000);

  HazelnutGripper::Gripper::closeAll();

  delay(5000);

  HazelnutGripper::Gripper::spreadFingers(180);

  delay(1000);

  HazelnutGripper::Gripper::setRotationAll(180);
  delay(2000);


  HazelnutGripper::Gripper::spreadFingers(0);

  delay(5000);

  HazelnutGripper::Gripper::openAll();


  encoder.init();

  printf("annngle :: %f\n",encoder.getAngle());

  HazelnutGripper::Elevator::init(&d,&encoder);


*/



    main_logs.log(GOOD_LEVEL,"Using FreeRTOS\n");
    //Setup FreeRTOS

    BaseType_t ret_wb = xTaskCreate(
                wb_loop,
                "Wheeledbase loop",
                10000,
                static_cast<void*>(&wheeledbase),
                5,//Prio max
                &hl_wb );
    if(ret_wb!=pdPASS) {Error_Handler()}


    BaseType_t ret_sens= xTaskCreate(
                 SensorsThread::Thread,
                "Sensors loop",
                 10000,
                 static_cast<void*>(&wheeledbase),
                 5,
                 &hl_sens );

     if(ret_sens!=pdPASS) {Error_Handler()}


    BaseType_t ret_robot = xTaskCreate(
                cerveau::automate::play_match,
                "Robot loop",
                10000,
                nullptr,
                5,
                &hl_robot);

    if(ret_robot!=pdPASS) {Error_Handler()}

    main_logs.log(GOOD_LEVEL,"Starting tasks\n");
    TaskStatus_t q;
    vTaskGetInfo(hl_robot, &q, pdTRUE, eInvalid);
    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    wheeledbase.leftWheel->setVelocity(0);
    wheeledbase.rightWheel->setVelocity(0);
    motor.setVelocity(0);
    main_logs.log(ERROR_LEVEL,"FreeRTOS crashed\n");
    Error_Handler();
}
float i=0;
void loop(){
}

