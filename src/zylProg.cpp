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

//***************** ZylProg base class functions *******************
zylProg::zylProg()
{	// automatically add new zylProg to linked list
	zylProgManager::add(this);
}

zylProg::zylProg(bool add)
{	// automatically add new zylProg to linked list
	//! to use this, derived zylProg needs "using zylProg::zylProg"
	if(add)
		zylProgManager::add(this);
}

int zylProg::push()
{	//pushes program to the top of the render queue
	if(m_pAbove || m_pBelow){
		return 1;
	}else{
		m_pAbove = 						&zylProgManager::s_FG;	//set own pointers
		m_pBelow = 						zylProgManager::s_FG.m_pBelow;
		zylProgManager::s_FG.m_pBelow = this;					//redirect other's pointers
		m_pBelow->m_pAbove = 			this;
		return 0;
	}
}

//TODO make it impossible to pop FG and BG
int zylProg::pop()
{	//removes program from render queue, if it's in there
	if(m_pAbove || m_pBelow){
		m_pAbove->m_pBelow = 	m_pBelow; 	//redirect other's pointers
		m_pBelow->m_pAbove = 	m_pAbove;
		m_pAbove = 				NULL;		//remove own pointers
		m_pBelow = 				NULL;
		return 0;
	}else
		return 1;
}

int zylProg::move(bool up)
{	//swaps program with one above(/below) if in render queue
	if(m_pAbove == NULL || m_pBelow == NULL){
		return 1;	// program not in queue
	}else if((m_pAbove == &zylProgManager::s_FG && up)
	 ||(m_pBelow == &zylProgManager::s_BG && !up)){
		return 2;	// program at edge
	}else{
		if(up){		//get a whiteboard and draw some arrows if unclear
			zylProg* oldAbove = 	m_pAbove;
			m_pAbove = 				oldAbove->m_pAbove;
			oldAbove->m_pAbove =	this;
			oldAbove->m_pBelow = 	m_pBelow;
			m_pBelow->m_pAbove = 	oldAbove;
			m_pBelow = 				oldAbove;
			m_pAbove->m_pBelow = 	this;
			return 0;
		}else{
			zylProg* oldBelow = 	m_pBelow;
			m_pBelow = 				oldBelow->m_pBelow;
			oldBelow->m_pBelow = 	this;
			oldBelow->m_pAbove = 	m_pAbove;
			m_pAbove->m_pBelow = 	oldBelow;
			m_pAbove = 				oldBelow;
			m_pBelow->m_pAbove = 	this;
			return 0;
		}
	}
}

//************************* Program Manager **********************
int 		zylProgManager::s_Count =				0;
zylProg*	zylProgManager::s_pHead = 				NULL;
zylProg*	zylProgManager::s_pActive =				NULL;
CRGB 		zylProgManager::s_aColors[MAX_COLORS] = {CRGB::Black};
int 		zylProgManager::s_ActiveColorIndex = 	0;
zylProg		zylProgManager::s_FG(false);
zylProg		zylProgManager::s_BG(false);


void zylProgManager::add(zylProg* ptr)
{	//call this in the constructor of your programs to add them to a list of all programs
	ptr->m_pNext = 	s_pHead;
	s_pHead = 		ptr;
	s_Count++;
}

int zylProgManager::focus(int id)
{	//change active program by ID
	zylProg* ptr = s_pHead;
	while(ptr != NULL){
		if(ptr->m_Id==id){
			Serial.printf("Found program with ID %d\n", id);
			s_pActive = ptr;
			s_pActive->activate();
			return 0;
		}
		ptr = ptr->m_pNext;
	}
	return 1;
}

void zylProgManager::input(uint8_t x, uint8_t y, uint8_t z)
{	//forward a three byte input command to the active program
	s_pActive->input(x, y, z);
}

int zylProgManager::initPrograms()
{	//initialize all programs
	Serial.printf("initializing %d programs\n", s_Count);
	int error=0;
	zylProg* ptr = s_pHead;
	for(int i=0; i<s_Count; i++){
		error += ptr->init();
		Serial.printf("Program with ID %d at %p\n", ptr->m_Id, ptr);
		ptr = ptr->m_pNext;
	}
	return error;
}

