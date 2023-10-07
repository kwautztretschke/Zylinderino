#include "Program.h"

static class : public Program{
public:
	int m_ColorIndex = 0;
	using Program::Program;
	int init(){
		m_Name = "solidColor";
		return 0;
	}
	int input(char* key, char* value){
		if(!strcmp(key, "colorindex"))	
			m_ColorIndex = strtol(value, NULL, 10);
		else{
			// wrong input
			return 1;
		}
		return 0;
	}
	void render(long ms){
		for (int i=0;i<FB_SIZE;i++){
			m_FB[i] = ProgramManager::getColor(m_ColorIndex);
		}
	}
} solidColor;
