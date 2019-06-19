/*
 * Motor.c
 *
 * Created: 4/4/2016 8:24:43 PM
 *  Author: reed
 */
#include "Motor.h"
#include "general.h"
#include "assert.h"
#include "Timer.h"
#include "can.h"
#include "STD_Methods.h"
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LEDs.h"

#define ACCEPTABLE_DVEL_LIMIT 5

#define F_CPU 16000000
#include <util/delay.h>
#define CAN_PACKET_SIZE 8
#define RECEIVE_MASK 0x7ff

timer_t motorRampTimer;
int motorVelocity, motorCommandMode;
int encoderDistanceTarget;
long encoder_counts_abs = 0;


void initMotors(void)
{
	setTimerInterval(&motorRampTimer,20);
}

long getEncoderDistance(void)
{
	
	return encoder_counts_abs;
}

void setMotorCommandMode(int m)
{
	motorCommandMode=m;
}

int getMotorCommandMode(void)
{
	return motorCommandMode;
}

void setMotorEncoderDistance(int target)
{
	encoderDistanceTarget=target;
}

void setMotorVelocity(int Vel)
{
	motorVelocity=Vel;
}



int previousMotorCommand=0;
void motorRampControl(int Vel)
{
	//If the previous motor command is within the acceptable dVel range
	if(isInRange((previousMotorCommand),Vel,ACCEPTABLE_DVEL_LIMIT))
	{
		//toggleLED(LED2);
		if(Vel>0)
		{
			//Set direction
			MOTOR_DIRECTION_PORT=MOTOR_LEFT_DIRECTION;
		}
		else if(Vel<0)
		{
			//Set Direction
			MOTOR_DIRECTION_PORT=MOTOR_RIGHT_DIRECTION;
		}
		else
		{
			MOTOR_DIRECTION_PORT = MOTOR_IDLE;
			
		}
		//Set the velocity directly
		setOC1BPulseWidth(abs(Vel)*10);	
		//Update the previous value to our setpoint now	
		previousMotorCommand=Vel;
	}
	else
	{
		//toggleLED(LED0);
		//Increment by the acceptable dVel range (ramp up)
		if(previousMotorCommand<Vel)
		{
			previousMotorCommand+=ACCEPTABLE_DVEL_LIMIT;
		}
		else   //Decrement by the acceptable dVel range (ramp down)
		{
			previousMotorCommand-=ACCEPTABLE_DVEL_LIMIT;
		}
		
		//Determine direction and set it correctly
		if(previousMotorCommand>0)
		{
			//Set direction
			MOTOR_DIRECTION_PORT=MOTOR_LEFT_DIRECTION;
		}
		else
		{
			//Set Direction
			MOTOR_DIRECTION_PORT=MOTOR_RIGHT_DIRECTION;			
		}
		//Set the new vel command
		setOC1BPulseWidth(abs(previousMotorCommand)*10);
	}
}

void updateMotorRamping(void)
{
	if(timerDone(&motorRampTimer))
	{
		//toggleLED(LED2);
		motorRampControl(motorVelocity);
		resetTimer(&motorRampTimer);
	}
}



void initializeExternalInterrupts(void) 
{
	
	//two bits per external interrupt, from 3 to 0.
	//10 means falling edge, 11 means rising edge, 01 is any edge
	EICRA = 0b00101000;
	
	//lower 4 bits are masks for the external interrupts 3-0
	EIMSK = 0b00000100;
	
}

uint8_t interval=0;
ISR(INT2_vect) {
	
	if(interval>16)
	{
		if(motorVelocity>0)
		{
			//this is the interrupt for encoder feedback from the motors
			encoder_counts_abs++;
		}
		else
		{
			encoder_counts_abs--;
		}
		interval=0;
	}
	else
	{
		interval++;
		
	}
	
	//note, ISR should clear self when called
	
}

ISR(INT1_vect) {
	//this is the interrupt for the bumper switch
	
	//note, ISR should clear self when called
}