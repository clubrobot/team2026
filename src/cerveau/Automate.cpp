//
// Created by awing on 10/05/2026.
//

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

    cerveau::automate::Team team;
    cerveau::automate::automateLogger.log(INFO_LEVEL,"Le robot est armé!\n");

    //Detect tirette
    pinMode(PD11,OUTPUT);

    digitalWrite(PD11,1);
    HazelnutGripper::Gripper::spreadFingers(0);
    HazelnutGripper::Gripper::setRotationAll(0);
#if LCD_OUTPUT
    ihm::ihmLogger.log(SCREEN_LEVEL, "Team ?");
#endif
    bool etat=false;
    bool t = false;
    while (!ihm::etat_bleu() && !ihm::etat_jaune()) {
        ihm::led_rouge(etat);
        digitalWrite(PD11,t);
        t = !t;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    if (ihm::etat_bleu()) {
        digitalWrite(PD11, 0);
        cerveau::automate::automateLogger.log(INFO_LEVEL,"Equipe bleue détectée\n");
        team = cerveau::automate::BLEU;
        Logger::sameLine(" Bleu");
    } else {
        digitalWrite(PD11, 0);
        cerveau::automate::automateLogger.log(INFO_LEVEL,"Equipe jaune détectée\n");
        team = cerveau::automate::JAUNE;
        Logger::sameLine(" Jaune");
    }
    cerveau::automate::init(team, wheeledbase);
    cerveau::automate::ourTeam = team;
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

void cerveau::automate::play_match(void *pvParameters) {
    auto *wheeledbase = static_cast<Wheeledbase::WheeledBase*>(pvParameters);
    procedure_demarrage(*wheeledbase);
    //while (true) {
    //    for (int i = 0; i < 4; ++i) {
    //        HazelnutGripper::GripperFinger *finger = &HazelnutGripper::Gripper::getFinger(i);
    //        finger->setSensingMode(HazelnutGripper::OperationMode::Continuous);
    //        while (!finger->hasNewColorData()) {
    //            vTaskDelay(pdMS_TO_TICKS(20));
    //        }
    //        auto [clear, red, green, blue] = finger->getColor();
    //        printf("Finger %d - Clear: %d, Red: %d, Green: %d, Blue: %d\n", i, clear, red, green, blue);
    //        vTaskDelay(pdMS_TO_TICKS(50));
    //    }
    //    vTaskDelay(pdMS_TO_TICKS(100));
    //}
    strategie::strat->execute();
    vTaskDelete(nullptr);

    //Wheeledbase::SET_OPENLOOP_VELOCITIES(100,0);



    /*

    HazelnutGripper::Gripper::closeAll();

    HazelnutGripper::Gripper::setRotationAll(0);

    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached())
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    Wheeledbase::GOTO_DELTA(400, 0, true);
    HazelnutGripper::Elevator::setAngle(10);
    while (abs(HazelnutGripper::Elevator::getAngle() - 10) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    printf("Reading colors\n");
    vTaskDelay(pdMS_TO_TICKS(2000));

    printf("Reading color ends\n");
    HazelnutGripper::Elevator::setAngle(20);
    HazelnutGripper::Gripper::openAll();
    Wheeledbase::GOTO_DELTA(50, 0, true);

    printf("Waiting for fingers\n");
    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached() || abs(HazelnutGripper::Elevator::getAngle() - 20) > 3)
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }


    printf("New angle\n");
    HazelnutGripper::Elevator::setAngle(0);
    while (abs(HazelnutGripper::Elevator::getAngle()) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
    HazelnutGripper::Gripper::closeAll();

    vTaskDelay(pdMS_TO_TICKS(1000));
    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached())
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    HazelnutGripper::Elevator::setAngle(60);

    while (abs(HazelnutGripper::Elevator::getAngle() - 60) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    Wheeledbase::TURNTO_DELTA(PI/2);

    HazelnutGripper::Gripper::spreadFingers(180);

    vTaskDelay(pdMS_TO_TICKS(1000));

    HazelnutGripper::Gripper::getFinger(1).setAngle(1,180);
    HazelnutGripper::Gripper::getFinger(3).setAngle(1,180);


    vTaskDelay(pdMS_TO_TICKS(2000));


    HazelnutGripper::Gripper::spreadFingers(0);

    HazelnutGripper::Elevator::setAngle(0);
    while (abs(HazelnutGripper::Elevator::getAngle() - 0) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
    HazelnutGripper::Gripper::openAll();

    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached())
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    HazelnutGripper::Elevator::setAngle(60);

    while (abs(HazelnutGripper::Elevator::getAngle() - 53) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    HazelnutGripper::Gripper::closeAll();*/
    vTaskDelete(nullptr);
}
