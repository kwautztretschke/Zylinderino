#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "ProgramManager.h"

class Program{
public:
	const char*				m_Name;
	uint8_t					m_Color[3]; //TODO "Framebuffer"
	Program*				m_pNext = NULL;
	//* methods applicable for each Program
	;						Program();
	;						Program(bool add);
	//* methods to be redefined by programs -> "interface"
	virtual int 			init(){return 0;}
	virtual void          	activate(){};
	virtual void          	render(long tick){};
	virtual void			input(char* key, char* value){};
};


#endif // __PROGRAM_H__