#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     HTSMUX2,        sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C2_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     inLeft,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     inRight,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     liftRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C1_1,    bananaServo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    gateBack,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    hookFront,            tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    hookRight,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    hookLeft,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)

#include "util.h"
#include "lift.h"
#include "autonomous3.h"
#include "autonomousf.h"

task main()
{
	initializeRobot();
	wait1Msec(500);
	rampCLine(false, 20);

}
