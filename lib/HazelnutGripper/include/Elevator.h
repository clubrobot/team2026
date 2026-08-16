
//
// Created by Romain Pouvreau on 08/03/2026.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "../Wheeledbase/include/Controller/DifferentialController.h"

namespace HazelnutGripper
{
    /**
     * @class AbstractAbsoluteEncoder
     * @brief Interface pour un encodeur de position absolue.
     * * Cette classe définit le contrat pour tout capteur capable de fournir
     * * une position angulaire absolue.
     */
    class AbstractAbsoluteEncoder
    {
    public:
        virtual ~AbstractAbsoluteEncoder() = default;

        /**
         * @brief Récupère la position angulaire actuelle.
         * @return Angle mesuré en degrés (deg).
         */
        virtual float getAngle() = 0;

        /**
         * @brief Initialise le matériel de l'encodeur.
         */
        virtual void init() = 0;
    };

    /**
     * @namespace Elevator
     * @brief Namespace gérant l'asservissement en position de l'ascenseur.
     * * L'Elevator coordonne un moteur et un encodeur via un correcteur PID
     * pour atteindre et maintenir une position angulaire précise.
     */
    namespace Elevator
    {
        inline AbstractMotor* m_motor = nullptr;            ///< Pointeur vers le moteur asservi.
        inline AbstractAbsoluteEncoder* m_encoder = nullptr; ///< Pointeur vers l'encodeur de retour.
        inline float m_currentAngle = 0.0f;
        inline float m_angleSetpoint = 0.0f; ///< Consigne de position angulaire (Setpoint) en degrés.
        inline PID* m_pid = nullptr;    ///< Correcteur PID utilisé pour le calcul de la vitesse.
        constexpr float m_maxAngle = 83;
        constexpr float m_minAngle = 160.312500;
        constexpr float m_maxRange = m_minAngle - m_maxAngle;

        enum elevatorHeight {
            BAS = 0,
            CAPTEURS = 10,
            HAUT = static_cast<int>(m_maxRange),
        };


        /**
         * @brief Initialise les périphériques de l'ascenseur.
         * * Lie le moteur et l'encodeur à la classe et calibre la position
         * cible initiale sur la position actuelle de l'ascenseur.
         * * @param motor Référence vers le driver du moteur.
         * @param encoder Référence vers le capteur de position.
         */
        void init(AbstractMotor* motor, AbstractAbsoluteEncoder* encoder);

        /**
         * @brief Définit la position cible à atteindre.
         * @param angle Position souhaitée en degrés (deg).
         */
        inline void setAngle(float angle) { m_angleSetpoint = m_minAngle - angle; }

        inline float getAngle() {return m_minAngle - m_angleSetpoint;}

        /**
         * @brief Tâche de calcul de l'asservissement (Boucle de contrôle).
         * * Lit l'encodeur, calcule l'erreur, applique le PID et commande le moteur.
         * Cette méthode est conçue pour être lancée comme une tâche FreeRTOS.
         * * @param pvParameters Paramètres de tâche (non utilisés, typiquement NULL).
         */
        [[noreturn]] void task(void *pvParameters);

        /**
         * @brief Configure le correcteur PID à utiliser pour l'asservissement.
         * @param pid Référence vers l'objet PID configuré.
         */
        inline void setPID(PID& pid) { m_pid = &pid; }

    };
}

#endif // ELEVATOR_H