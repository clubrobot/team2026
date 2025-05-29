#include <Arduino.h>
#include <EEPROM.h>

#include "Codewheel.h"

/**
 * @brief Constructeur pour une roue codeuse
 * @param htim Timer utilisé par la roue codeuse
 * @warning Que pour STM32
 */
Codewheel::Codewheel(TIM_HandleTypeDef *htim){
	//Initialisation des valeurs avant le load
	m_currentCounter = 0;
	m_startCounter = 0;
	m_wheelRadius = 1 / (2 * M_PI);
	m_countsPerRev = 1000;
	m_htim = htim;
}

/**
 * @brief Remet à zero le counter de départ
 */
void Codewheel::reset(){
	m_startCounter = 0;
}

/**
 * @brief Met à jour le compteur
 * @warning Que pour STM32
 */
void Codewheel::update(){
	m_currentCounter = __HAL_TIM_GetCounter(m_htim);
}

/**
 * @brief Renvoie la distance parcourue par la roue codeuse
 * @return distance parcourue en mm
 */
float Codewheel::getTraveledDistance()
{
	return (float)(getCounter() - m_startCounter) / m_countsPerRev * (2.0 * M_PI * m_wheelRadius);
}

/**
 * @brief Renvoie la distance parcourue entre le dernier appel de restart
 * @return distance relative au dernier appel de restart
 */
float Codewheel::restart()
{
	float distance = getTraveledDistance();
	m_startCounter = m_currentCounter;
	return distance;
}


void Codewheel::load(int address)
{
	EEPROM.get(address, m_wheelRadius);  address += sizeof(m_wheelRadius);
	EEPROM.get(address, m_countsPerRev); address += sizeof(m_countsPerRev);
}

void Codewheel::save(int address)
{
	EEPROM.put(address, m_wheelRadius);
	address += sizeof(m_wheelRadius);
	EEPROM.put(address, m_countsPerRev);
	address += sizeof(m_countsPerRev);
}

/**
 * @brief Modifie la variable des current_points par révolution de la roue codeuse
 * @param countsPerRev point par révolution
 */
void Codewheel::setCountsPerRev(long countsPerRev)
{
	m_countsPerRev = countsPerRev;
}

/**
 * @brief Modifie le rayon de la roue codeuse
 * @param wheelRadius rayon de la roue codeuse en mm
 */
void Codewheel::setWheelRadius (float wheelRadius)
{
	m_wheelRadius = wheelRadius;
}