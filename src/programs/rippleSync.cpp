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
	int m_Interval = 1; //only ripple every n frames
	int m_FrameCounter = 0;
public:
	using Program::Program;
	int init(){
		m_Name = "rippleSync";
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
		}else if(!strcmp(key, "interval")){
			m_Interval = strtol(value, NULL, 10);
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	void rippleL2R(CRGB c){
		for(int i=0; i<(FB_SIZE-1); i++){
			// shift each LED to the right
			m_FB[i] = m_FB[i+1];
		}
		// sync last LED
		m_FB[FB_SIZE-1] = c;
	}
	void rippleR2L(CRGB c){
		for(int i=FB_SIZE-1; i>0; i--){
			// shift each LED to the left
			m_FB[i] = m_FB[i-1];
		}
		// sync first LED
		m_FB[0] = c;
	}
	void rippleOUT(CRGB c){
		// ripple left half to the left, and mirror that to the right
		for(int i=0; i<(FB_SIZE/2)-1; i++){
			m_FB[i] = m_FB[i+1];
			m_FB[FB_SIZE-i-1] = m_FB[FB_SIZE-i-2];
		}
		// sync center LEDs
		// TODO make center size configurable
		for(int i=(FB_SIZE/2)-1; i<=FB_SIZE-(FB_SIZE/2); i++){
			m_FB[i] = c;
		}
	}
	void rippleIN(CRGB c){
		// ripple right half to the left
		for(int i=(FB_SIZE/2)-1; i>0; i--){
			m_FB[i] = m_FB[i-1];
		}
		// ripple left half to the right
		for(int i=FB_SIZE/2; i<(FB_SIZE-1); i++){
			m_FB[i] = m_FB[i+1];
		}
		// sync outmost LEDs
		m_FB[0] = c;
		m_FB[FB_SIZE-1] = c;
	}
	
	void render(long ms){
		if(++m_FrameCounter < m_Interval)
			return;
		m_FrameCounter = 0;

		CRGB c = getColor();
		c.nscale8(m_ArtnetHelper.getModulator());
		switch(m_Mode){
			case R2L:
				rippleR2L(c);
				break;
			case L2R:
				rippleL2R(c);
				break;
			case OUT:
				rippleOUT(c);
				break;
			case IN:
				rippleIN(c);
				break;
		}
	}
} rippleSync;
