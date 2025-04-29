#include "AX12.h"
#include "Dynamixel.h"	
#include <Arduino.h>

/**
 * @brief Ouvre le port serial défini par le param rtx du bus d'AX12
 * @param baud Baud du bus d'AX12, mettre AX12_BAUDRATE par default
 * @param rtx  Pins du port serial
 */
void AX12::SerialBegin(long baud, unsigned char rtx){
	Dynamixel.begin(baud, rtx);
}

/**
 * @brief Ouvre le port serial défini dans Dynamixel.cpp du bus d'AX12
 * @param baud Baud du bus d'AX12, mettre AX12_BAUDRATE par default
 */
void AX12::SerialBegin(long baud){
	Dynamixel.begin(baud);
}

/**
 * @brief Fini la comm avec le bus d'AX12
 */
void AX12::end(){
	Dynamixel.end();
}

/**
 * @brief Déclare un AX12 dans le bus d'AX12
 * @param id Identifiant de l'AX12
 */
void AX12::attach(unsigned char id){
	m_id = id;
}

/**
 * @brief Enlève la déclaration de l'AX12
 */
void AX12::detach(){
	m_id = -1;
}

/**
 * @brief Ping l'AX12 pour voir s'il est dans le bus
 * @return 1 si l'AX12 est dans le bus 0 sinon
 */
int AX12::ping(){
	return Dynamixel.ping(m_id);
}

/**
 * @brief Déclare une nouvelle ID à l'AX12
 * @param newID nouvelle ID de l'AX12
 * @return Code d'erreure
 */
int AX12::setID(unsigned char newID){
	return Dynamixel.setID(m_id, newID);
}

/**
 * @brief Change le baud d'un AX12 parmis le bus d'AX12
 * @param baud Nouveau baud
 * @return Code d'erreur
 */
int AX12::setBD(long baud){
	return Dynamixel.setBD(m_id, baud);
}

/**
 * @brief Bouge l'AX12 à un position définie
 * @warning enlève le EndlessMode
 * @param Position Pos en ° à atteindre
 * @return Code d'erreur
 */
int AX12::move(float Position){
	if(m_endlessMode){
		setEndlessMode(OFF);
	}
	int pos = min((float) 1023,Position/300*1023);
	return Dynamixel.move(m_id, pos);
}

/**
 * @brief Bouge l'AX12 à un position & vitesse définie
 * @warning enlève le EndlessMode
 * @param Position Pos à atteindre
 * @param speed Vitesse de l'AX12
 * @return Code d'erreur
 */
int AX12::moveSpeed(float Position, float speed){
	if(m_endlessMode){
		setEndlessMode(OFF);
	}
	int pos = min((float) 1023,Position/300*1023);
	return Dynamixel.moveSpeed(m_id, pos, speed);
}

/**
 * @brief Met ou non le mode sans fin de l'AX12
 * @param Status 1 pour EndlessMode 0 sinon
 * @return Code d'erreur
 */
int AX12::setEndlessMode(bool Status){
	m_endlessMode = Status;
	return Dynamixel.setEndless(m_id, Status);
}

/**
 * @brief Fait tourner l'AX12 en mode Moteur à une vitesse définie
 * @param Speed vitesse de l'AX12
 * @return Code d'erreur
 */
int AX12::turn(int Speed){
	if(Speed>0){
		int spd = min(1023, Speed);
		return Dynamixel.turn(m_id, 0, spd);
	}
	else{
		int spd = max(-1023, Speed);
		return Dynamixel.turn(m_id, 1, abs(spd));
	}
}

/**
 * @brief Programme la prochaine action réalisée quand action sera appelé
 * @param Position Pos de l'action
 * @return code de l'erreur
 */
int AX12::Nextmove(float Position) {
	int pos = min((float) 1023,Position/300*1023);
	return Dynamixel.moveRW(m_id, pos);
}

/**
 * @brief Programme la prochaine action réalisée quand action sera appelé
 * @param Position Pos de l'action
 * @param Speed vitesse de l'action
 * @return code de l'erreur
 */
int AX12::NextmoveSpeed(float Position, float Speed){
	int pos = min((float) 1023, Position/300*1023);
	return Dynamixel.moveSpeedRW(m_id, pos, Speed);
}

/**
 * @brief déclenche l'action pour tout les AX12
 */
void AX12::action(){
	Dynamixel.setEndless(254, OFF);
	Dynamixel.action();
}

/**
 * @brief Définie la temparture limite de l'AX12
 * @param Temperature température limite
 * @return code d'erreur
 */
int AX12::setTempLimit(unsigned char Temperature){
	return Dynamixel.setTempLimit(m_id, Temperature);
}

