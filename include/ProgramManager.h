#ifndef __PROGRAMMANAGER_H__
#define __PROGRAMMANAGER_H__

#include <stdint.h>

class Program;

namespace ProgramManager{

void		add(Program *ptr);
int			initPrograms();
int			init();

void		render(long tick);
int			focus(char* program);
int			input(char* key, char* value);

void		setColor(uint8_t* c);
uint8_t*	getColor();
uint8_t*	getFB();

} // namespace ProgramManager

#endif // __PROGRAMMANAGER_H__