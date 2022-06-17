/**
 * @file noise.cpp
 * @author Leo Burke
 * @date 2022-03-29
 * 
 */

#include "zylProg.h"

static class : public zylProg{
private:
	float speed = 0.002;
	float frequency = 50;
	int xpos = 70;
	int ypos = 20;
	bool invert = 0;

public:
	using zylProg::zylProg;
	int init(){
		m_Id = 134;
		return 0;
	}
	void render(){
		for (int x = 0; x < X_RES; x++){
			for (int y = 0; y < Y_RES; y++){
				m_FB[x][y].setHue((sin(millis()*speed + (invert * frequency) * sqrt((x-xpos)^2 + (y-ypos)^2))+1)*127);
				m_FB[x][y].nscale8((sin(millis()*speed - (invert * frequency) * sqrt((x-xpos)^2 + (y-ypos)^2))+1)*127);
			}
		}
	}
} ripple(true);