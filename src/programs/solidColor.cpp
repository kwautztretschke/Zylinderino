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
	using 		zylProg::zylProg;
	int			m_ColorIndex = 0;

	void input(uint8_t x, uint8_t y, uint8_t z){
		switch(x){
		case 1:
			m_ColorIndex = y;
			break;
		}
	}
	int init(){
		m_Id = 0;
		return 0;
	}
	void render(){
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++)
				//m_FB[x][y].setHue((millis()/10)%255);
				m_FB(x, y) = zylProgManager::getColor(m_ColorIndex);
	}
} solidColor;