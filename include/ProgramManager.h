#ifndef __PROGRAMMANAGER_H__
#define __PROGRAMMANAGER_H__

class Program;

class ProgramManager{
private:
	static int			m_Count;
	static Program*		m_pHead;
	static Program*		m_pActive;
	//static zylPel				s_aColors[MAX_COLORS];
	//static int					s_ActiveColorIndex;
	static uint8_t		m_Color[3]; // TODO array of colors
public:
	static void			add(Program *ptr);
	static int			initPrograms();
	static int			init();

	static void			render(uint8_t* fb, long tick);
	static int			focus(char* program);
	static int			input(char* key, char* value);

	static void			setColor(uint8_t* c){
							for(int i=0;i<3;i++)
								m_Color[i] = c[i];
						}
	static uint8_t*		getColor() {return m_Color;}
};


#endif // __PROGRAMMANAGER_H__