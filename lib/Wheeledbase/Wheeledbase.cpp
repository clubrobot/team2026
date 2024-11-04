//
// Created by boris on 28/10/2024.
//

#include "Wheeledbase.h"

// Instructions


void Wheeledbase::DISABLE(){
	velocityControl.disable();
	positionControl.disable();
	leftWheel .setVelocity(0);
	rightWheel.setVelocity(0);
}

void Wheeledbase::GOTO_DELTA(float dx, float dy){
	purePursuit.reset();
	positionControl.disable();

	Position initial_pos =  odometry.getPosition();

	Position target_pos;
	target_pos.x = initial_pos.x + dx*cos(initial_pos.theta)    + dy*-1*sin(initial_pos.theta);
	target_pos.y = initial_pos.y + dx*sin(initial_pos.theta) + dy*cos(initial_pos.theta);

	target_pos.theta = atan2(target_pos.y-initial_pos.y,target_pos.x-initial_pos.x);
	int direction;

	initial_pos.theta = inrange(initial_pos.theta,-M_PI,M_PI);

	if (fabs(inrange(target_pos.theta - initial_pos.theta,-M_PI,M_PI))<(M_PI/2))
	{
		direction = PurePursuit::FORWARD;
	}else{
		direction = PurePursuit::BACKWARD;
	}

	purePursuit.setDirection((PurePursuit::Direction) direction);
	purePursuit.addWaypoint(PurePursuit::Waypoint(initial_pos.x, initial_pos.y));
	purePursuit.addWaypoint(PurePursuit::Waypoint(target_pos.x, target_pos.y));

	purePursuit.setFinalAngle(target_pos.theta);

	positionControl.setPosSetpoint(Position(target_pos.x, target_pos.y, target_pos.theta + direction * M_PI));

	// Enable PurePursuit controller
	velocityControl.enable();
	positionControl.setMoveStrategy(purePursuit);
	positionControl.enable();
}

void Wheeledbase::SET_OPENLOOP_VELOCITIES(float leftWheelVel, float rightWheelVel){
	velocityControl.disable();
	positionControl.disable();
	leftWheel .setVelocity(leftWheelVel);
	rightWheel.setVelocity(rightWheelVel);
}

void Wheeledbase::GET_CODEWHEELS_COUNTERS(float *leftCodewheelCounter, float *rightCodewheelCounter){
	*leftCodewheelCounter  = leftCodewheel. getCounter();
	*rightCodewheelCounter = rightCodewheel.getCounter();
}

void Wheeledbase::SET_VELOCITIES(float linVelSetpoint, float angVelSetpoint){
	positionControl.disable();
	velocityControl.enable();
	velocityControl.setSetpoints(linVelSetpoint, angVelSetpoint);
}

void Wheeledbase::RESET_PUREPURSUIT()
{
	purePursuit.reset();
	positionControl.disable();
}

void Wheeledbase::START_PUREPURSUIT(uint8_t direction, float finalAngle)
{
	// Setup PurePursuit
	purePursuit.setFinalAngle(finalAngle);

	switch (direction){
	case 0: purePursuit.setDirection(PurePursuit::FORWARD); break;
	case 1: purePursuit.setDirection(PurePursuit::BACKWARD); break;
	}

	// Compute final setpoint
	const PurePursuit::Waypoint wp0 = purePursuit.getWaypoint(purePursuit.getNumWaypoints() - 2);
	const PurePursuit::Waypoint wp1 = purePursuit.getWaypoint(purePursuit.getNumWaypoints() - 1);
	positionControl.setPosSetpoint(Position(wp1.x, wp1.y, atan2(wp1.y - wp0.y, wp1.x - wp0.x) + direction * M_PI));
	Serial.println("A");
	// Enable PurePursuit controller
	velocityControl.enable();
	positionControl.setMoveStrategy(purePursuit);
	positionControl.enable();
}

