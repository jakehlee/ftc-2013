#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C2_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     liftRight,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    bananaServo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    gateBack,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
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

/*
Copyright (c) 2014 Jake Lee, Team 4790

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

//TOWER AUTONOMOUS
int sonarvalue = 0;
void autoStraight();
void autoDiag();
void autoDiagR();
void autoHoriz();

//if the end goal is straight ahead
void autoStraight(){
	liftMan(0);
	wait1Msec(200);
	liftMan(2);
	wait1Msec(10);
	driveBackwardDist(35, 50);	//drive out from the parking zone
	wait1Msec(50);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardDist(5,15); //move closer

	wait1Msec(1000);

	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move closer

	wait1Msec(500);

	liftMove(300);

	turnEuler(90,55,false); //turn towards pole
	wait1Msec(10);
	driveBackwardDist(14, 50); //drive towards pole
	turnEuler(90,55,true); //turn towards pole
	driveBackwardDist(30,40); //drive against pole and knock it down
	wait1Msec(10);
	liftMove(RESET);

/*
	int a = 0;
	int dist = 0;
	while (true){
		dist = USreadDist(Sonar);
		writeDebugStreamLine("%d",dist);
		motor[leftDrive] = -20;
		motor[rightDrive] = -20;
		if(dist < 30){
			a ++;
		}
		if(a > 7){
			motor[leftDrive] = 0;
			motor[rightDrive]= 0;
			break;
		}
	}

*/
	return;
}

void autoDiag(){
	liftMan(0);
	wait1Msec(200);
	liftMan(2);
	writeDebugStreamLine("Function AutoDiag");
	driveBackwardDist(27, 30);	//drive out from the parking zone
	wait1Msec(10);
	turnEuler(90,55,true); //turn right
	wait1Msec(10);
	driveBackwardDist(30, 30); //drive left backwards
	wait1Msec(10);
	turnEuler(133,70,false); //turn towards the goal SYNC
	wait1Msec(10);
	driveBackwardDist(17, 30); // move towards the goal
	//score
	wait1Msec(50);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardDist(5,15); //move closer

	wait1Msec(1000);

	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move closer

	wait1Msec(500);

	liftMove(RESET);

	driveForwardDist(10,50);

	/*
	liftMan(2);

	//pole

	turnEuler(90,55,false); //turn towards pole
	wait1Msec(10);
	driveBackwardDist(14, 50); //drive towards pole
	turnEuler(90,55,true); //turn towards pole
	driveBackwardDist(30,40); //drive against pole and knock it down
	wait1Msec(10);
	liftMove(RESET);

	*/
	return;
}

void autoDiagR(){
	turnEuler(45, 70, true);
	driveForward(3000, 20);
	return;
}

void autoHoriz(){
	driveBackwardDist(24,20); //drive out of zone
	wait1Msec(100);
	turnEuler(45,55,true); //turn diagonally towards goal
	wait1Msec(100);
	driveBackwardDist(30,20); //drive backwards
	wait1Msec(100);
	turnEuler(135,55,false); //turn directly towards goal
	wait1Msec(100);
	driveBackwardDist(15,20); //drive towards to goal
	wait1Msec(5000);
	//pole
	driveForwardDist(15, 20); //drive back
	wait1Msec(100);
	turnEuler(90,55,false); //turn towards pole
	wait1Msec(100);
	driveBackwardDist(10, 20); //drive towards pole
	wait1Msec(100);
	turnEuler(90,55,true); //turn towards pole
	wait1Msec(100);
	driveBackwardDist(20,40); //drive against pole and knock it down
	return;
}


void initializeRobot(){
	calibrateGyro();
	nMotorEncoder[liftLeft] = 0;		//reset encoder
	hook(true);			//reset servos
	banana(false);
	gate(false);
	//RESET SERVOS
	return;
}

task main()
{
	int a = 0;
	int j = 0;
	int k = 0;
	initializeRobot();
	waitForStart();
	while(true){
		sonarvalue = USreadDist(Sonar);
		writeDebugStreamLine("sonar = %d", sonarvalue);
		if(sonarvalue < 0){
			//Diagonal center console
			a++;
			writeDebugStreamLine("a = %d", a);
			if(a > 5){
				writeDebugStreamLine("Diagonal, %d", sonarvalue);
				autoDiag();
				wait1Msec(2000);
				//autoDiagR();
				break;
			}
			//The ultrasonic sensor cannot detect diagonal surfaces - therefore, it returns 255 as its default value.

		}else if(sonarvalue < 120){
			//goal is straight ahead
			j++;
			writeDebugStreamLine("j = %d", j);
			if(j > 5){
				writeDebugStreamLine("Ahead, %d", sonarvalue);
				autoStraight();
				break;
			}
		}else{
			//goal is sideways
			k++;
			writeDebugStreamLine("k = %d", k);
			if(k > 5){
				writeDebugStreamLine("Sideways, %d", sonarvalue);
				break;
			}
		}
	}
	PlaySoundFile("attention.rso");
}
