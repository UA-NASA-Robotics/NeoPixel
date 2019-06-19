/*
 * IncFile1.h
 *
 * Created: 4/4/2016 8:24:18 PM
 *  Author: reed
 */ 

#ifndef Motor_H_
#define Motor_H_

#include "AT90CAN_UART.h"
#include "SDO.h"

#define MOTOR_DIRECTION_PORT PORTC
#define MOTOR_LEFT_DIRECTION (1<<PORTC6)|(0<<PORTC5)
#define MOTOR_RIGHT_DIRECTION (0<<PORTC6)|(1<<PORTC5)
#define MOTOR_IDLE (0<<PORTC6)|(0<<PORTC5)


void initMotors(void);
//float getDriveEncoderVal(void);
void setMotorCommandMode(int m);
int getMotorCommandMode(void);
void setMotorEncoderDistance(int target);
void setMotorVelocity(int Vel);
long getEncoderDistance(void);

void motorRampControl(int Vel);

void updateMotorRamping(void);

void initializeExternalInterrupts(void); 

#endif /* Motor_H_ */