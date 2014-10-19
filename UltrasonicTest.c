#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int sonarvalue = 0;
void autoStraight();

void autoStraight(){
	while (SensorValue[Sonar] > 15){
		motor[motorLeft] = 20;
		motor[motorRight] = 20;
	}
	motor[motorLeft] = 0;
	motor[motorRight]= 0;
}

task main()
{
	while(true){
		sonarvalue = SensorValue[Sonar];
		if(sonarvalue == 255){
			//Diagonal center console
			nxtDisplayCenteredTextLine(3, "Diagonal, %d", sonarvalue);
		}else if(SensorValue[Sonar] < 105){
			//goal is straight ahead
			nxtDisplayCenteredTextLine(3, "Ahead, %d", sonarvalue);
			autoStraight();
			break;
		}else{
			//goal is sideways
			nxtDisplayCenteredTextLine(3, "Sideways, %d", sonarvalue);
		}
	}
	PlaySoundFile("attention.rso");
}
