#include "Program.h"
#include <string.h>
#include <stdlib.h>

static class : public Program{
private:
	uint8_t m_ArtNetHistory[32] = {0};
	ArtnetHelper m_ArtnetHelper = ArtnetHelper(m_ArtNetHistory, 32);
public:
	int init(){
		m_Name = "simpleSync";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (!m_ArtnetHelper.input(key, value))
			return 0; //input was handled by artnethelper
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	void render(long ms){
		CRGB c = getColor();
		c.nscale8(m_ArtnetHelper.getModulator());
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++)
				m_FB[x][y] = c;
	}
} simpleSync;