void Wheeledbase::ADD_PUREPURSUIT_WAYPOINT(float x, float y){
	// Queue waypoint
	Serial.println("B");
	purePursuit.addWaypoint(PurePursuit::Waypoint(x, y));
}

void Wheeledbase::START_TURNONTHESPOT(bool dir, float theta)
{
	Position posSetpoint = odometry.getPosition();
	float initTheta = posSetpoint.theta;
	posSetpoint.theta = theta;
	float angPosSetpoint = inrange((posSetpoint.theta - initTheta), -M_PI, M_PI);
	velocityControl.enable();
	positionControl.setPosSetpoint(posSetpoint);
	if(dir){
		if(angPosSetpoint>0) turnOnTheSpot.setDirection(TurnOnTheSpot::CLOCK);
		else                 turnOnTheSpot.setDirection(TurnOnTheSpot::TRIG);
	}
	else{
		if(angPosSetpoint>0) turnOnTheSpot.setDirection(TurnOnTheSpot::TRIG);
		else                 turnOnTheSpot.setDirection(TurnOnTheSpot::CLOCK);
	}
	positionControl.setMoveStrategy(turnOnTheSpot);
	positionControl.enable();
}

void Wheeledbase::START_TURNONTHESPOT_DIR(bool dir, float theta)
{
	Position posSetpoint = odometry.getPosition();
	posSetpoint.theta = theta;
	velocityControl.enable();
	positionControl.setPosSetpoint(posSetpoint);
	if (dir){
		turnOnTheSpot.setDirection(TurnOnTheSpot::TRIG);
	}
	else{
		turnOnTheSpot.setDirection(TurnOnTheSpot::CLOCK);
	}
	positionControl.setMoveStrategy(turnOnTheSpot);
	positionControl.enable();
}

/**
* ret:
0b00 si pas reached pas spin urgency (0)
0b01 si reached (1)
0b10 si spin urgency (2)
0b11 si les deux (3)
*/
uint8_t Wheeledbase::POSITION_REACHED(){
	bool positionReached = positionControl.getPositionReached() && positionControl.isEnabled();
	bool spinUrgency = !velocityControl.isEnabled();
	uint8_t ret = 0;
    ret = ret|positionReached;
    ret = ret | (spinUrgency<<1);
    return ret;
}

void Wheeledbase::GET_VELOCITIES_WANTED(float *linOutput, float *angOutput, bool spin)
{

	if(spin){
		*linOutput = velocityControl.getLinOutput();
		*angOutput = velocityControl.getAngOutput();
	}else{
		*linOutput = velocityControl.getLinSpinGoal();
		*angOutput = velocityControl.getAngSpinGoal();
	}
}


void Wheeledbase::SET_POSITION(float x, float y, float theta){
	odometry.setPosition(x, y, theta);
}

void Wheeledbase::GET_POSITION(float *x, float *y, float *theta){
	const Position& pos = odometry.getPosition();

	*x = pos.x;
 	*y = pos.y;
 	*theta = pos.theta;
}

void Wheeledbase::GET_VELOCITIES(float *linVel, float *angVel){
	*linVel = odometry.getLinVel();
	*angVel = odometry.getAngVel();
}

