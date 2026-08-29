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

namespace cerveau::manual
{
    struct message
    {
        std::array<char, 2> data;
    };
    struct Control
    {
        float linSpeed;
        float angSpeed;

        float elevatorAngle;
        bool gripperOpen;
        uint8_t gripperRotate;
    };

    enum Identifiers : u_int8_t
    {
        negLinSpeed = 0b00000011,
        posLinSpeed = 0b00000010,

        posAngSpeed = 0b00000100,
        negAngSpeed = 0b00000101,

        elevatorAngle = 0b00001000,
        negElevatorAngle = 0b00001001,

        gripperOpen =   0b00010000,
        gripperRotateA = 0b00101000,
        gripperRotateB = 0b00100100,
        gripperRotateC = 0b00100010,
        gripperRotateD = 0b00100001,
    };

    enum Masks : u_int8_t
    {
        identifierMask = 0b00011111,
        valueMask = 0b01111111,
        fingerA = 0b00001000,
        fingerB = 0b00000100,
        fingerC = 0b00000010,
        fingerD = 0b00000001,
    };

    constexpr float maxValue = 127.0f;
    static Control control = {};
    static Control status = {};

    message get_command();
    void parse_command(const message& command);
    void execute_command(Wheeledbase::WheeledBase* wb);

    class ManualControlRunner : public PeriodicProcess
    {
        Wheeledbase::WheeledBase* wb;
    protected:
        void process(float timestep) override;
    public:
        void setWb(Wheeledbase::WheeledBase* wb) { this->wb = wb; }
    }

    static runner = ManualControlRunner();
}

#endif //TEAM2026_AUTOMATE_H
