#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C2_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     inLeft,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     inRight,       tmotorTetrix, openLoop)
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "util.h"
#include "lift.h"
#include "autonomous3.h"

const tMUXSensor HTANG = msensor_S3_1;
const tMUXSensor Sonar = msensor_S3_2;

//RAMP AUTONOMOUS

void initializeRobot(){
	calibrateGyro();
	nMotorEncoder[liftLeft] = 0;		//reset encoder
	hook(true);			//reset servos
	banana(false);
	gate(false);
	servo[hookFront] = 254;
	//RESET SERVOS
	return;
}

task main(){
	int degrees;						//used for degrees calculation
	int initAng;						//used for angle sensor calcs
	int inches = 50;				//inches needed to move on first movement
	int speed = 30;					//speed going down the ramp
	float lastTime = 0;				//used for dt calculation
	float dt = 0;					//dt for integration
	float g_val = 0;				//gyro value in degrees per second
	float currPos = 0;				//current turn position

	initializeRobot();		//reset servos

	/* CALIBRATE GYRO */
	int gyro_zero = 0;
	for (int i = 0; i < 10; i++) {
		gyro_zero += SensorValue[gyro];
		wait1Msec(100);
	}
	gyro_zero /= 10;

	/* END CALIBRATE GYRO */

	//waitForStart();

	/* LIFT LIFT BEFORE MOVING OFF RAMP */
	liftMan(0);
	wait1Msec(200);
	liftMan(2);


	//drive backwards off the ramp

	/*DETERMINE ANGLE FOR ANGLE SENSOR */
	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]


	/*INITIALIZE CLOCK */
	lastTime = nSysTime;

	/*GO DOWN RAMP WHILE MONITORING DISTANCE AND ANGLE */
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		motor[leftDrive] = -speed;
		motor[rightDrive] = -speed;
		writeDebugStreamLine("accumulated angle: %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));

		g_val = SensorValue[gyro] - gyro_zero;
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		//integration end

		writeDebugStreamLine("rotated %f", currPos);
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

	wait1Msec(100);

	driveBackwardDist(25, 100);

	driveBackwardDist(10, 20);

	hook(false);
	liftMove(SIXTY_LIFT);
	wait1Msec(1000);
	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);
	liftMove(500);

	turnEuler(180, 50, true);

	driveForwardDist(14, 50);

	servo[hookFront] = 58;

	wait1Msec(700);

	turnEuler(30, 40, false);

	driveBackwardDist(105, 100);

	turnEuler(60, 50, false);

	driveBackwardDist(10,50);

	liftMove(RESET);

	/*
	turnEuler(30, 50, false);

	driveForwardDist(80,100);

	turnEuler(180, 50, false);

	liftMove(RESET);

	*/

	//keep driving
	//driveBackward(1000);
	//stop infront of the tube67
	//driveStop();
	//hook the tube
	//hook(false);
	//raise the arm
	//liftMove(SIXTY_LIFT, true);
	//open the gate
	//turn
	//turnEuler(35, 35, false);
	//drive forward to the goal
	//driveForward(4000);

}
