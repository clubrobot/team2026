//
// Created by awing on 10/05/2026.
//

/**
 * @file Automate.h
 * @ingroup strategy
 * @ingroup core
 * @brief Contient le code nécessaire pour jouer un match.
 */

#ifndef TEAM2026_AUTOMATE_H
#define TEAM2026_AUTOMATE_H

#include "Strategie.h"
#include "Wheeledbase.h"

/**
 * @namespace cerveau::automate
 * @brief Contient le code nécessaire pour jouer un match.
 */
namespace cerveau::automate {
    //TODO: (2026-06-25) Dedup le logger avec celui du NS cerveau
    inline auto automateLogger = Logger("AUTOMATE");
    enum s_Team {
        BLEU,
        JAUNE,
    };
    typedef s_Team Team;
    inline Team ourTeam;

    void init(Team team, Wheeledbase::WheeledBase& wheeledbase);
    void play_match(void *pvParameters);
}

#endif //TEAM2026_AUTOMATE_H
