#ifndef LIFT_H
#define LIFT_H

#define RESET 0
#define THIRTY_LIFT 1 	//calibrate
#define SIXTY_LIFT 2 	//calibrate
#define NINETY_LIFT 3 	//calibrate
#define GOAL_LIFT 4 	//calibrate
#define LIFT_UP 100 	//calibrate
#define LIFT_DOWN -20 	//calibrate
#define LIFT_TRIM 40  	//calibrate
#define GATE_OPEN 40 		//calibrate
#define GATE_CLOSE 60 	//calibrate

int temp;

void liftMove(int target, bool up);
void equalize();
void trimLeft(bool up);
void trimRight(bool up);
void hook(bool up);

void liftMove(int target, bool up){
	//if the lift is moving UP
	if(up){
		while(nMotorEncoder[liftLeft] < target && nMotorEncoder[liftRight] < target){
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			writeDebugStreamLine("Right Encoder %d", nMotorEncoder[liftRight]);
			motor[liftLeft] = LIFT_UP;
			motor[liftRight] = LIFT_UP;
		}
		motor[liftLeft] = 0;
		motor[liftRight] = 0;
		equalize();
	}else{ 				//if the lift is moving DOWN
		while(nMotorEncoder[liftLeft] > target && nMotorEncoder[liftRight] > target){
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			writeDebugStreamLine("Right Encoder %d", nMotorEncoder[liftRight]);
			motor[liftLeft] = LIFT_DOWN;
			motor[liftRight] = LIFT_DOWN;
		}
		motor[liftLeft] = 0;
		motor[liftRight] = 0;
		equalize();
	}

}

void equalize(){
	//If two lifts are at different heights, match the heights
	writeDebugStreamLine("EQUALIZE");
	if(nMotorEncoder[liftLeft] > nMotorEncoder[liftRight]){
		writeDebugStream("Left > Right");
		while(nMotorEncoder[liftRight] > nMotorEncoder[liftLeft]){
			motor[liftLeft] = 50;
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			writeDebugStreamLine("Right Encoder %d", nMotorEncoder[liftRight]);
		}
		motor[liftLeft] = 0;
	}else if(nMotorEncoder[liftLeft] < nMotorEncoder[liftRight]){
		writeDebugStream("Right > Left");
		while(nMotorEncoder[liftLeft] < nMotorEncoder[liftRight]){
			motor[liftRight] = 50;
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			writeDebugStreamLine("Right Encoder %d", nMotorEncoder[liftRight]);
		}
		motor[liftRight] = 0;
	}
}

void trimLeft(bool up){
	//Change the height of left lift without changing the encoder value
	if(up){
		temp = nMotorEncoder[liftLeft];
		motor[liftLeft] = LIFT_TRIM;
		wait1Msec(300);
		motor[liftLeft] = 0;
		nMotorEncoder[liftLeft] = temp;
		writeDebugStreamLine("temp %d", temp);
	}else{
		temp = nMotorEncoder[liftLeft];
		motor[liftLeft] = -LIFT_TRIM;
		wait1Msec(300);
		motor[liftLeft] = 0;
		nMotorEncoder[liftLeft] = temp;
		writeDebugStreamLine("temp %d", temp);
	}
}

void trimRight(bool up){
	//Change the height of left lift without changing the encoder value
	if(up){
		temp = nMotorEncoder[liftRight];
		motor[liftRight] = LIFT_TRIM;
		wait1Msec(300);
		motor[liftRight] = 0;
		nMotorEncoder[liftRight] = temp;
		writeDebugStreamLine("temp %d", temp);
	}else{
		temp = nMotorEncoder[liftRight];
		motor[liftRight] = -LIFT_TRIM;
		wait1Msec(300);
		motor[liftRight] = 0;
		nMotorEncoder[liftRight] = temp;
		writeDebugStreamLine("temp %d", temp);
	}
}

void hook(bool up){
	if(up){
		servo[hookLeft] = 182;
		servo[hookRight] = 79;
	}else{
		servo[hookLeft] = 230;
		servo[hookRight] = 34;
	}
}


#endif
