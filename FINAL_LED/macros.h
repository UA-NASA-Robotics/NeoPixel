/*
 * macros.h
 *
 * Created: 5/14/2017 3:02:06 PM
 *  Author: Seth Carpenter
 */ 


#ifndef MACROS_H_
#define MACROS_H_
#include <stdbool.h>

int deltaEncoderDistLeft;

int getPerformNavigationCommand(void);
void setPerformNavigationCommand(int c);
void setNavigationCommandData(int d);
int getNavigationCommandData(void);
void updateMacroCommunications(void);
void stopNavigationCommand(void);
void updateMotors();
void doNavigationCommand(void);
long getLocalEncoderVal();
void setMacroState(bool val);
void transmitGyroComplete();
int getPauseData(void);
int getPauseCommand(void);
void setPauseData(int _data);
void setPauseCommand(int _data);
long getDriveEncoderVal(void);

#endif /* MACROS_H_ */