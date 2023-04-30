#ifndef __PROGRAMMANAGER_H__
#define __PROGRAMMANAGER_H__



class ProgramManagerClass{
public:
	static void 	init();
	static void 	renderProgram();
	static int		focus(char* program);
	static void		input(char* key, char* value);
};

extern ProgramManagerClass ProgramManager;

#endif // __PROGRAMMANAGER_H__