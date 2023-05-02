#include <HardwareSerial.h>

#include "ProgramManager.h"
#include "Program.h"

void ProgramManager::add(Program* ptr)
{	//call this in the constructor of your programs to add them to a list of all programs
	ptr->m_pNext = 	m_pHead;
	m_pHead = 		ptr;
	m_Count++;
}

int ProgramManager::init(){
	Serial.println("Initializing Program Manager");
	return 0;
}

int ProgramManager::initPrograms(){
	Serial.println("Initializing Programs");
	return 0;
}

void ProgramManager::render(uint8_t* fb, long tick){
}

int ProgramManager::focus(char* program){
	Serial.printf("Program Manager focusing program \"%s\"\n", program);
	return 0;
}

int ProgramManager::input(char* key, char* value){
	Serial.printf("Program Manager received input key=\"%s\", value=\"%s\"\n", key, value);
	return 0;
}
