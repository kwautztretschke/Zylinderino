#include "Program.h"
#include <string.h>
#include <stdlib.h>

#include "Hardware.h"

static class : public Program{
private:
	uint8_t m_ArtNetHistory[32] = {0};
	ArtnetHelper m_ArtnetHelper = ArtnetHelper(m_ArtNetHistory, 32);
	enum Direction{
		R,
		L,
		OUT,
		IN
	} m_Direction = R;
	enum Orientation{
		H,
		V
	} m_Orientation = H;
	uint8_t m_Fade = 128;
	int m_FrameCounter = 0;
	int m_Interval = 20; // only dim once every n frames //TODO hacky!
public:
	using Program::Program;
	int init(){
		m_Name = "barSync";
		return 0;
	}
	void activate(){
		// m_ArtnetHelper.clearArtNetHistory();
		m_FrameCounter = 0;
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++)
				m_FB[x][y] = CRGB::Black;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (!m_ArtnetHelper.input(key, value))
			return 0; //input was handled by artnethelper
		if(!strcmp(key, "direction")){
			if(!strcmp(value, "R")){
				m_Direction = R;
				m_Orientation = H;
			}else if(!strcmp(value, "L")){
				m_Direction = L;
				m_Orientation = H;
			}else if(!strcmp(value, "D")){
				m_Direction = R;
				m_Orientation = V;
			}else if(!strcmp(value, "U")){
				m_Direction = L;
				m_Orientation = V;
			}else if(!strcmp(value, "OUT")){
				m_Direction = OUT;
			}else if(!strcmp(value, "IN")){
				m_Direction = IN;
			}else
				return 1; //wrong mode
			return 0;
		}
		if(!strcmp(key, "orientation")){
			if(!strcmp(value, "H"))
				m_Orientation = H;
			else if(!strcmp(value, "V"))
				m_Orientation = V;
			else
				return 1; //wrong mode
			return 0;
		}
		if(!strcmp(key, "fade")){
			m_Fade = strtol(value, NULL, 10);
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	void barVU(CRGB c, int d){
		for(int x=0;x<X_RES;x++)
			for(int y=0;y<d;y++)
				m_FB[x][y] = c;
	}
	void barVD(CRGB c, int d){
		for(int x=0;x<X_RES;x++)
			for(int y=0;y<d;y++)
				m_FB[x][Y_RES-1-y] = c;
	}
	void barVOUT(CRGB c, int d){
		d/=2;
		for(int x=0;x<X_RES;x++)
			for(int y=0;y<d;y++)
				m_FB[x][Y_RES/2-1-y] = m_FB[x][Y_RES/2+y] = c;
	}
	void barVIN(CRGB c, int d){
		d/=2;
		for(int x=0;x<X_RES;x++)
			for(int y=0;y<d;y++)
				m_FB[x][y] = m_FB[x][Y_RES-y-1] = c;
	}
	void barHL(CRGB c, int d){
		for(int x=0;x<d;x++)
			for(int y=0;y<Y_RES;y++)
				m_FB[x][y] = c;
	}
	void barHR(CRGB c, int d){
		for(int x=0;x<d;x++)
			for(int y=0;y<Y_RES;y++)
				m_FB[X_RES-1-x][y] = c;
	}
	void barHOUT(CRGB c, int d){
		d/=2;
		for(int x=0;x<d;x++)
			for(int y=0;y<Y_RES;y++)
				m_FB[X_RES/2-x-1][y] = m_FB[X_RES/2+x][y] = c;
	}
	void barHIN(CRGB c, int d){
		d/=2;
		for(int x=0;x<d;x++)
			for(int y=0;y<Y_RES;y++)
				m_FB[x][y] = m_FB[X_RES-x-1][y] = c;
	}
	
	void render(long ms){
		if (++m_FrameCounter > m_Interval){ //i think this is slow af
			m_FrameCounter = 0;
			for(int x=0; x<X_RES; x++)
				for(int y=0; y<Y_RES; y++)
					m_FB[x][y].nscale8(m_Fade); //slowly dim all pixels
		}
		CRGB color = getColor();
		if(m_Orientation == V){
			int distance = (Y_RES * m_ArtnetHelper.getModulator()) / 255;
			switch(m_Direction){ //and light up with full brightness
				case R:
					barVD(color, distance);
					break;
				case L:
					barVU(color, distance);
					break;
				case OUT:
					barVOUT(color, distance);
					break;
				case IN:
					barVIN(color, distance);
					break;
			}	
		}else{
			int distance = (X_RES * m_ArtnetHelper.getModulator()) / 255;
			switch(m_Direction){ //and light up with full brightness
				case R:
					barHR(color, distance);
					break;
				case L:
					barHL(color, distance);
					break;
				case OUT:
					barHOUT(color, distance);
					break;
				case IN:
					barHIN(color, distance);
					break;
			}
		}
	}
} barSync;
