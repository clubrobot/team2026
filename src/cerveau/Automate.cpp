//
// Created by awing on 10/05/2026.
//

#include "Automate.h"
#include "Automate.h"

#include "FreeRTOS.h"
#include "Killer.h"
#include "variables_globales.h"
#include "Wheeledbase.h"
#include "FreeRTOS/Source/include/task.h"
#include "ihm/ihm.h"
#include "Geogebra.h"
#include "include/Types.h"

void procedure_demarrage(Wheeledbase::WheeledBase& wheeledbase) {

    //cerveau::automate::Team team;
    cerveau::automate::automateLogger.log(INFO_LEVEL,"Le robot est armé!\n");

    //Detect tirette
    pinMode(PD11,OUTPUT);

    digitalWrite(PD11,1);
    HazelnutGripper::Gripper::spreadFingers(0);
    HazelnutGripper::Gripper::setRotationAll(0);
#if LCD_OUTPUT
    ihm::ihmLogger.log(SCREEN_LEVEL, "Bienvenue !");
#endif
    bool etat=false;
    bool t = false;
    while (!ihm::etat_bleu() && !ihm::etat_jaune()) {
        ihm::led_rouge(etat);
        digitalWrite(PD11,t);
        t = !t;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    while(ihm::etat_tirette()){vTaskDelay(pdMS_TO_TICKS(100));}
    while (!ihm::etat_tirette()){vTaskDelay(pdMS_TO_TICKS(100));}
    ihm::ihmLogger.log(SCREEN_LEVEL, "Lets go !");

    BaseType_t ret_gripper = xTaskCreate(
            &killer::killer_loop,
            "Elevator",
            10000,
            nullptr,
            5,//Prio max
            &killer_handle );
    if(ret_gripper!=pdPASS) {Error_Handler()}
}

void cerveau::automate::init(const Team team, Wheeledbase::WheeledBase& wheeledbase) {
    if (team == BLEU) {
        strategie::start = positions_bleu[Depart_B];
        strategie::generateBlueStrat();
        //strategie::stratDeSecoursBleu();
    } else {
        strategie::start = positions_jaune[Depart_J];
        strategie::generateYellowStrat();
        //strategie::stratDeSecoursJaune();
    }
    Wheeledbase::setPosition(&wheeledbase, &strategie::start);
}




/**
 * Parse a command string into a Control struct.
 * @param control the current Control struct to fill with parsed values.
 * @param command The command string to parse.
 * @return The parsed Control struct.
 *
 * command format:
 *   - First character: identifier (e.g., 'L' for linear speed, 'A' for angular speed, etc.) should be lower than 128
 *   - Second character: value | 128 meaning the first bit is reserved for Serial alignment purposes, rest is data
 */
void cerveau::manual::parse_command(const message& command)
{
    const char identifier = command.data[0];
    char value = command.data[1];
    value = value & valueMask;
    value /= maxValue;

    switch (identifier)
    {
    case posLinSpeed:
        control.linSpeed = static_cast<float>(value);
        break;
    case negLinSpeed:
        control.linSpeed = static_cast<float>(-value);
        break;
    case posAngSpeed:
        control.angSpeed = static_cast<float>(value);
        break;
    case negAngSpeed:
        control.angSpeed = static_cast<float>(-value);
        break;
    case elevatorAngle:
        control.elevatorAngle += static_cast<float>(value);
        break;
    case negElevatorAngle:
        control.elevatorAngle -= static_cast<float>(value);
        break;
    case gripperOpen:
        control.gripperOpen = static_cast<bool>(value);
        break;
    case gripperRotateA:
        control.gripperRotate &= ~fingerA;
        control.gripperRotate |= (value * 255) & fingerA;
        break;
    case gripperRotateB:
        control.gripperRotate &= ~fingerB;
        control.gripperRotate |= (value * 255) & fingerB;
        break;
    case gripperRotateC:
        control.gripperRotate &= ~fingerC;
        control.gripperRotate |= (value * 255) & fingerC;
        break;
    case gripperRotateD:
        control.gripperRotate &= ~fingerD;
        control.gripperRotate |= (value * 255) & fingerD;
        break;
    default:
        automate::automateLogger.log(ERROR_LEVEL, "Unknown command 0x%x", command);
        break;
    }

}

void cerveau::manual::execute_command(Wheeledbase::WheeledBase* wb)
{
    Wheeledbase::setVelocities(wb, control.linSpeed, control.angSpeed);
    status.linSpeed = control.linSpeed;
    status.angSpeed = control.angSpeed;
    map(control.elevatorAngle, 0.0f, 1.0f, HazelnutGripper::Elevator::BAS, HazelnutGripper::Elevator::HAUT);
    HazelnutGripper::Elevator::setAngle(control.elevatorAngle);
    status.elevatorAngle = control.elevatorAngle;
    if (control.gripperOpen != status.gripperOpen)
    {
        HazelnutGripper::Gripper::spreadFingers(180);
        if (control.gripperOpen)
        {
            HazelnutGripper::Gripper::openAll();
        }
        else
        {
            HazelnutGripper::Gripper::closeAll();
        }
        status.gripperOpen = control.gripperOpen;
        HazelnutGripper::Gripper::spreadFingers(0);
    }
    if (control.gripperRotate != status.gripperRotate)
    {
        HazelnutGripper::Gripper::spreadFingers(180);
        for (int i = 0; i < 4; i++)
        {
            HazelnutGripper::Gripper::getFinger(i).setAngle(1, (control.gripperRotate & (1 << i)) * 180);
        }
        HazelnutGripper::Gripper::spreadFingers(0);
        status.gripperRotate = control.gripperRotate;
    }
}

cerveau::manual::message cerveau::manual::get_command()
{
    if (Serial.available() >= 2)
    {
        if (const auto first = static_cast<uint8_t>(Serial.read()); (first & reservedMask) == 0)
        {
            const auto second = static_cast<uint8_t>(Serial.read());
            if ((second & reservedMask) != 0)
            {
                return message{{static_cast<char>(first), static_cast<char>(second)}};
            }
            if (Serial.available() >= 1)
            {
                if (const auto third = static_cast<uint8_t>(Serial.read()); (third & reservedMask) != 0)
                {
                    return message{{static_cast<char>(second), static_cast<char>(third)}};
                }
            }
        }
    }
    return message{{0, 0}};

}

void cerveau::manual::ManualControlRunner::process(float timestep)
{
    execute_command(this->wb);
}

void cerveau::automate::play_match(void *pvParameters) {
    auto *wheeledbase = static_cast<Wheeledbase::WheeledBase*>(pvParameters);
    procedure_demarrage(*wheeledbase);
    manual::runner.setWb(wheeledbase);
    manual::Control control = {};
    automateLogger.log(INFO_LEVEL, "Manual control started");
    while (true)
    {
        if (auto command = manual::get_command(); command.data[0] != 0)
        {
            manual::parse_command(command);
        }
        manual::runner.update();
    }
    vTaskDelete(nullptr);
}
