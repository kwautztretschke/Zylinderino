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
#include "lib8tion/lib8tion.h"

class zylFB {
private:
	zylPel				m_FB[X_RES][Y_RES];
public:
	//****** constructors  *********************************************************
	;					zylFB(zylPel c);
	;					zylFB();

	//***** operators *************************************************************
	zylPel&				operator()(int x, int y);
	void				operator=(zylPel c);

	//***** methods ***************************************************************
	zylPel&				xy(int x, int y);
	void				setAll(zylPel c);
	void				setAlpha(uint8_t na);
	void				blur(fract8 blur_amount);
};

#endif