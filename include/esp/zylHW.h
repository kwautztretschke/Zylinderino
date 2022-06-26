/**
 * @file zylHW.h
 * @author Bernhard Stöffler
 * @brief 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __ZYLHW_H_
#define __ZYLHW_H_

#include <FastLED.h>
#include "zylFB.h"
#include "config.h"

#define LED_VOLTAGE 			5                   //Led voltage
#define LED_MAX_MILLIAMPS 		1000                //Maximum current provided by power source
#define GLOBAL_BRIGHTNESS 		10                  //Scales down overall brightness
#ifdef Z_LEO
  #define NUM_LEDS 				336				    //Total number of Leds
  #define DATA_PIN 				13                  //Led data pin
#endif
#ifdef Z_BERNIE
  #define NUM_LEDS 				270                 //Total number of Leds
  #define DATA_PIN 				26                  //Led data pin
  #define DIP1_PIN				33					//Dipswitches
  #define DIP2_PIN				32
  #define DIP3_PIN				35
  #define DIP4_PIN				34
#endif

class zylHW{
public:
	virtual int 	init();
	virtual void	show(zylFB fb);
};

class zylHW_Bernie : zylHW{		//? does this need to be in the header or can we just define it in zylHW.cpp?
private:
	static const int 		m_aRes[8];
	static const int 		m_aOff[8];
	CRGB 					m_aLeds[NUM_LEDS];
public:
	int 					init();
	void					show(zylFB fb);
	int						getDipSwitch(int num);
};


#endif