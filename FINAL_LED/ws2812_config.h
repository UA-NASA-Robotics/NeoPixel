/*
 * light_ws2812_config.h
 * v2.4 - Nov 27, 2016
 * User Configuration file for the light_ws2812_lib
 */ 


#ifndef WS2812_CONFIG_H_
#define WS2812_CONFIG_H_

// Define Reset time in µs. 
// WS2813 needs 300 µs reset time
// WS2812 and clones only need 50 µs
#define ws2812_port B     // Data port 

#define ws2812_resettime  300 

#define ws2812_pin1 5    // Data out pin
#define ws2812_pin2 6    // Data out pin



#endif /* WS2812_CONFIG_H_ */