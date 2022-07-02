/**
 * @file rainbow.cpp
 * @author  Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "zylProg.h"

class : public zylProg{
private:
	int 		m_Speed = 128;
	int 		m_Slant = 0;
	//int			m_Dir	= 1;
	//TODO add offsets for continous movement when flipping
public:
	using zylProg::zylProg;
	int init(){
		m_Id = 1;
		return 0;
	}
	void render(){
		int v = (millis()*m_Speed/1024);
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
	void input(uint8_t x, uint8_t y, uint8_t z){
		switch(x){
		case 0:
			m_Speed = y;
			break;
		case 6:
			m_Slant = y;
			break;
		case 2:
			//m_Dir = !m_Dir;
			m_Speed = -m_Speed;
		}
	}
}rainbow;
