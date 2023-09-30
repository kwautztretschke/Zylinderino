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
	uint8_t m_Fade = 230;
	int m_FrameCounter = 0;
	int m_Interval = 20; // only dim once every n frames //TODO hacky!
public:
	using Program::Program;
	int init(){
		m_Name = "barFadeSync";
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
		}else if(!strcmp(key, "fade")){
			m_Fade = strtol(value, NULL, 10);
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	void barR2L(CRGB c, int d){
		for(int i=0; i<d; i++){
			m_FB[i] = c;
		}
	}
	void barL2R(CRGB c, int d){
		for(int i=0; i<d; i++){
			m_FB[FB_SIZE-1 - i] = c;
		}
	}
	void barOUT(CRGB c, int d){
		d/=2;
		for(int i=0; i<d; i++){
			m_FB[FB_SIZE/2 - i] = m_FB[FB_SIZE/2 + i-1] = c;
		}
	}
	void barIN(CRGB c, int d){
		d/=2;
		for(int i=0; i<d; i++){
			m_FB[i] = m_FB[FB_SIZE-i-1] = c;
		}
	}
	
	void render(long ms){
		CRGB color = getColor();
		int distance = (FB_SIZE * m_ArtnetHelper.getModulator()) / 255;
		if (++m_FrameCounter > m_Interval){
			m_FrameCounter = 0;
			for(int i=0; i<FB_SIZE; i++){
				m_FB[i].nscale8(m_Fade); //slowly dim all LEDs
			}
		}
		switch(m_Mode){ //and light up with full brightness
			case R2L:
				barR2L(color, distance);
				break;
			case L2R:
				barL2R(color, distance);
				break;
			case OUT:
				barOUT(color, distance);
				break;
			case IN:
				barIN(color, distance);
				break;
		}
	}
} barFadeSync;
