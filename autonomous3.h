#ifndef AUTONOMOUS3_H
#define AUTONOMOUS3_H

void calibrateGyro();
void driveForward(int millis, int speed);
void driveForward(int speed);
void driveBackward(int millis, int speed);
void driveBackward(int speed);
void driveForwardDist(int inches, int speed);
void driveBackwardDist(int inches, int speed);
void driveForwardDistAC(int inches, float speed);
void driveBackwardDistAC(int inches, float speed);
void driveBackwardUltra(int speed, int ultra);
void driveBackwardDistPC(int inches, float speed);
void driveStop(bool forward, int speed);
void driveStop(bool forward);
void turnEuler(int degrees, int speed, bool left);
void rampCLine(bool forward, int speed);
float gyroValue();
float gyroValueR();
float gyro_zero;

#include "util.h"


/*
Copyright (c) 2014 Jake Lee, AJ Stubbard, Team 4790

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


//gyroscope calibration - run before use
void calibrateGyro() {
	HTGYROsetCal(gyro, 0);
	gyro_zero = 0;

	for (int i = 0; i < 10; i++){
		gyro_zero += HTGYROreadRot(gyro);
		wait1Msec(100);
	}

	gyro_zero /= 10;
}
//drive for a certain time at a certain speed
void driveForward(int millis, int speed) {
	driveForward(speed);
	wait1Msec(millis);
	driveStop(true, speed);
}

//drive at a certain speed
void driveForward(int speed) {
	motor[leftDrive] = speed;
	motor[rightDrive] = speed;
}

//drive back for a certain time at a certain speed
void driveBackward(int millis, int speed) {
	driveForward(millis, -speed);
}

//drive back at a certain speed
void driveBackward(int speed) {
	driveForward(-speed);
}

void driveBackwardUltra(int speed, int ultra){
	while(USreadDist(Sonar) > ultra){
		motor[leftDrive] = -speed;
		motor[rightDrive] = -speed;
	}
	driveStop(true, speed);
}

//drive forward for a specified distance at a certain speed
void driveForwardDist(int inches, int speed) {
	//driving forward using the angle sensor
	int degrees;
	int initAng;
	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		motor[leftDrive] = speed;
		motor[rightDrive] = speed;
		//writeDebugStreamLine("accumulated angle = %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
	}
	writeDebugStreamLine("------------------------");
	driveStop(true, speed);
	wait1Msec(100);
	writeDebugStreamLine("%d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
}

//drive backward for a specified distance at a certain speed
void driveBackwardDist(int inches, int speed) {
	//driving backward using the angle sensor
	int degrees;
	int initAng;
	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		motor[leftDrive] = -speed;
		motor[rightDrive] = -speed;
		//writeDebugStreamLine("accumulated angle: %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
	}
	writeDebugStreamLine("------------------------");
	driveStop(false, speed);
	wait1Msec(100);
	writeDebugStreamLine("%d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
}

//drive forward for a specified distance at a certain speed while maintaining the initial angle
void driveForwardDistAC(int inches, float speed) {
	//driving forward using the angle sensor
	int degrees;
	int initAng;

	//managing the angle
	float factor = 8;
	float lastTime = nSysTime;				//used for dt calculation
	float dt = 0;											//dt for integration
	float g_val = 0;									//gyro value in degrees per second
	float currPos = 0;								//current turn position

	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		//gyro code
		g_val = gyroValueR();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;

		writeDebugStreamLine("Turned %f", currPos);

		if(currPos > 0){
			motor[leftDrive] = speed - (abs(currPos) * factor);
			motor[rightDrive] = speed;
			writeDebugStreamLine("leftDrive = %f", speed + (abs(currPos) * factor));
		}else if(currPos < 0){
			motor[leftDrive] = speed;
			motor[rightDrive] = speed - (abs(currPos) * factor);
			writeDebugStreamLine("rightDrive = %f", speed + (abs(currPos) * factor));
		}else{
			motor[leftDrive] = speed;
			motor[rightDrive] = speed;
			writeDebugStreamLine("straight");
		}

		writeDebugStreamLine("accumulated angle = %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
	}
	writeDebugStreamLine("------------------------");
	driveStop(true, speed);
	wait1Msec(100);
	writeDebugStreamLine("%d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));

}

//drive backward for a specified distance at a certain speed while maintaining the initial angle
void driveBackwardDistAC(int inches, float speed) {
	//driving forward using the angle sensor
	int degrees;
	int initAng;

	//managing the angle
	float factor = 8;
	float lastTime = nSysTime;				//used for dt calculation
	float dt = 0;											//dt for integration
	float g_val = 0;									//gyro value in degrees per second
	float currPos = 0;								//current turn position

	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		//gyro code
		g_val = gyroValueR();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;

		writeDebugStreamLine("Turned %f", currPos);

		if(currPos > 0){
			motor[leftDrive] = -speed;
			motor[rightDrive] = -speed + (abs(currPos) * factor);
			writeDebugStreamLine("rightDrive = %f", -speed + (abs(currPos) * factor));
		}else if(currPos < 0){
			motor[leftDrive] = -speed + (abs(currPos) * factor);
			motor[rightDrive] = -speed;
			writeDebugStreamLine("leftDrive = %f", -speed + (abs(currPos) * factor));
		}else{
			motor[leftDrive] = -speed;
			motor[rightDrive] = -speed;
			writeDebugStreamLine("straight");
		}

		writeDebugStreamLine("accumulated angle = %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
	}
	writeDebugStreamLine("------------------------");
	driveStop(false, speed);
	wait1Msec(100);
	writeDebugStreamLine("%d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
}

void driveBackwardDistPC(int inches, float speed) {
	//driving forward using the angle sensor
	int degrees;
	int initAng;

	bool flag1 = false;
	float correction = 0;

	//managing the angle
	float lastTime = nSysTime;				//used for dt calculation
	float dt = 0;											//dt for integration
	float g_val = 0;									//gyro value in degrees per second
	float currPos = 0;								//current turn position

	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]

	motor[leftDrive] = -speed;
	motor[rightDrive] = -speed;
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		//gyro code
		g_val = gyroValueR();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;

		writeDebugStreamLine("Turned %f", currPos);

		if(currPos > 4 || currPos < -4){
			flag1 = true;
			correction = currPos;
		}

		/*

		if(currPos > 0){
			motor[leftDrive] = -speed;
			motor[rightDrive] = -speed + (abs(currPos) * factor);
			writeDebugStreamLine("rightDrive = %f", -speed + (abs(currPos) * factor));
		}else if(currPos < 0){
			motor[leftDrive] = -speed + (abs(currPos) * factor);
			motor[rightDrive] = -speed;
			writeDebugStreamLine("leftDrive = %f", -speed + (abs(currPos) * factor));
		}else{
			motor[leftDrive] = -speed;
			motor[rightDrive] = -speed;
			writeDebugStreamLine("straight");
		}

		*/

		writeDebugStreamLine("accumulated angle = %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
	}
	writeDebugStreamLine("------------------------");
	driveStop(false);
	wait1Msec(100);

	if(flag1 == true && correction > 4){
		writeDebugStreamLine("Correction: %f", currPos);
		turnEuler(abs(currPos) - 2, 40, true);
	}else if(flag1 == true && correction < -4){
		writeDebugStreamLine("Correction: %f", currPos);
		turnEuler(abs(currPos) - 2, 40, false);
	}

	wait1Msec(500);

	writeDebugStreamLine("%d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
}

