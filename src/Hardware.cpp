#include "Hardware.h"
#include "ZylOsConfig.h"

#define LED_VOLTAGE 			5                   //Led voltage
#define LED_MAX_MILLIAMPS 		500                //Maximum current provided by power source
#define GLOBAL_BRIGHTNESS 		32                  //Scales down overall brightness

#define NUM_LEDS 				270                 //Total number of Leds
#define DATA_PIN 				26                  //Led data pin
#define DIP1_PIN				33					//Dipswitches
#define DIP2_PIN				32
#define DIP3_PIN				35
#define DIP4_PIN				34

namespace Hardware{

static const int s_aRes[8] = {32, 33, 33, 34, 34, 34, 35, 35};		// Number of LEDs in each row 
static const int s_aOff[8] = {0, 32, 65, 98, 132, 166, 200, 235};	// indices of first LED in row
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
	for(int y=0; y<8&&y<Y_RES; y++){
		for (int x=0; x<s_aRes[y]&&x<X_RES; x++){
			s_aLeds[s_aOff[y] + x] = fb[x][7-y].nscale8(brightness); 		//flip y values because of OpenGL indexing
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