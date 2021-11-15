/**
 * @file zylProg.cpp
 * @author Bernhard Stöffler
 * @brief 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "zylProg.h"


zylProg::zylProg()
{ // automatically add new zylProg to linked list
	zylProgManager::add(this);
};

//************************* Program Manager **********************

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

void zylProgManager::input(uint8_t x, uint8_t y, uint8_t z){
	g_pActive->input(x, y, z);
}

