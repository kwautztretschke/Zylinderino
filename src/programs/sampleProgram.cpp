#include <HardwareSerial.h>
#include "Program.h"

static class : public Program{
public:
	using Program::Program;
	int init(){
		m_Name = "sample";
		return 0;
	}
	void render(long ms){
		m_FB[0] =  ms 			% 255;
		m_FB[1] = (ms + 85)		% 255;
		m_FB[2] = (ms + 170)	% 255;
		Serial.printf("Sampleprogram go brrrr %d\n", ms);
	}
} sampleProgram;
