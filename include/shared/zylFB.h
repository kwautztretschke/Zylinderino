/**
 * @file zylFB.h
 * @author Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __ZYLFB_H_
#define __ZYLFB_H_

#include "shared/config.h"
#include "shared/zylPel.h"

class zylFB {
private:
	zylPel				m_FB[X_RES][Y_RES];
public:
	zylPel&				xy(int x, int y);
	void				setAll(zylPel c);
	void				setAlpha(uint8_t na);
	zylPel&				operator()(int x, int y);
	void				operator=(zylPel c);
	;					zylFB(zylPel c);
	;					zylFB();
};

#endif