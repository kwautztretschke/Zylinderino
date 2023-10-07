#include "Program.h"
#include <string.h>
#include <stdlib.h>

#include "Hardware.h"

static class : public Program{
private:
	uint8_t m_ArtNetHistory[32] = {0};
	ArtnetHelper m_ArtnetHelper = ArtnetHelper(m_ArtNetHistory, 32);
	enum Mode{
		R2L,
		L2R,
		OUT,
		IN
	} m_Mode = R2L;
public:
	using Program::Program;
	int init(){
		m_Name = "barSync";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (!m_ArtnetHelper.input(key, value))
			return 0; //input was handled by artnethelper
		if(!strcmp(key, "mode")){
			if(!strcmp(value, "R2L"))
				m_Mode = R2L;
			else if(!strcmp(value, "L2R"))
				m_Mode = L2R;
			else if(!strcmp(value, "OUT"))
				m_Mode = OUT;
			else if(!strcmp(value, "IN"))
				m_Mode = IN;
			else
				return 1; //wrong mode
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	void barR2L(CRGB c, CRGB b, int d){
		for(int i=0; i<FB_SIZE; i++){
			m_FB[i] = i<d?c:b;
		}
	}
	void barL2R(CRGB c, CRGB b, int d){
		for(int i=0; i<FB_SIZE; i++){
			m_FB[i] = i>FB_SIZE-d?c:b;
		}
	}
	void barOUT(CRGB c, CRGB b, int d){
		d = (FB_SIZE - d)/2;
		for(int i=0; i<FB_SIZE/2; i++){
			m_FB[i] = m_FB[FB_SIZE-i-1] = i<d?b:c;
		}
	}
	void barIN(CRGB c, CRGB b, int d){
		d/=2;
		for(int i=0; i<FB_SIZE/2; i++){
			m_FB[i] = m_FB[FB_SIZE-i-1] = i<d?c:b;
		}
	}
	
	void render(long ms){
		CRGB color = getColor();
		CRGB background = getColorRelative(1);
		int distance = (FB_SIZE * m_ArtnetHelper.getModulator()) / 255;
		switch(m_Mode){
			case R2L:
				barR2L(color, background, distance);
				break;
			case L2R:
				barL2R(color, background, distance);
				break;
			case OUT:
				barOUT(color, background, distance);
				break;
			case IN:
				barIN(color, background, distance);
				break;
		}
	}
} barSync;
