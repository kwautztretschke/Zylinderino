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

//class zylProgManager; // forward declaration, needed for zylProg(zpm)

class zylProg{
protected:
	CRGB					m_FB[X_RES][Y_RES];
public:
	zylProg					*m_pNext = NULL;

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


/* move to cpp *****************/

//init "static members" (i.e. global class variables)

int zylProgManager::g_Count=0;
zylProg *zylProgManager::g_pHead=NULL;
zylProg *zylProgManager::g_pActive=NULL;

// implement "static methods" (i.e. global functions)

void zylProgManager::add(zylProg* ptr)
{
	if (g_pHead == NULL){ //first program
		g_pHead = ptr;
		g_pActive = ptr;
	}else{
		zylProg* cur = g_pHead;
		while(cur->m_pNext != NULL)
			cur = cur->m_pNext;
		cur->m_pNext = ptr;
	}
	g_Count++;
}

void zylProgManager::focus(int index)
{
	zylProg* ptr = g_pHead;
	for(int i=0; i<index; i++)
		ptr = ptr->m_pNext;
	g_pActive = ptr;
	g_pActive->activate();
}

void zylProgManager::input(uint8_t x, uint8_t y, uint8_t z) // I would strongly recommend int x,
															// but there are bazillions of flys ...
{
	g_pActive->input(x, y, z);
}

zylProg::zylProg()
{ // automatically add new zylProg to linked list
	zylProgManager::add(this);
};


#endif
