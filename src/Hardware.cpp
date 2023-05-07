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

void display (uint8_t* fb){
	analogWrite(LEDR, fb[0]);
	analogWrite(LEDG, fb[1]);
	analogWrite(LEDB, fb[2]);
}


}