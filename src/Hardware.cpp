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

void display(uint8_t* fb, uint8_t brightness){
	int r = (fb[0] * brightness) / 255;
	int g = (fb[1] * brightness) / 255;
	int b = (fb[2] * brightness) / 255;
	analogWrite(LEDR, r);
	analogWrite(LEDG, g);
	analogWrite(LEDB, b);
}

void turnOff(){
	digitalWrite(LEDR, LOW);
	digitalWrite(LEDG, LOW);
	digitalWrite(LEDB, LOW);
}

}