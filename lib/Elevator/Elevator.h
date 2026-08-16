
//
// Created by Romain Pouvreau on 08/03/2026.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "../Wheeledbase/include/Controller/DifferentialController.h"

class AbstractAbsoluteEncoder
{
public:
    virtual ~AbstractAbsoluteEncoder()= default;

    /**
    *	@brief Calcul de la position angulaire.
    *
    * Méthode à implémenter, dont le rôle est de retourner la l'angle de l'encodeur.
    *
    * @return Position angulaire de l'encodeur en deg.
    */
    virtual float getAngle() = 0;


    /**
     * @brief Initialisation de l'encodeur
     */

    virtual void init() = 0;
};


class Elevator
{
public:
    Elevator(AbstractMotor& motor, AbstractAbsoluteEncoder& encoder): m_motor(motor), m_encoder(encoder){}

    /**
     * @breif Défini une position à atteindre
     *
     * @param angle position shouaité en deg
     */
    void setAngle(float angle) {m_angle = angle;};

    /**
    * @brief Calcul l'asservissement.
    */
    void task(void *pvParameters);


    /**
    * @brief Charge l'asservissement.
    *
     * Charge les pointeurs PID pour l'asservissement de DifferentialController.
     *
     * @param pid Asservissement angulaire.
     */
    void setPID(PID& pid){m_pid = &pid;}


protected:
    AbstractMotor& m_motor;
    AbstractAbsoluteEncoder& m_encoder;

    float m_angle; /*!< Angle à atteindre en deg. */

    PID* m_pid;
};


#endif //ELEVATOR_H