void driveStop(bool forward) {
	//braking is a lot quicker when something is sent to the motors
	if(forward == true){
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}else{
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}
}

void driveStop(bool forward, int speed) {
	//braking is a lot quicker when something is sent to the motors
	if(forward == true){
		speed = speed - 10;
		motor[leftDrive] = speed;
		motor[leftDrive] = speed;
		while(speed > 0){
			speed = speed - 10;
			motor[leftDrive] = speed;
			motor[rightDrive] = speed;
			wait1Msec(50);
		}
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}else{
		speed = speed - 10;
		motor[leftDrive] = -speed;
		motor[rightDrive] = -speed;
		while(speed < 0){
			speed = speed - 10;
			motor[leftDrive] = -speed;
			motor[rightDrive] = -speed;
			wait1Msec(50);
		}
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}
}

//Gyroscope turn function
void turnEuler(int degrees, int speed, bool left) { // degrees in degrees, speed in %, left (true), right (false)
	float lastTime = 0;				//used for dt calculation
	float dt = 0;					//dt for integration
	float g_val = 0;				//gyro value in degrees per second
	float currPos = 0;				//current turn position
	float downPos = 0;				//decceleration point
	float halfdeg = 0;				//half of angle target
	int maxSpeed = speed;			//maximum speed
	int minSpeed = 35;				//minimum speed
	float currSpeed = 0;			//current speed
	float accelVal = 0;				//acceleration in power/10Msec
	float slopeTime = 600; 			// time to accel in Msec
	int i;							//counters

	//define halfdeg for cutting of acceleration
	halfdeg = degrees /2 ;
	//writeDebugStreamLine("halfdeg = %d", halfdeg);

	//get the motors moving
	if(left){
		motor[leftDrive] = (int) -minSpeed;
		motor[rightDrive] = (int) minSpeed;
	}else{
		motor[leftDrive] = (int) minSpeed;
		motor[rightDrive] = (int) -minSpeed;
	}
	currSpeed = minSpeed;

	//define acceleration rate
	accelVal = ((maxSpeed - minSpeed) / slopeTime) * 10;
	//writeDebugStreamLine("accelVal = %f", accelVal);

	//acceleration
	//writeDebugStreamLine("accelerating!");
	lastTime = nSysTime;
	for(i=0; i < (slopeTime/10); i++){
		//integration start
		g_val = gyroValue();
		writeDebugStreamLine("%f", g_val);
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		//integration end
		//writeDebugStreamLine("rotated %f", currPos);
		if(currPos >= halfdeg){		//if the acceleration is going past half of the total angle, break and go into decceleration
			//writeDebugStreamLine("breaking from accel!");
			break;
		}
		currSpeed += accelVal;		//increment every time by acceleration value
		//writeDebugStreamLine("current speed = %f", currSpeed);
		if(left){
			motor[leftDrive] = (int) -currSpeed;
			motor[rightDrive] = (int) currSpeed;
		}else{
			motor[leftDrive] = (int) currSpeed;
			motor[rightDrive] = (int)-currSpeed;
		}

		wait1Msec(10 - dt);		//always 10 Msec delay, despite changes in dt
	}

	//calculate when it needs to setart deccelerating
	downPos = degrees - (30);
	//writeDebugStreamLine("downPos = %d", downPos);

	//constant max speed
	if(left){
		motor[leftDrive] = (int) -maxSpeed;
		motor[rightDrive] = (int) maxSpeed;
	}else{
		motor[leftDrive] = (int) maxSpeed;
		motor[rightDrive] = (int) -maxSpeed;
	}

	//keep integrating until we reach downPos
	lastTime = nSysTime;
	while(true){
		//integration start
		g_val = gyroValue();
		writeDebugStreamLine("%f", g_val);
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		//integration end
		if(currPos >= downPos){
			break;
		}
		wait1Msec(10 - dt);
	}

	//writeDebugStreamLine("deccelerating!");
	//decceleration
	lastTime = nSysTime;
	for(i=0; i < (slopeTime/10); i++){
		//integration start
		g_val = gyroValue();
		writeDebugStreamLine("%f", g_val);
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		//integration end
		//writeDebugStreamLine("rotated %f", currPos);
		currSpeed -= (accelVal * 3.5);		//increment every time by acceleration value
		//writeDebugStreamLine("currSpeed %f", currSpeed);

		//if speed is incremented below the minimum speed, reset to min speed
		if(currSpeed < minSpeed){
			currSpeed = minSpeed;
		}

		//if position goes past the target, stop
		if(currPos >= (degrees - (maxSpeed/20))){
			//writeDebugStreamLine("stopping!");
			//turn the motors the opposite direction to prevent coasting
			if(left){
				motor[leftDrive] = 5;
				motor[rightDrive] = -5;
			}else{
				motor[leftDrive] = -5;
				motor[rightDrive] = 5;
			}
			wait1Msec(10);
			motor[leftDrive] = 0;
			motor[rightDrive] = 0;
			break;
		}

		if(left){
			motor[leftDrive] = (int) -currSpeed;
			motor[rightDrive] = (int) currSpeed;
		}else{
			motor[leftDrive] = (int) currSpeed;
			motor[rightDrive] = (int) -currSpeed;
		}

		if(i == (slopeTime/10)-1 && currPos < degrees)
			i -= 1;

		wait1Msec(10 - dt);		//always 10 Msec delay
	}

	//debug code to measure overturns
	//writeDebugStreamLine("Overturning:");
	lastTime = nSysTime;
	for(i=0; i < 30; i++) {
		g_val = gyroValue();\
		writeDebugStreamLine("%f", g_val);
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		wait1Msec(10 - dt);
	}
	writeDebugStreamLine("rotated %f", currPos);
	if(currPos - degrees > 10){
		if(left == true){
			turnEuler(currPos-degrees, speed, false);
		}else{
			turnEuler(currPos-degrees, speed, true);
		}
	}
	writeDebugStreamLine("done.");
	writeDebugStreamLine("----------------------------");
}

