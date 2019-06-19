// Reed J.
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
//
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"
#include "light_ws2812.c"
#include "ws2812_config.h"
//#include "CANFastTransfer.h"

struct cRGB led[18]; //The size of this array has to be the ammount of LEDs on the strip with the greatest amount of LEDs
//#include <Timers.h>

//int received[4];
//#define STATE 1
//#define COLOR 2
//#define UPDATE_FLAG 3
//
//int state;
//bool initialized;


// 0 is start up
// 1 is autonomous-UA
// 2 is macro-UA
// 3 is normal-UA
// 4 is christmas
// 5 is party
// 6 is override
// 7 is error
//#define GETTING_COMMS   0
//#define AUTONOMOUS      1
//#define MACRO           2
//#define NORMAL          3


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


//int main(void)
//{
	//initCANFastTransfer();
	//
	//_delay_ms(1000);
	//
  //if (ReceiveDataCAN()) 
  //{
	  //if (state == GETTING_COMMS)
	  //{
		//while(!ReceiveDataCAN())
		//{
			//led[0].r=0;led[0].g=0;led[0].b=255;    // Write red to array
			//ws2812_setleds(led,1);                       
			//_delay_ms(500);
			//led[0].r=255;led[0].g=0;led[0].b=0;    // Write red to array
			//ws2812_setleds(led,1);
		//}
		//initialized = false;
	  //}
	  //else if (state == AUTONOMOUS  &&!initialized)
	  //{
		//led[0].r=0;led[0].g=0;led[0].b=255;    // Write red to array
		//ws2812_setleds(led,1);
		//initialized = true;
	  //}
	  //else if (state == MACRO )
	  //{
		//led[0].r=150;led[0].g=0;led[0].b=100;    // Write red to array
		//ws2812_setleds(led,1);
		//initialized = true;
	  //}
	  //else if (state == NORMAL &&!initialized)
	  //{
		//led[0].r=0;led[0].g=255;led[0].b=0;    // Write red to array
		//ws2812_setleds(led,1);
		//initialized = true;
	  //}  
   //}
//}



int main(void)
{
	for(int counter = 1; counter < 18; counter++)
	{
	led[counter].r=0;led[counter].g=255;led[counter].b=0;    
	ws2812_setleds(led,counter);                        // wait for 500ms.
	_delay_ms(500);
	}
}

