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

#include "zylProg.h"

static class : public zylProg{
public:
	using zylProg::zylProg;
	int init(){
		m_Id = 128;
		return 0;
	}
	void render(){
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++)
				//m_FB[x][y].setHue((millis()/10)%255);
				m_FB[x][y] = zylProgManager::getColor(0);
	}
} sampleProgram(false);