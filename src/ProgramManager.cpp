#include <HardwareSerial.h>

#include "ProgramManager.h"
#include "Program.h"


namespace ProgramManager{
	
static int			s_Count = 0;
static Program*		s_pHead = NULL;
static Program*		s_pActive = NULL;
static uint8_t		s_Color[3] = {0}; // TODO array of colors
static uint8_t		s_FB[3]= {0}; //TODO framebuffer


void add(Program* ptr)
{	//call this in the constructor of your programs to add them to a list of all programs
	ptr->m_pNext = 	s_pHead;
	s_pHead = 		ptr;
	s_Count++;
}

int init(){
	Serial.println("Initializing Program Manager");
	s_pActive = s_pHead;
	return 0;
}

int initPrograms(){
	Serial.printf("initializing %d programs\n", s_Count);
	int error=0;
	Program* ptr = s_pHead;
	for(int i=0; i<s_Count; i++){
		error += ptr->init();
		Serial.printf("Program \"%s\" at %p\n", ptr->m_Name, ptr);
		ptr = ptr->m_pNext;
	}
	return error;
}

void render(long tick){
	s_pActive->render(tick);
	for (int i=0;i<3;i++)
		s_FB[i] = s_pActive->m_FB[i];
}

int focus(char* name){
	Serial.printf("Program Manager searching \"%s\"... ", name);
	Program* ptr = s_pHead;
	while(ptr){
		if(!strcmp(ptr->m_Name, name)){
			Serial.println("Found!");
			s_pActive = ptr;
			s_pActive->activate();
			return 0;
		}
		ptr = ptr->m_pNext;
	}
	Serial.println("Error!");
	return 1;
}

int input(char* key, char* value){
	Serial.printf("Program Manager received input key=\"%s\", value=\"%s\"\n", key, value);
	return s_pActive->input(key, value);
}

void setColor(uint8_t* c){
	for(int i=0;i<3;i++)
		s_Color[i] = c[i];
}

uint8_t* getColor() {
	return s_Color;
}

uint8_t* getFB() {
	return s_FB;
}

} // namespace ProgramManager