/**
 * @brief Définie les bornes de rotations
 * @param CW Borne sens anti-trigo en °
 * @param CCW Borne sens trigo en °
 * @return code d'erreur
 */
int AX12::setAngleLimit(float CW, float CCW){
	int CWLimit = min((float) 1023, CW/300*1023);
	int CCWLimit = min((float) 1023, CCW/300 *1023);
	return Dynamixel.setAngleLimit(m_id, CWLimit, CCWLimit);
}

/**
 * @brief Définie les limites de tension de l'AX12
 * @param DVoltage Volts Min
 * @param UVoltage Volts Max
 * @return code d'erreur
 */
int AX12::setVoltageLimit(unsigned char DVoltage, unsigned char UVoltage){
	return Dynamixel.setVoltageLimit(m_id, DVoltage*10, UVoltage*10);
}

/**
 * @brief Définie la limite MAX de couple
 * @param MaxTorque limite max de couple le max étant 1023
 * @return code d'erreur
 */
int AX12::setMaxTorque(int MaxTorque){
	return Dynamixel.setMaxTorque(m_id, MaxTorque);
}

/**
 * @brief Définie dans la RAM la limite MAX de couple
 * @warning Cette limite sera oubliée au prochains redémarrage
 * @param MaxTorque limite max de couple le max étant 1023
 * @return code d'erreur
 */
int AX12::setMaxTorqueRAM(int MaxTorque){
	return Dynamixel.setMaxTorqueRAM(m_id, MaxTorque);
}

int AX12::setSRL(unsigned char SRL){
	return Dynamixel.setSRL(m_id, SRL);
}
	
int AX12::setRDT(unsigned char RDT){
	return Dynamixel.setRDT(m_id, RDT);
}
	
int AX12::setLEDAlarm(unsigned char LEDAlarm){
	return Dynamixel.setLEDAlarm(m_id, LEDAlarm);
}
	
int AX12::setShutdownAlarm(unsigned char SALARM){
	return Dynamixel.setShutdownAlarm(m_id, SALARM);
}

int AX12::setCMargin(unsigned char CWCMargin, unsigned char CCWCMargin){
	return Dynamixel.setCMargin(m_id, CWCMargin, CCWCMargin);
}
	
int AX12::setCSlope(unsigned char CWCSlope, unsigned char CCWCSlope){
	return Dynamixel.setCSlope(m_id, CWCSlope, CCWCSlope);
}
	
int AX12::setPunch(int Punch){
	return Dynamixel.setPunch(m_id, Punch);	
}

/**
 * @brief Regarde si l'AX12 bouge de lui même
 * @return 1 si l'AX12 bouge 0 sinon
 */
int AX12::moving(){
	return Dynamixel.moving(m_id);
}
	
int AX12::lockRegister(){
	return Dynamixel.lockRegister(m_id);
}

/**
 * @brief Renvoie l'action programmée pour le prochain appel d'action
 * @return L'action programmée
 */
int AX12::savedMove(){
	return Dynamixel.RWStatus(m_id);
}

/**
 * @brief Lis la température de l'AX12
 * @return température
 */
int AX12::readTemperature(){
	return Dynamixel.readTemperature(m_id);
}

/**
 * @brief Lis la tension de l'AX12
 * @return La tension de l'AX12
 */
float AX12::readVoltage(){
	return Dynamixel.readVoltage(m_id)/10;
}

/**
 * @brief Renvoie la position actuelle de l'AX12
 * @return Pos de l'AX12
 */
float AX12::readPosition(){
	float pos = (float)(Dynamixel.readPosition(m_id)) *300 /1023;
	return pos;
}

/**
 * @brief Renvoie la vitesse de l'AX12
 * @return Vit de l'AX12
 */
float AX12::readSpeed(){
	if(m_endlessMode){
		return Dynamixel.readSpeed(m_id);
	}
	else{
		return Dynamixel.readSpeed(m_id) /1023*114 ;
	}
}

/**
 * @brief Couple la vitesse de l'AX12
 * @return Couple de l'AX12
 */
int AX12::readTorque(){
	int torque = Dynamixel.readLoad(m_id);
	if(torque <=1023){
		return map(torque, 0, 1023, 0, -1023);
	}
	else{
		return map(torque, 1024, 2047, 0, 1023);
	}
}
	
int AX12::hold(bool Status){
	m_holding = Status;
	return Dynamixel.torqueStatus(m_id, Status);
}

bool AX12::isHolding(){
	return m_holding;
}

/**
 * @brief Modifie l'allumage de la LED
 * @param Status 1 si allumé 0 sinon
 * @return code d'erreur
 */
int AX12::led(bool Status){
	return Dynamixel.ledStatus(m_id, Status);
}