int zylProgManager::init()
{	//initialize the zylProgManager (Set variables and add one program to renderqueue)
	s_aColors[0] = 		CRGB::Yellow;
	s_FG.m_pAbove = 	&s_FG;
	s_FG.m_pBelow = 	&s_BG;
	s_BG.m_pAbove = 	&s_FG;
	s_BG.m_pBelow = 	&s_BG;
	if(s_pHead == NULL){
		Serial.println("NULL POINTER ERROR, no programs loaded\n");
		return 1;
	}
	s_pActive = s_pHead;	//focus first program and push it on the render list
	#ifdef ZPM_DEFAULT_PROGRAM
		focus(ZPM_DEFAULT_PROGRAM);
	#endif
	s_pActive->push();
	s_pActive->activate();
	return 0;
}

void zylProgManager::renderPrograms()
{	//render all programs in renderqueue
	zylProg* ptr = s_BG.m_pAbove;
	while(ptr != &s_FG){
		ptr->render();
		ptr = ptr->m_pAbove;
	}
}

//TODO merge with renderPrograms()
void zylProgManager::composite(CRGB fb_in[X_RES][Y_RES])
{	//composite programs in the renderqueue into a given framebuffer
	//? maybe clear the framebuffer first?
	zylProg* ptr = s_BG.m_pAbove;
	while(ptr != &s_FG){
		//? just add render() here?
		for(int x=0;x<X_RES;x++){
			for(int y=0;y<Y_RES;y++){
				switch(ptr->m_CompositeMode){
				case ZCM_SOLID:	//default
					fb_in[x][y] = ptr->m_FB[x][y]; //TODO alpha, opacity
					break;
				case ZCM_ADD:
					fb_in[x][y] = 
						fb_in[x][y]
						+ ptr->m_FB[x][y]; //TODO alpha, opacity
					break;
				case ZCM_SUB:
					fb_in[x][y] = 
						fb_in[x][y]
						- ptr->m_FB[x][y]; //TODO alpha, opacity
					break;
				case ZCM_AVG:
					fb_in[x][y] = 
						fb_in[x][y]/2
						+ ptr->m_FB[x][y]/2; //TODO alpha, opacity
					break;
				}
			}
		}
		ptr = ptr->m_pAbove;
	}
}

int zylProgManager::changeComposition(int x, int y)
{	//modify the renderqueue or related settings
	switch(x){
	case 0: //change mode
		s_pActive->m_CompositeMode = (zylCompositeMode) y;
		return 0;
	case 1: //change order
		switch(y){
		case 0: //push
			return s_pActive->push();
		case 1: //pop
			return s_pActive->pop();
		case 2: //move up
			return s_pActive->move(true);
		case 3: //move down
			return s_pActive->move(false);
		default: //invalid input
			return 3;
		}
		break;
	case 2: //change opacity
		return 0; //TODO implement
	case 3: //show only a single program
		for (zylProg* ptr = s_BG.m_pAbove; ptr != &s_FG; ptr = s_BG.m_pAbove)
			ptr->pop();
		return s_pActive->push();
	default: //invalid input
		return 3;
	}
}

void zylProgManager::printComposition()
{	//print info about the renderqueue on serial
	Serial.printf("\nComposition:\n");
	zylProg* ptr = &s_FG;
	for(int i=0;;i++){
		if(ptr == &s_FG){
			Serial.printf("Layer %d: Foreground\n", i);
		}else if(ptr == &s_BG){
			Serial.printf("Layer %d: Background\n", i);
			break;
		}else{
			Serial.printf("Layer %d: Program %d, mode %d %s\n", i, ptr->m_Id, ptr->m_CompositeMode, (ptr==s_pActive)?"<-Active":"");
		}
		ptr = ptr->m_pBelow;
	}
}

void zylProgManager::selectColor(int i)
{	//activates color i
	s_ActiveColorIndex = i;
}

void zylProgManager::setColor(CRGB c, int i)
{	//changes a specific color and leaves index on it
	if(i>=0 && i<MAX_COLORS){
		s_ActiveColorIndex = i;
		setColor(c);
 	}
}
 
void zylProgManager::setColor(CRGB c)
{	//changes the currently active color
	s_aColors[s_ActiveColorIndex] = c;
}

CRGB zylProgManager::getColor(int i)
{	//returns a specific color without activating it
	return s_aColors[i];
}

CRGB zylProgManager::getColor()
{	//returns the currently selected color
	return s_aColors[s_ActiveColorIndex];
}