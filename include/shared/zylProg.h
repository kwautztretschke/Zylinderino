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

#include "zylFB.h"
#include "config.h"

//************************* Zylinder Program ************************
enum zylCompositeMode{
	ZCM_SOLID 	= 0,
	ZCM_ADD 	= 1,
	ZCM_SUB 	= 2,
	ZCM_AVG 	= 3
};

class zylProg{
public:
	int						m_Id;
	zylCompositeMode		m_CompositeMode = ZCM_SOLID;
	zylFB					m_FB;
	zylProg*				m_pNext = NULL;
	zylProg*				m_pAbove = NULL;
	zylProg*				m_pBelow = NULL;
	//* methods applicable for each zylProg
	;						zylProg();
	;						zylProg(bool add);
	int 					push();
	int						pop();
	int						move(bool up);
	//* methods to be redefined by programs -> "interface"
	virtual int 			init(){return 0;}
	virtual void          	activate(){};
	virtual void          	render(){};
	virtual void			input(uint8_t, uint8_t, uint8_t){};
};

//************************* Program Manager *************************

class zylProgManager{
private:
	static int					s_Count;
	static zylProg*				s_pHead;
	static zylProg*				s_pActive;
	static zylPel				s_aColors[MAX_COLORS];
	static int					s_ActiveColorIndex;
public:
	//* Head and Tail for doubly linked render-list
	static zylProg				s_FG;
	static zylProg				s_BG;
	static void					add(zylProg *ptr);
	static int					initPrograms();
	static int					init();

	static int					focus(int id);
	static void					renderPrograms();
	static void					composite(zylFB fb);
	static void					input(uint8_t x, uint8_t y, uint8_t z);

	static int					changeComposition(int x, int y);
	static void					printComposition();
	static void					selectColor(int i);
	static void					setColor(zylPel c, int i);
	static void					setColor(zylPel c);
	static zylPel				getColor(int i);
	static zylPel				getColor();
};

#endif
