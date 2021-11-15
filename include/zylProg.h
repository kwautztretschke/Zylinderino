/**
 * @file zylProg.h
 * @author Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __ZYLPROG_H_
#define __ZYLPROG_H_

#ifdef ARDUINO
#include <FastLED.h>
#else
typedef char CRGB;
#include	<stdlib.h>
#include	<stdint.h>
#endif
#include "config.h"


class zylProg{
protected:
	CRGB					m_FB[X_RES][Y_RES];
public:
	zylProg*					m_pNext = NULL;

	;						zylProg();
	virtual int 			init(){}
	virtual void          	activate(){};
	virtual void          	render() = 0;    // * Virtual function, so must be redefined
	virtual void			input(uint8_t x, uint8_t y, uint8_t z);
};

//************************* Program Manager *************************

class zylProgManager{
private:
	static int					g_Count;
	static zylProg*				g_pHead;
	static zylProg*				g_pActive;
public:
	static void					add(zylProg *ptr);
	static void					focus(int index);
	static void					renderPrograms();
	static void					composite(CRGB *fb);
	static void					input(uint8_t x, uint8_t y, uint8_t z);
};

#endif
