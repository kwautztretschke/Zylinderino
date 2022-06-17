/**
 * @file noise.cpp
 * @author Leo Burke
 * @date 2021-12-02
 * 
 */

#include "zylProg.h"

static class : public zylProg{
private:
	int scale = 128;			//todo: find good defaults
	int speed = 4;
	int threshhold = 1;
	int numcolors = 2;

	int m_aNoiseDividers[6][6] =	{{255,  0,  0,  0,  0,  0},  //takes[color][divider] and returns upper bound
									{127,255,  0,  0,  0,  0},
									{ 85,170,255,  0,  0,  0},
									{ 64,127,191,255,  0,  0},
									{ 51,102,153,204,255,  0},
									{ 70,95,120,150,180,255}};

	#define N_LOWEST 30
	#define N_HIGHEST 225

	uint8_t cutoffMap(int input,uint8_t fromlow,uint8_t fromhigh,uint8_t tolow, uint8_t tohigh){
	int value = map(input,fromlow,fromhigh,tolow,tohigh);
	if (value < 0) return 0;
	else if (value > 255) return 255;
	else return value;
	}
public:
	using zylProg::zylProg;
	int init(){
		m_Id = 3;
		return 0;
	}
	void render(){
		for (int x = 0; x < X_RES; x++){
			for (int y = 0; y < Y_RES; y++){
				int noise = inoise8(x*(scale+20)/5,y*(scale+20)/5,millis()*(speed+1)/20); //todo: get sliders and time factor
				//Serial.print(noise);
				int prestep = 0;
				if (false){	//todo: hue mode here
					m_FB[x][y].setHue(cutoffMap(noise, N_LOWEST,N_HIGHEST,0,255));
				} else {
					for (int color = 0; color < numcolors; color++){	//todo: loop to number of colors(value of discrete slider)
						int step = m_aNoiseDividers[numcolors-1][color];
						if (noise<=step){
							m_FB[x][y] = zylProgManager::getColor(color);
							if (noise<(prestep + step)/2){
								m_FB[x][y].nscale8(map(noise,prestep,step,50,255));
							}else{
								m_FB[x][y].nscale8(map(noise,prestep,step,255,50));
							}
							//Serial.print(numcolors);
							break;
						} else{
							prestep = step;
							//Serial.print("x");
						}
					}
				}
			}
		}
	}

	void input(uint8_t x, uint8_t y, uint8_t z){
		switch(x){
		case 0:
			speed = y/16; //TODO wertebereich von 1 bis 10 oder so, mehr ist augenkrebs alter
			break;
		case 4:
			scale = y;
			break;
		case 129:
			numcolors = y;
			break;
		}
	}
} noise;