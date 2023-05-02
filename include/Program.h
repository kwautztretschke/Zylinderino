#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "ProgramManager.h"

class Program{
public: //TODO make some of these Private?
	const char*				m_Name;
	uint8_t					m_FB[3]; //TODO "Framebuffer"
	Program*				m_pNext = 0;
	//* methods applicable for each Program
	;						Program();
	;						Program(bool add);
	//* methods to be redefined by programs -> "interface"
	virtual int 			init(){return 0;}
	virtual void          	activate(){}
	virtual void          	render(long tick){}
	virtual int				input(char* key, char* value){return 0;}
};


#endif // __PROGRAM_H__