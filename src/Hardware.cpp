#include "Hardware.h"

namespace Hardware{

int init(){
	pinMode(LEDR, OUTPUT);
	pinMode(LEDG, OUTPUT);
	pinMode(LEDB, OUTPUT);
	digitalWrite(LEDR, LOW);
	digitalWrite(LEDG, LOW);
	digitalWrite(LEDB, LOW);
	return 0;
}

void display(CRGB* fb, uint8_t brightness){
	CRGB c = fb->scale8(brightness);
	analogWrite(LEDR, c.r);
	analogWrite(LEDG, c.g);
	analogWrite(LEDB, c.b);
}

void turnOff(){
	digitalWrite(LEDR, LOW);
	digitalWrite(LEDG, LOW);
	digitalWrite(LEDB, LOW);
}

}