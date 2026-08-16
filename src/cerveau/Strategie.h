//
// Created by awing on 10/05/2026.
//

/**
 * @file Strategie.h
 * @ingroup strategy
 * @ingroup core
 * @brief Contient les diverses stratégies que le robot peut executer
 */

#ifndef TEAM2026_STRATEGIE_H
#define TEAM2026_STRATEGIE_H

#include "Elevator.h"
#include "Grafcet.h"
#include "HazelnutGripper.h"
#include "Logger.h"
#include "Components/Odometry.h"
#include "Geogebra.h"

#ifndef ELEVATOR_IN_POS
#define ELEVATOR_IN_POS() (fabs(HazelnutGripper::Elevator::m_currentAngle - HazelnutGripper::Elevator::m_angleSetpoint) < 5)
#endif

/**
 * @namespace cerveau
 * @brief Contient les fonctions et variables nécessaires pour gérer la stratégie du robot
 */
namespace cerveau {
    /// Le logger à utiliser par les composants de la stratégie
    inline auto stratLogger = Logger("STRATEGIE");
}

/**
 * @namespace cerveau::strategie
 * @brief Contient les fonctions et variables nécessaires pour gérer la stratégie du robot
 */
namespace cerveau::strategie {
    inline Grafcet::ActionNode* yellowStartingNode = {};
    inline Grafcet::ActionNode* bleuStartingNode = {};
    inline auto* strat = new Grafcet::StateMachine();

    void generateBlueStrat();
    void generateYellowStrat();

    void stratDeSecoursBleu();
    void stratDeSecoursJaune();

    //checkers


    inline Position start = {};
    inline const Position blueStart;
    inline const Position yellowStart;
}


#endif //TEAM2026_STRATEGIE_H
