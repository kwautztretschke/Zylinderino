#include "Program.h"

static class : public Program{
public:
	using Program::Program;
	int init(){
		m_Name = "sample";
		return 0;
	}
	void render(long ms){
		m_Color
	}
} sampleProgram;