void Wheeledbase::SET_PARAMETER_VALUE(byte paramID, float value){
	switch (paramID){
	case LEFTWHEEL_RADIUS_ID:
		leftWheel.setWheelRadius(value);
		break;
	case LEFTWHEEL_CONSTANT_ID:
		leftWheel.setConstant(value);
		break;
	case LEFTWHEEL_MAXPWM_ID:
		leftWheel.setMaxPWM(value);
		break;
	case RIGHTWHEEL_RADIUS_ID:
		rightWheel.setWheelRadius(value);
		break;
	case RIGHTWHEEL_CONSTANT_ID:
		rightWheel.setConstant(value);
		break;
	case RIGHTWHEEL_MAXPWM_ID:
		rightWheel.setMaxPWM(value);
		break;
	case LEFTCODEWHEEL_RADIUS_ID:
		leftCodewheel.setWheelRadius(value);
		break;
	case LEFTCODEWHEEL_COUNTSPERREV_ID:
		leftCodewheel.setCountsPerRev(static_cast<long>(value));
		break;
	case RIGHTCODEWHEEL_RADIUS_ID:
		rightCodewheel.setWheelRadius(value);
		break;
	case RIGHTCODEWHEEL_COUNTSPERREV_ID:
		rightCodewheel.setCountsPerRev(static_cast<long>(value));
		break;
	case ODOMETRY_AXLETRACK_ID:
		odometry.setAxleTrack(value);
		break;
	case ODOMETRY_SLIPPAGE_ID:
		odometry.setSlippage(value);
		break;
	case VELOCITYCONTROL_AXLETRACK_ID:
		velocityControl.setAxleTrack(value);
		break;
	case VELOCITYCONTROL_MAXLINACC_ID:
		velocityControl.setMaxLinAcc(value);
		break;
	case VELOCITYCONTROL_MAXLINDEC_ID:
		velocityControl.setMaxLinDec(value);
		break;
	case VELOCITYCONTROL_MAXANGACC_ID:
		velocityControl.setMaxAngAcc(value);
		break;
	case VELOCITYCONTROL_MAXANGDEC_ID:
		velocityControl.setMaxAngDec(value);
		break;
	case VELOCITYCONTROL_SPINSHUTDOWN_ID:
		velocityControl.setSpinShutdown((bool)value);
		break;
	case LINVELPID_KP_ID:
		linVelPID.setTunings(value, linVelPID.getKi(), linVelPID.getKd());
		break;
	case LINVELPID_KI_ID:
		linVelPID.setTunings(linVelPID.getKp(), value, linVelPID.getKd());
		break;
	case LINVELPID_KD_ID:
		linVelPID.setTunings(linVelPID.getKp(), linVelPID.getKi(), value);
		break;
	case LINVELPID_MINOUTPUT_ID:
		linVelPID.setOutputLimits(value, linVelPID.getMaxOutput());
		break;
	case LINVELPID_MAXOUTPUT_ID:
		linVelPID.setOutputLimits(linVelPID.getMinOutput(), value);
		break;
	case ANGVELPID_KP_ID:
		angVelPID.setTunings(value, angVelPID.getKi(), angVelPID.getKd());
		break;
	case ANGVELPID_KI_ID:
		angVelPID.setTunings(angVelPID.getKp(), value, angVelPID.getKd());
		break;
	case ANGVELPID_KD_ID:
		angVelPID.setTunings(angVelPID.getKp(), angVelPID.getKi(), value);
		break;
	case ANGVELPID_MINOUTPUT_ID:
		angVelPID.setOutputLimits(value, angVelPID.getMaxOutput());
		break;
	case ANGVELPID_MAXOUTPUT_ID:
		angVelPID.setOutputLimits(angVelPID.getMinOutput(), value);
		break;
	case POSITIONCONTROL_LINVELKP_ID:
		positionControl.setVelTunings(value, positionControl.getAngVelKp());
		break;
	case POSITIONCONTROL_ANGVELKP_ID:
		positionControl.setVelTunings(positionControl.getLinVelKp(), value);
		break;
	case POSITIONCONTROL_LINVELMAX_ID:
		positionControl.setVelLimits(value, positionControl.getAngVelMax());
		break;
	case POSITIONCONTROL_ANGVELMAX_ID:
		positionControl.setVelLimits(positionControl.getLinVelMax(), value);
		break;
	case POSITIONCONTROL_LINPOSTHRESHOLD_ID:
		positionControl.setPosThresholds(value, positionControl.getAngPosThreshold());
		break;
	case POSITIONCONTROL_ANGPOSTHRESHOLD_ID:
		positionControl.setPosThresholds(positionControl.getLinPosThreshold(), value);
		break;
	case PUREPURSUIT_LOOKAHED_ID:
		purePursuit.setLookAhead(value);
		break;
	case PUREPURSUIT_LOOKAHEADBIS_ID:
		purePursuit.setLookAheadBis(value);
		break;
	}

}

