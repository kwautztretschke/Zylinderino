#include "Hardware.h"
#include "ZylOsConfig.h"

#define LED_VOLTAGE 			5                   //Led voltage
#define LED_MAX_MILLIAMPS 		500                //Maximum current provided by power source
#define GLOBAL_BRIGHTNESS 		32                  //Scales down overall brightness

#define NUM_LEDS 				336                 //Total number of Leds
#define DATA_PIN 				13                  //Led data pin
#define DIP1_PIN				33					//Dipswitches
#define DIP2_PIN				32
#define DIP3_PIN				35
#define DIP4_PIN				34

namespace Hardware{

static CRGB s_aLeds[NUM_LEDS] = {0};

int init(){
	//* dipswitches
	pinMode(DIP1_PIN, INPUT);
	pinMode(DIP2_PIN, INPUT);
	pinMode(DIP3_PIN, INPUT);
	pinMode(DIP4_PIN, INPUT);
	Serial.printf("Dipswitches: %d, %d, %d, %d\n", getDipSwitch(0), getDipSwitch(1), getDipSwitch(2), getDipSwitch(3));

	//* initialize LEDs
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(s_aLeds, NUM_LEDS);
	FastLED.setMaxPowerInVoltsAndMilliamps(LED_VOLTAGE, LED_MAX_MILLIAMPS);
	FastLED.setBrightness(GLOBAL_BRIGHTNESS);
	FastLED.show();
	return 0;
}

void display(CRGB fb[X_RES][Y_RES], uint8_t brightness){
	// map coordinates
	for (int x = 0; x < X_RES; x++){
		for (int y = 0; y < Y_RES; y++){
			s_aLeds[x*Y_RES + abs(6*((x+1)%2)-y)] = fb[x][y];
		}
	}
	FastLED.show();
}

void turnOff(){
	for(int j=0;j<NUM_LEDS; j++)
		s_aLeds[j] = CRGB::Black;
	FastLED.show();
}

int getDipSwitch(int num){
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


} // namespace Hardware