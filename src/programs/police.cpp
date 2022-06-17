/**
 * @file noise.cpp
 * @author Leo Burke
 * @date 2021-12-06
 * 
 */

#include "zylProg.h"

static class : public zylProg{
private:
	int colorId = 0;
	int speed = 1;
	int forceBlue = true;
	// int state = 0; 												//indicates states, 0,3 on; 0,15 off; 0,3on; 0,25off for each side
	// int side = 0;													//0 for right side, 1 for left side
	// int timings[4] = {120,40,120,60};
	#define length 20
	int dualPattern[2][length] = {{0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
																{0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0}};
	int stepWindow[2][2] = {{0,0},{0,0}};
	uint state = 0;

	
	int stepTime = 20;
	long nextStepTime = millis();

	CRGB value = CRGB::Black;
public:
	using zylProg::zylProg;
	int init(){
		m_Id = 133;
		return 0;
	}
	void render(){
		if(nextStepTime<millis()){
			for (int s = 0; s < 2; s++){	//two sides
				value = forceBlue ? CRGB::Blue : zylProgManager::getColor(colorId);
				switch (dualPattern[s][state%length]+dualPattern[s][(state+1)%length]){ //for each side add current and next value
				case 0:	//full off
					value = CRGB::Black;
					break;
				case 1:	//half on
					value.nscale8(128);
					break;
				case 2:	//full on
					break;
				}
				for (int x = X_RES/12 + s*X_RES/2; x < X_RES*5/12 + s*X_RES/2; x++)
					for (int y = 0; y < Y_RES; y++)
						m_FB[x][y] = value;
			}
			nextStepTime = millis() + stepTime;
			
			

			// for (int x = X_RES/12; x < X_RES*5/12; x++)
			// 	for (int y = 0; y < Y_RES; y++)
			// 		m_FB[x][y] = forceBlue ? CRGB::Blue : zylProgManager::getColor(colorId);
					
			// for (int x = X_RES*7/12; x < X_RES*11/12; x++)
			// 	for (int y = 0; y < Y_RES; y++)
			// 		m_FB[x][y] = forceBlue ? CRGB::Blue : zylProgManager::getColor(colorId);

			// for (int x = 0; x < X_RES; x++)
			// 	for (int y = 0; y < Y_RES; y++)
			// 		m_FB[x][y] = CRGB::Black;
					
			
		}
		
	}
} police(false);