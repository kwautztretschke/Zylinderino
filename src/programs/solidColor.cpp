#include "Program.h"

static class : public Program{
public:
	using Program::Program;
	int init(){
		m_Name = "solidColor";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		return 1;
	}
	void render(long ms){
		CRGB c = getColor();
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++)
				m_FB[x][y] = c;
	}
} solidColor;
