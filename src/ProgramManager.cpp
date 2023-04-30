#include "ProgramManager.h"
#include <HardwareSerial.h>

void ProgramManagerClass::init(){
	Serial.println("Initializing Program Manager");
}

void ProgramManagerClass::renderProgram(){
}

int ProgramManagerClass::focus(char* program){
	Serial.printf("Program Manager focusing program \"%s\"\n", program);
	return 0;
}

void ProgramManagerClass::input(char* key, char* value){
	Serial.printf("Program Manager received input key=\"%s\", value=\"%s\"\n", key, value);
}