void rampCLine(bool forward, int speed){
	//squaring up to the colored tape on the field for consistency
	int colorIn1;
	int colorIn2;
	bool flagA = true;
	bool flagB = false;
	bool flagC = false;
	bool flagD = false;
	if(forward){
		motor[leftDrive] = speed;
		motor[rightDrive] = speed;
	}else{
		motor[leftDrive] = -speed;
		motor[rightDrive] = -speed;
	}
	while(true){
		colorIn1 = HTCS2readColor(colorSensor);
		colorIn2 = HTCS2readColor(colorSensor2);

		if(flagA && colorIn1 > 10 && colorIn2 > 10){
			flagA = false;
			flagB = true;
		}
		if(flagB && (colorIn1 == 2 || colorIn1 == 3 || colorIn1 == 8 || colorIn1 == 9)){
			motor[leftDrive] = 0;
			flagC = true;
		}

		if(flagB && (colorIn2 == 2 || colorIn2 == 3 || colorIn2 == 8 || colorIn2 == 9)){
			motor[rightDrive] = 0;
			flagD = true;
		}
		if(flagD && flagC){
			break;
		}
	}
}

float gyroValue() {
	return abs(HTGYROreadRot(gyro) - gyro_zero);
}

float gyroValueR() {
	return HTGYROreadRot(gyro) - gyro_zero;
}

#endif
