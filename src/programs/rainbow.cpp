#include "Program.h"

class : public Program{
private:
	int 		m_Speed = 128;
	int 		m_Slant = 0;
	int			m_Dir	= 1;
	//TODO add offsets for continous movement when flipping
public:
	using Program::Program;
	int init(){
		m_Name = "rainbow";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (strcmp(key, "speed") == 0){
			m_Speed = strtol(value, NULL, 10);
			return 0;
		}
		if (strcmp(key, "slant") == 0){
			m_Slant = strtol(value, NULL, 10);
			return 0;
		}
		if (strcmp(key, "direction") == 0){
			m_Dir = value[0] == 'R' ? 1 : -1;
			return 0;
		}
		return 1;
	}
	void render(long ms){
		int v = (ms*m_Speed/128) * m_Dir;
		for (int x = 0; x < X_RES; x++){
			for (int y = 0; y < Y_RES; y++){
				m_FB[x][y].setHue(
					(x*255)/X_RES
					+y*m_Slant
					+v    
				); 
			} 
    	}
	}
}rainbow;
