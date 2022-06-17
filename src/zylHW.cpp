/**
 * @file zylHW.cpp
 * @author Bernhard Stöffler
 * @brief 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "zylHW.h"


const int zylHW_Bernie::m_aRes[8] = {32, 33, 33, 34, 34, 34, 35, 35};		// Number of LEDs in each row 
const int zylHW_Bernie::m_aOff[8] = {0, 32, 65, 98, 132, 166, 200, 235};		// indices of first LED in row

int zylHW_Bernie::init(){
	//* dipswitches
	pinMode(DIP1_PIN, INPUT);
	pinMode(DIP2_PIN, INPUT);
	pinMode(DIP3_PIN, INPUT);
	pinMode(DIP4_PIN, INPUT);
	Serial.printf("Dipswitches: %d, %d, %d, %d\n", getDipSwitch(0), getDipSwitch(1), getDipSwitch(2), getDipSwitch(3));
	//* initialize LEDs
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(m_aLeds, NUM_LEDS);
	FastLED.setMaxPowerInVoltsAndMilliamps(LED_VOLTAGE, LED_MAX_MILLIAMPS);
	FastLED.setBrightness(GLOBAL_BRIGHTNESS);
	//* set all LEDs to off
	for(int j=0;j<NUM_LEDS; j++)
		m_aLeds[j] = CRGB::Black;
	FastLED.show();
	return 0;
}

void zylHW_Bernie::show(CRGB fb[X_RES][Y_RES]){
	// map coordinates
	for(int y=0; y<8&&y<Y_RES; y++){
		for (int x=0; x<m_aRes[y]&&x<X_RES; x++){
			m_aLeds[m_aOff[y] + x] = fb[x][7-y]; 		//flip y values because of OpenGL indexing
		}
	}
	FastLED.show();
}

int zylHW_Bernie::getDipSwitch(int num){
	switch(num){
		case 0:
		return (digitalRead(DIP1_PIN)==HIGH);
		case 1:
		return (digitalRead(DIP2_PIN)==HIGH);
		case 2:
		return (digitalRead(DIP3_PIN)==HIGH);
		case 3:
		return (digitalRead(DIP4_PIN)==HIGH);
		default:
		return 0;
	}
}
