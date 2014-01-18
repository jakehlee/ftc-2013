#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     irLeft,         sensorI2CCustom)
#pragma config(Sensor, S3,     irRight,        sensorI2CCustom)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     rotator,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftTread,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     rightTread,    tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    extender,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    flagExtender,         tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-irseeker-v2.h"
#include "lib/event.h" // I have no idea where waitForStart() is declared....
#include "lib/timing.h"

#define DRIVE_SPEED 50
#define TURN_SPEED 75
#define QUARTER_TURN_TIME 800

void calibrateGyro();
void turnRight(float degrees);
void turnLeft(float degrees);

float gyroZero;

task main() {
	waitForStart();

	long timeForward;

	// Set the sensor's DSP mode
	while(true) {
		if (HTIRS2setDSPMode(irRight, DSP_600))
			break;
	}

	calibrateGyro();

	ClearTimer(T1);

	// Raise the arm
	motor[rotator] = 100;
	wait1Msec(2750);
	motor[rotator] = 0;

	// Drive forward until we get a sensor reading of 8
	motor[leftDrive] = DRIVE_SPEED;
	motor[rightDrive] = DRIVE_SPEED;
	while (true) {
		writeDebugStreamLine("%d", HTIRS2readACDir(irRight));
		if (time1[T1] > 10000) {
			PlaySound(soundException);
			StopAllTasks();
		} else if (HTIRS2readACDir(irRight) == 8) {
			// Stop driving forward, time to rotate
			timeForward = time1[T1];
			break;
		}
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

	// Turn 90 degrees to the right
	turnRight(80);

	// Eject the block
	motor[leftTread] = -60;
	motor[rightTread] = -60;
	wait1Msec(3000);
	motor[leftTread] = 0;
	motor[rightTread] = 0;

	// Raise the arm some more
	motor[rotator] = 100;
	wait1Msec(500);
	motor[rotator] = 0;

	// Turn back 90 degrees
	turnLeft(80);

	// Drive back to the wall
	motor[leftDrive] = -DRIVE_SPEED;
	motor[rightDrive] = -DRIVE_SPEED;
	wait1Msec(timeForward);
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

	// Turn right again
	turnRight(90);

	// Drive forward
	motor[leftDrive] = 100;
	motor[rightDrive] = 100;
	wait1Msec(1000);
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

	turnLeft(55);
	motor[leftDrive] = 100;
	motor[rightDrive] = 100;
	wait1Msec(2000);
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}

void calibrateGyro() {
	gyroZero = 0;

	for (int i = 0; i < 10; i++) {
		gyroZero += SensorValue[gyro];
		wait1Msec(100);
	}
	gyroZero /= 10;
}

void turnRight(float degrees) {
	float turned = 0;

	wait1Msec(1000);
	resetTimeDelta();
	getTimeDelta();
	motor[leftDrive] = TURN_SPEED;
	motor[rightDrive] = -TURN_SPEED;

	while(abs(turned) < degrees) {
		turned += (SensorValue[gyro] - gyroZero) * getTimeDelta() / 1000.0;
	}

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}

void turnLeft(float degrees) {
	float turned = 0;

	wait1Msec(1000);
	resetTimeDelta();
	getTimeDelta();
	motor[leftDrive] = -TURN_SPEED;
	motor[rightDrive] = TURN_SPEED;

	while(abs(turned) < degrees) {
		turned += (SensorValue[gyro] - gyroZero) * getTimeDelta() / 1000.0;
	}

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}