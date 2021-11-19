/**
 * @file zylFB.cpp
 * @author  Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "zylFB.h"


zylPel&	zylFB::xy(int x, int y){
	return m_FB[x][y];
}
void zylFB::setAll(CRGB c){
	for(int x=0;x<X_RES;x++)
		for(int y=0;y<X_RES;y++)
			m_FB[x][y]=c;
}
void zylFB::setAlpha(uint8_t na){
	for(int x=0;x<X_RES;x++)
		for(int y=0;y<X_RES;y++)
			m_FB[x][y].setAlpha(na);
}

zylPel&	zylFB::operator()(int x, int y)	{
	return xy(x,y);
}

void zylFB::operator=(CRGB c)	{
	setAll(c);
}

zylFB::zylFB(CRGB c){
	setAll(c);
	setAlpha(255);
}

zylFB::zylFB(){
	setAll((uint32_t)CRGB::Black);
	setAlpha(255);
}

