#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Sonar,          sensorSONAR)
#pragma config(Sensor, S3,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     liftLeft,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     liftRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    gateFront,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    gateBack,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    hookLeft,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    hookRight,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "util.h"
#include "lift.h"

task main(){
	//waitForStart();
	nMotorEncoder[liftLeft] = 0;
	nMotorEncoder[liftRight] = 0;
	servo[hookLeft] = 182;
	servo[hookRight] = 79;
	servo[gateFront] = 0;
	servo[gateBack] = 255;
	while(true){
    	// Drive controls
        motor[leftDrive] = scaleJoystick(joystickValue(1, 1, 2));
        motor[rightDrive] = scaleJoystick(joystickValue(1, 2, 2));

        // Lift controls
        /*
        if(joy1Btn(CONTROLLER_A)){
            if(nMotorEncoder[liftLeft] < THIRTY_LIFT){
                liftMove(THIRTY_LIFT, true);
            }else if(nMotorEncoder[liftLeft] > THIRTY_LIFT){
                liftMove(THIRTY_LIFT, false);
            }else{
                //nothing
            }
        } else if(joy1Btn(CONTROLLER_B)){
            if(nMotorEncoder[liftLeft] < SIXTY_LIFT){
                liftMove(SIXTY_LIFT, true);
            }else if(nMotorEncoder[liftLeft] > SIXTY_LIFT){
                liftMove(SIXTY_LIFT, false);
            }else{
                //nothing
            }
        } else if(joy1Btn(CONTROLLER_X)){
            if(nMotorEncoder[liftLeft] < NINETY_LIFT){
                liftMove(NINETY_LIFT, true);
            }else if(nMotorEncoder[liftLeft] > NINETY_LIFT){
                liftMove(NINETY_LIFT, false);
            }else{
                //nothing
            }
        } else if(joy1Btn(CONTROLLER_Y)){
            if(nMotorEncoder[liftLeft] < GOAL_LIFT){
                liftMove(GOAL_LIFT, true);
            }else if(nMotorEncoder[liftLeft] > GOAL_LIFT){
                liftMove(GOAL_LIFT, false);
            }else{
                //nothing
            }
        }
        */

        //temp lift controls
        if(joy1Btn(CONTROLLER_R1)){
					motor[liftLeft] = 100;
					motor[liftRight] = 100;
				}else if(joy1Btn(CONTROLLER_R2)){
					//if(	nMotorEncoder[liftLeft] < 45 || nMotorEncoder[liftRight] < 45){ //bottom limit
					//	motor[liftLeft] = 0;
					//	motor[liftRight] = 0;
					//}else{
						motor[liftLeft] = -10;
						motor[liftRight] = -10;
					//}
				}else{
					motor[liftLeft] = 0;
					motor[liftRight] = 0;
				}

        //hook controls
		    if(joystick.joy1_TopHat == 0){
		        hook(true);
		    }else if(joystick.joy1_TopHat == 4){
		        hook(false);
		    }

		    //gate controls
		    if(joy2Btn(CONTROLLER_R1)){
		        servo[gateFront] = 0;
		    }else if(joy2Btn(CONTROLLER_R2)){
		        servo[gateFront] = 255;
		    }

		    if(joy2Btn(CONTROLLER_L1)){
		        servo[gateBack] = 255;
		    }else if(joy2Btn(CONTROLLER_L2)){
		        servo[gateBack] = 0;
		    }


		    //intake controls
        if(joy1Btn(CONTROLLER_L1)){
					motor[intake] = 100;
				}else if(joy1Btn(CONTROLLER_L2)){
					motor[intake] = -100;
				}else{
					motor[intake] = 0;
				}

    }
}
