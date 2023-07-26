#include "Program.h"

static class : public Program{
public:
	using Program::Program;
	int init(){
		m_Name = "solidColor";
		return 0;
	}
	void render(long ms){
		for (int i=0;i<3;i++){
			m_FB[i] = ProgramManager::getColor()[i];
		}
	}
} solidColor;