void SAVE_PARAMETERS()
{
	leftWheel.save(LEFTWHEEL_ADDRESS);
	rightWheel.save(RIGHTWHEEL_ADDRESS);
	leftCodewheel.save(LEFTCODEWHEEL_ADDRESS);
	rightCodewheel.save(RIGHTCODEWHEEL_ADDRESS);
	odometry.save(ODOMETRY_ADDRESS);
	velocityControl.save(VELOCITYCONTROL_ADDRESS);
	linVelPID.save(LINVELPID_ADDRESS);
	angVelPID.save(ANGVELPID_ADDRESS);
	positionControl.save(POSITIONCONTROL_ADDRESS);
	purePursuit.save(PUREPURSUIT_ADDRESS);
}

void Wheeledbase::GET_PARAMETER_VALUE()
{
	byte id = talking.read<byte>();
	if(id==LEFTWHEEL_RADIUS_ID){
		talking.write<float>(leftWheel.getWheelRadius());
		}
	else if(id== LEFTWHEEL_CONSTANT_ID){
		talking.write<float>(leftWheel.getConstant());
		}
	else if(id== LEFTWHEEL_MAXPWM_ID){
		talking.write<float>(leftWheel.getMaxPWM());
		}

	else if(id== RIGHTWHEEL_RADIUS_ID){
		talking.write<float>(rightWheel.getWheelRadius());
		}
	else if(id== RIGHTWHEEL_CONSTANT_ID){
		talking.write<float>(rightWheel.getConstant());
		}
	else if(id== RIGHTWHEEL_MAXPWM_ID){
		talking.write<float>(rightWheel.getMaxPWM());
		}

	else if(id== LEFTCODEWHEEL_RADIUS_ID){
		talking.write<float>(leftCodewheel.getWheelRadius());
		}
	else if(id== LEFTCODEWHEEL_COUNTSPERREV_ID){
		talking.write<long>(leftCodewheel.getCountsPerRev());
		}

	else if(id== RIGHTCODEWHEEL_RADIUS_ID){
		talking.write<float>(rightCodewheel.getWheelRadius());
		}
	else if(id== RIGHTCODEWHEEL_COUNTSPERREV_ID){
		talking.write<long>(rightCodewheel.getCountsPerRev());
		}

	else if(id== ODOMETRY_AXLETRACK_ID){
		talking.write<float>(odometry.getAxleTrack());
		}
	else if(id== ODOMETRY_SLIPPAGE_ID){
		talking.write<float>(odometry.getSlippage());
		}

	else if(id== VELOCITYCONTROL_AXLETRACK_ID){
		talking.write<float>(velocityControl.getAxleTrack());
		}
	else if(id== VELOCITYCONTROL_MAXLINACC_ID){
		talking.write<float>(velocityControl.getMaxLinAcc());
		}
	else if(id== VELOCITYCONTROL_MAXLINDEC_ID){
		talking.write<float>(velocityControl.getMaxLinDec());
		}
	else if(id== VELOCITYCONTROL_MAXANGACC_ID){
		talking.write<float>(velocityControl.getMaxAngAcc());
		}
	else if(id== VELOCITYCONTROL_MAXANGDEC_ID){
		talking.write<float>(velocityControl.getMaxAngDec());
		}
	else if(id== VELOCITYCONTROL_SPINSHUTDOWN_ID){
		talking.write<byte>(velocityControl.getSpinShutdown());
		}

	else if(id== LINVELPID_KP_ID){
		talking.write<float>(linVelPID.getKp());
		}
	else if(id== LINVELPID_KI_ID){
		talking.write<float>(linVelPID.getKi());
		}
	else if(id== LINVELPID_KD_ID){
		talking.write<float>(linVelPID.getKd());
		}
	else if(id== LINVELPID_MINOUTPUT_ID){
		talking.write<float>(linVelPID.getMinOutput());
		}
	else if(id== LINVELPID_MAXOUTPUT_ID){
		talking.write<float>(linVelPID.getMaxOutput());
		}

	else if(id== ANGVELPID_KP_ID){
		talking.write<float>(angVelPID.getKp());
		}
	else if(id== ANGVELPID_KI_ID){
		talking.write<float>(angVelPID.getKi());
		}
	else if(id== ANGVELPID_KD_ID){
		talking.write<float>(angVelPID.getKd());
		}
	else if(id== ANGVELPID_MINOUTPUT_ID){
		talking.write<float>(angVelPID.getMinOutput());
		}
	else if(id== ANGVELPID_MAXOUTPUT_ID){
		talking.write<float>(angVelPID.getMaxOutput());
		}

	else if(id== POSITIONCONTROL_LINVELKP_ID){
		talking.write<float>(positionControl.getLinVelKp());
		}
	else if(id== POSITIONCONTROL_ANGVELKP_ID){
		talking.write<float>(positionControl.getAngVelKp());
		}
	else if(id== POSITIONCONTROL_LINVELMAX_ID){
		talking.write<float>(positionControl.getLinVelMax());
		}
	else if(id== POSITIONCONTROL_ANGVELMAX_ID){
		talking.write<float>(positionControl.getAngVelMax());
		}
	else if(id== POSITIONCONTROL_LINPOSTHRESHOLD_ID){
		talking.write<float>(positionControl.getLinPosThreshold());
		}
	else if(id== POSITIONCONTROL_ANGPOSTHRESHOLD_ID){
		talking.write<float>(positionControl.getAngPosThreshold());
		}

	else if(id== PUREPURSUIT_LOOKAHED_ID){
		talking.write<float>(purePursuit.getLookAhead());
		}
	else if(id== PUREPURSUIT_LOOKAHEADBIS_ID){
		talking.write<float>(purePursuit.getLookAheadBis());
		}

	talking.endTranfert();
}

