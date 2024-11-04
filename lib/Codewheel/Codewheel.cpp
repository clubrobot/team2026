#include <Arduino.h>
#include <EEPROM.h>

#include "Codewheel.h"

Codewheel::Codewheel(TIM_HandleTypeDef *htim){
	//Initialisation des valeurs avant le load
	m_currentCounter = 0;
	m_startCounter = 0;
	m_wheelRadius = 1 / (2 * M_PI);
	m_countsPerRev = 1000;
	m_htim = htim;
}

void Codewheel::reset(){
	m_startCounter = 0;

}

void Codewheel::update(){
	m_currentCounter = __HAL_TIM_GetCounter(m_htim);
}

float Codewheel::getTraveledDistance()
{
	return (float)(getCounter() - m_startCounter) / m_countsPerRev * (2.0 * M_PI * m_wheelRadius);
}

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

void Codewheel::setCountsPerRev(long countsPerRev)
{
	m_countsPerRev = countsPerRev;
}

void Codewheel::setWheelRadius (float wheelRadius)
{
	m_wheelRadius = wheelRadius;
}