#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Sonar,          sensorSONAR)
#pragma config(Sensor, S3,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     liftRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servoGate,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servoGate2,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    hookLeft,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    hookRight,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "util.h"
#include "lift.h"

task main()
{
	nMotorEncoder[liftLeft] = 0;
	nMotorEncoder[liftRight] = 0;
		servo[hookLeft] = 182;
		servo[hookRight] = 79;
	while(true){
		if(joy1Btn(CONTROLLER_R1)){
			motor[liftLeft] = 100;
			motor[liftRight] = 100;
		}else if(joy1Btn(CONTROLLER_R2)){
			motor[liftLeft] = -20;
			motor[liftRight] = -20;
		}else{
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}
		if(joy1Btn(CONTROLLER_A)){
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			writeDebugStreamLine("Right Encoder %d", nMotorEncoder[liftRight]);
			wait10Msec(100);
		}

		if(joy1Btn(CONTROLLER_B)){
			writeDebugStreamLine("BUTTONB");
			equalize();
		}
    //Gate Controls
    if(joy1Btn(CONTROLLER_L1)){
        gate(true);
    }else if(joy1Btn(CONTROLLER_L2)){
        gate(false);
    }

	}
}