void RESET_PARAMETERS()
{
	leftWheel.load(LEFTWHEEL_ADDRESS);
	rightWheel.load(RIGHTWHEEL_ADDRESS);
	leftCodewheel.load(LEFTCODEWHEEL_ADDRESS);
	rightCodewheel.load(RIGHTCODEWHEEL_ADDRESS);
	odometry.load(ODOMETRY_ADDRESS);
	velocityControl.load(VELOCITYCONTROL_ADDRESS);
	linVelPID.load(LINVELPID_ADDRESS);
	angVelPID.load(ANGVELPID_ADDRESS);
	positionControl.load(POSITIONCONTROL_ADDRESS);
	purePursuit.load(PUREPURSUIT_ADDRESS);
}

void PRINT_PARAMS(){
	/*Serial.println(F(" LEFTWHEEL_RADIUS_ID:")); Serial.println(leftWheel.getWheelRadius());
	Serial.println(F(" LEFTWHEEL_CONSTANT_ID:")); Serial.println(leftWheel.getConstant());
	Serial.println(F(" LEFTWHEEL_MAXPWM_ID:")); Serial.println(leftWheel.getMaxPWM());
	Serial.println(F(" RIGHTWHEEL_RADIUS_ID:")); Serial.println(rightWheel.getWheelRadius());
	Serial.println(F(" RIGHTWHEEL_CONSTANT_ID:")); Serial.println(rightWheel.getConstant());
	Serial.println(F(" RIGHTWHEEL_MAXPWM_ID:")); Serial.println(rightWheel.getMaxPWM());
	Serial.println(F(" LEFTCODEWHEEL_RADIUS_ID:")); Serial.println(leftCodewheel.getWheelRadius());
	Serial.println(F(" LEFTCODEWHEEL_COUNTSPERREV_ID:")); Serial.println(leftCodewheel.getCountsPerRev());
	Serial.println(F(" RIGHTCODEWHEEL_RADIUS_ID:")); Serial.println(rightCodewheel.getWheelRadius());
	Serial.println(F(" RIGHTCODEWHEEL_COUNTSPERREV_ID:")); Serial.println(rightCodewheel.getCountsPerRev());
	Serial.println(F(" ODOMETRY_AXLETRACK_ID:")); Serial.println(odometry.getAxleTrack());
	Serial.println(F(" ODOMETRY_SLIPPAGE_ID:")); Serial.println(odometry.getSlippage());
	Serial.println(F(" VELOCITYCONTROL_AXLETRACK_ID:")); Serial.println(velocityControl.getAxleTrack());
	Serial.println(F(" VELOCITYCONTROL_MAXLINACC_ID:")); Serial.println(velocityControl.getMaxLinAcc());
	Serial.println(F(" VELOCITYCONTROL_MAXLINDEC_ID:")); Serial.println(velocityControl.getMaxLinDec());
	Serial.println(F(" VELOCITYCONTROL_MAXANGACC_ID:")); Serial.println(velocityControl.getMaxAngAcc());
	Serial.println(F(" VELOCITYCONTROL_MAXANGDEC_ID:")); Serial.println(velocityControl.getMaxAngDec());
	Serial.println(F(" VELOCITYCONTROL_SPINSHUTDOWN_ID:")); Serial.println(velocityControl.getSpinShutdown());
	Serial.println(F(" LINVELPID_KP_ID:")); Serial.println(linVelPID.getKp());
	Serial.println(F(" LINVELPID_KI_ID:")); Serial.println(linVelPID.getKi());
	Serial.println(F(" LINVELPID_KD_ID:")); Serial.println(linVelPID.getKd());
	Serial.println(F(" LINVELPID_MINOUTPUT_ID:")); Serial.println(linVelPID.getMinOutput());
	Serial.println(F(" LINVELPID_MAXOUTPUT_ID:")); Serial.println(linVelPID.getMaxOutput());
	Serial.println(F(" ANGVELPID_KP_ID:")); Serial.println(angVelPID.getKp());
	Serial.println(F(" ANGVELPID_KI_ID:")); Serial.println(angVelPID.getKi());
	Serial.println(F(" ANGVELPID_KD_ID:")); Serial.println(angVelPID.getKd());
	Serial.println(F(" ANGVELPID_MINOUTPUT_ID:")); Serial.println(angVelPID.getMinOutput());
	Serial.println(F(" ANGVELPID_MAXOUTPUT_ID:")); Serial.println(angVelPID.getMaxOutput());
	Serial.println(F(" POSITIONCONTROL_LINVELKP_ID:")); Serial.println(positionControl.getLinVelKp());
	Serial.println(F(" POSITIONCONTROL_ANGVELKP_ID:")); Serial.println(positionControl.getAngVelKp());
	Serial.println(F(" POSITIONCONTROL_LINVELMAX_ID:")); Serial.println(positionControl.getLinVelMax());
	Serial.println(F(" POSITIONCONTROL_ANGVELMAX_ID:")); Serial.println(positionControl.getAngVelMax());
	Serial.println(F(" POSITIONCONTROL_LINPOSTHRESHOLD_ID:")); Serial.println(positionControl.getLinPosThreshold());
	Serial.println(F(" POSITIONCONTROL_ANGPOSTHRESHOLD_ID:")); Serial.println(positionControl.getAngPosThreshold());
	Serial.println(F(" PUREPURSUIT_LOOKAHED_ID:")); Serial.println(purePursuit.getLookAhead());
	Serial.println(F(" PUREPURSUIT_LOOKAHEADBIS_ID:")); Serial.println(purePursuit.getLookAheadBis());*/
}