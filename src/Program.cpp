#include "Program.h"

Program::Program()
{	// automatically add new Program to linked list
	ProgramManager::add(this);
}

Program::Program(bool add)
{	// automatically add new Program to linked list
	//! to use this, derived Program needs "using Program::Program"
	if(add)
		ProgramManager::add(this);
}