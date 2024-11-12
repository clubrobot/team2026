#ifndef __CODEWHEEL_H__
#define __CODEWHEEL_H__

#include "NonCopyable.h"
#include "Odometry.h"
#include "EEPROM.h"

#include <math.h>

/** class Codewheel
 *  \brief Fait la passerelle entre les roues codeuses et le stm32
 *  \author Boris HILKENS
 *	Cette classe permet de récupérer les tics des roues codeuses à travers le timer du STM32.
 * 	
 */

class Codewheel : private NonCopyable, public AbstractCodewheel{
public:

	Codewheel(TIM_HandleTypeDef *htim);

	long getCounter(){update(); return m_currentCounter;}

	/**
	 * @brief Donne le nombre de tics par tour courant.
	 * 
	 * @return long Nombre de tics par tour.
	 */
	long getCountsPerRev(){return m_countsPerRev;}

	/**
	 * @brief Donne le rayon de la roue en mm
	 * 
	 * @return float rayon en mm.
	 */
	float getWheelRadius(){return m_wheelRadius;}
	
	/**
	 * @brief Set le nombre de tics par tour.
	 * 
	 * @param countsPerRev nb de tics par tour.
	 */
	void setCountsPerRev(long countsPerRev);

	/**
	 * @brief Set le rayon en mm de la roue.
	 * 
	 * @param wheelRadius rayon en mm.
	 */
	void setWheelRadius (float wheelRadius);

	/**
	 * @brief Réinitialise le compteur à 0.
	 * 
	 * Cette méthode peut rendre caduque le prochain Codewheel::getTraveledDistance.
	 */
	void reset();

	/**
	 * @brief Donne la distance parcouru.
	 * 
	 * Cette méthode donne la distance parcouru par la roue depuis le dernier Codewheel::reset ou Codewheel::restart.
	 * @return float 
	 */
	float getTraveledDistance();

	/**
	 * @brief Donne la distance parcouru et reset le compteur.
	 * 
	 * Cette méthode appel la méthode Codewheel::getTravemedDistance avant de mettre à jour le compteur de l'arduino (pas du compteur (puce elec)).
	 * 
	 * @return float 
	 */
	float restart();

	/**
	 * @brief Charge les données de l'EEPROM avec l'offset.
	 * 
	 * @param address Offset à utiliser pour lire dans l'EEPROM.
	 */
	void load(int address);
	
	/**
	 * @brief Sauvegarde les constantes actuelles dans l'EEPROM
	 * 
	 * @param address Offset à utiliser pour ecrire dans l'EEPROM.
	 */
	void save(int address);

protected:

	/**
	 * @brief Récupère le nombre de tics stoqués dans le compteur.
	 * 
	 */
	void update();

	long m_currentCounter; //!< Tic courant.
	long m_startCounter;//!< Tic depuis le dernier reset

	float m_wheelRadius; //!< Rayon de la roue codeuse en  mm
	long m_countsPerRev;   //!<  Nombre de tics par tour de roue.

	TIM_HandleTypeDef *m_htim;
	TIM_TypeDef *m_tim;
};

#endif // __ROTARYENCODER_H__
