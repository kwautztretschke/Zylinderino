/**
 * @file sampleProgram.cpp
 * @author Bernhard Stöffler
 * @brief 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "shared/zylProg.h"

static class : public zylProg{
public:
	using zylProg::zylProg;
	int init(){
		m_Id = 128;
		return 0;
	}
	void render(long ms){
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++)
				//m_FB[x][y].setHue((millis()/10)%255);
				m_FB(x, y) = (ms/100 % 2) ? zylPel(255, 0, 0) : zylPel(0, 255, 0);
	}
} sampleProgram(false);
