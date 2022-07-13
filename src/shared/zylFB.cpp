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

#include "shared/zylFB.h"

zylFB::zylFB(zylPel c){
	setAll(c);
}

zylFB::zylFB(){
	setAll(zylPel(255, 0, 0, 0));
}

zylPel&	zylFB::operator()(int x, int y)	{
	return xy(x,y);
}

void zylFB::operator=(zylPel c)	{
	setAll(c);
}

zylPel&	zylFB::xy(int x, int y){
	return m_FB[x][y];
}
void zylFB::setAll(zylPel c){
	for(int x=0;x<X_RES;x++)
		for(int y=0;y<Y_RES;y++)
			m_FB[x][y]=c;
}
void zylFB::setAlpha(uint8_t na){
	for(int x=0;x<X_RES;x++)
		for(int y=0;y<Y_RES;y++)
			m_FB[x][y].setAlpha(na);
}

void zylFB::blur(uint8_t amount){
	blurRows(amount);
	blurColumns(amount);
}

void zylFB::blurRows(uint8_t amount){
    // blur rows same as columns, for irregular matrix
    uint8_t keep = 255 - amount;
    uint8_t seep = amount >> 1;
    for(int row = 0; row < Y_RES; row++) {
        zylPel carryover = zylPel(0, 0, 0);
        for(int i = 0; i < X_RES; i++) {
            zylPel cur = xy(i,row);
            zylPel part = cur;
            part.nscale8(seep);
            cur.nscale8(keep);
            cur += carryover;
            if(i) 
				xy(i-1,row) += part;
            xy(i,row) = cur;
            carryover = part;
        }
    }
}

void zylFB::blurColumns(uint8_t amount){
    // blur columns
    uint8_t keep = 255 - amount;
    uint8_t seep = amount >> 1;
    for(uint8_t col = 0; col < X_RES; ++col) {
        zylPel carryover = zylPel(0, 0, 0);
        for(int i = 0; i < Y_RES; ++i) {
            zylPel cur = xy(col,i);
            zylPel part = cur;
            part.nscale8(seep);
            cur.nscale8(keep);
            cur += carryover;
            if(i) 
				xy(col,i-1) += part;
            xy(col,i) = cur;
            carryover = part;
        }
    }
}