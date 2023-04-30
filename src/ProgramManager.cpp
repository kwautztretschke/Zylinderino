#include "ProgramManager.h"
#include <HardwareSerial.h>

void ProgramManagerClass::init(){
	Serial.println("Initializing Program Manager");
}

void ProgramManagerClass::renderProgram(){
}

int ProgramManagerClass::focus(char* program){
	return 0;
}

void ProgramManagerClass::input(char* key, char* value){
}