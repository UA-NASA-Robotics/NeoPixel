/*
 * macros.c
 *
 * Created: 5/14/2017 3:01:48 PM
 *  Author: Seth Carpenter
 */ 

#include "macros.h"
#include <stdbool.h>
#include <stdlib.h>
#include "STD_methods.h"
#include "..\..\Common\CommsDefenition.h"
#include "CANFastTransfer.h"
#include "Motor.h"
#include "PID.h"
#include "LEDs.h"
#include "UART_handler.h"
#define F_CPU 16000000
#include <util/delay.h>
//this is the tolerance value of how close the encoder values are to the desired distance for the robot to move
#define DRIVE_ENCODER_DELTA_RANGE 25


#define motor_KP 1
#define motor_KI 0
#define motor_KD 0

#define motorSpeedMax 500
#define motorSpeedMin 100

int getNewPID_val(long newVal);
int performNavigationCommand    = 0;
int PauseCommand				= 0;
int PauseData					= 0;
int navigationCommandData       = 0;
bool wasPaused					= false;
bool macroRunning               = false;
int StoredEncoderReading			= 0;
int storedRequestedDist				= 0;
PID_Struct_t motorPID;

long localEncoderVal = 0;
long LastEncoderVal = 0;

void setMacroState(bool val)
{
	macroRunning = val;
	
}
long getLocalEncoderVal()
{
	return localEncoderVal;
}
void performVelocityControl(int Vel)
{
	setMotorVelocity(Vel);
	//toggleLED(LED0);
}
void preformDriveSequence(int dist)
{
	if(dist != 0)
	{
		setLED(LED2,ON);
		dist=dist;
		localEncoderVal = 0;
		LastEncoderVal = getDriveEncoderVal();
	
		INIT_PID(&motorPID,dist, motor_KP, motor_KI, motor_KD);
// 		if(abs(dist) > 25)
// 		{
// 		
// 			toggleLED(LED0);
// 		}
		while (isInRange(getLocalEncoderVal(),dist, DRIVE_ENCODER_DELTA_RANGE) == false && getPerformNavigationCommand() != 0 && getPauseCommand() != PAUSE)
		{ 
		
	 		//this is pretty self explanatory
			updateMacroCommunications();
			//motor control handled in here
			updateMotors();
			updateMotorRamping();
			localEncoderVal += getDriveEncoderVal() - LastEncoderVal;
			LastEncoderVal = getDriveEncoderVal(); 
			
		
		}
		//checking to see if the gyros sent a pause command 
		if(getPauseCommand() != PAUSE)
		{
			transmitGyroComplete();
			setPauseCommand(0);
		}
	
		deltaEncoderDistLeft = dist - getLocalEncoderVal();
// 		_delay_ms(5);
// 		SendChar(0x77);
// 		_delay_ms(5);
		SendChar(deltaEncoderDistLeft);
		stopNavigationCommand();
		setMotorVelocity(0);
		setLED(LED2,OFF);
		//_delay_ms(10);
	}
	else
	{
		setPauseCommand(0);
		setNavigationCommandData(0);
		setPerformNavigationCommand(0);
		macroRunning=false;
		setMotorVelocity(0);
	}
}
void transmitGyroComplete()
{
	//clear the commands
	ToSendCAN(1,0);
	sendDataCAN(MouseGyroAddress);
	
}
int getNewPID_val(long newVal)
{
	int speed = updateOutput(&motorPID, newVal);
	if(abs(speed) > motorSpeedMax)
	{
		return (speed > 0? 1: -1)*motorSpeedMax;
	}
	else if(abs(speed) < motorSpeedMin)
	{
		return (speed > 0? 1: -1)*motorSpeedMin;
	}
	return speed;
}
void updateMotors()
{
	int speed = getNewPID_val(getLocalEncoderVal());
	setMotorVelocity(speed);
}

int getPerformNavigationCommand(void)
{
	return performNavigationCommand;
}
int getNavigationCommandData(void)
{
	return navigationCommandData;
}
int getPauseCommand(void)
{
	return PauseCommand;
}
int getPauseData(void)
{
	return PauseData;
}
void setPauseCommand(int _data)
{
	PauseCommand = _data;
	if(PauseCommand == REQUEST_ENCODER_VAL)
	{
		ToSendCAN(MOTOR_PAUSE_DATA_ADDRESS,deltaEncoderDistLeft);
		sendDataCAN(MouseGyroAddress);
	}
}
void setPauseData(int _data)
{
	PauseData = _data;
}
long getDriveEncoderVal(void)
{
	
		return getEncoderDistance();
		
}
void setPerformNavigationCommand(int c)
{
	performNavigationCommand=c;
}
void setNavigationCommandData(int d)
{
	navigationCommandData = d;
}
void updateMacroCommunications(void)
{
	//Check communications from the router for a cancel command
	checkCANFTdata();
	if(getPerformNavigationCommand()==0)
	{
		stopNavigationCommand();
	}
	
}
void doNavigationCommand(void)
{
	if(getPauseCommand() == RESUME)
		{
			macroRunning=true;
			//setPausedData(0);
			preformDriveSequence(getPauseData());
			setLED(LED3,ON);
		}
	if(!macroRunning)
	{
		
	
			switch(getPerformNavigationCommand())
			{
				case VELOCITY_MODE:
					performVelocityControl(getNavigationCommandData());
					setPerformNavigationCommand(0);
				
					break;
				case ENCODER_DISTANCE_MODE:
					macroRunning=true;
					preformDriveSequence(getNavigationCommandData());
				
					break;
			}
		
	}
}
void stopNavigationCommand(void)
{
	setNavigationCommandData(0);
	if(macroRunning)
	{
 		macroRunning=false;
		setMotorVelocity(0);
		/*set(LED0,OFF);*/
	}
}