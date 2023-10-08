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
		if(!strcmp(key, "interval")){
			m_Interval = strtol(value, NULL, 10);
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	//TODO maybe reorder functions or make them static
	void rippleHL(CRGB c){
		for(int x=0; x<X_RES-1; x++){
			for(int y=0; y<Y_RES; y++){
				m_FB[x][y] = m_FB[x+1][y]; //shift each column left
			}
		}
		for(int y=0; y<Y_RES; y++){
			m_FB[X_RES-1][y] = c; //sync last column
		}
	}
	void rippleHR(CRGB c){
		for(int x=X_RES-1; x>0; x--){
			for(int y=0; y<Y_RES; y++){
				m_FB[x][y] = m_FB[x-1][y]; //shift each column right
			}
		}
		for(int y=0; y<Y_RES; y++){
			m_FB[0][y] = c; //sync first column
		}
	}
	void rippleHOUT(CRGB c){
		for(int x=0; x<X_RES/2; x++){
			for(int y=0; y<Y_RES; y++){
				m_FB[x][y] = m_FB[x+1][y]; //shift each column left
				m_FB[X_RES-x-1][y] = m_FB[X_RES-x-2][y]; //shift each column right
			}
		}
		for(int y=0; y<Y_RES; y++){
			m_FB[X_RES/2][y] = c; //sync center column
		}
	}
	void rippleHIN(CRGB c){
		for(int x=X_RES/2-1; x>0; x--){
			for(int y=0; y<Y_RES; y++){
				m_FB[x][y] = m_FB[x-1][y]; //shift each column left
			}
		}
		for(int x=X_RES/2; x<X_RES-1; x++){
			for(int y=0; y<Y_RES; y++){
				m_FB[x][y] = m_FB[x+1][y]; //shift each column right
			}
		}
		for(int y=0; y<Y_RES; y++){
			m_FB[0][y] = c; //sync first column
			m_FB[X_RES-1][y] = c; //sync last column
		}
	}
	void rippleVD(CRGB c){
		for(int y=0; y<Y_RES-1; y++){
			for(int x=0; x<X_RES; x++){
				m_FB[x][y] = m_FB[x][y+1]; //shift each row down
			}
		}
		for(int x=0; x<X_RES; x++){
			m_FB[x][Y_RES-1] = c; //sync last row
		}
	}
	void rippleVU(CRGB c){
		for(int y=Y_RES-1; y>0; y--){
			for(int x=0; x<X_RES; x++){
				m_FB[x][y] = m_FB[x][y-1]; //shift each row up
			}
		}
		for(int x=0; x<X_RES; x++){
			m_FB[x][0] = c; //sync first row
		}
	}
	void rippleVOUT(CRGB c){
		for(int y=0; y<Y_RES/2-1; y++){
			for(int x=0; x<X_RES; x++){
				m_FB[x][y] = m_FB[x][y+1]; //shift each row down
				m_FB[x][Y_RES-y-1] = m_FB[x][Y_RES-y-2]; //shift each row up
			}
		}
		for(int x=0; x<X_RES; x++){
			m_FB[x][Y_RES/2-1] = c; //sync center rows
			m_FB[x][Y_RES/2] = c;
		}
	}
	void rippleVIN(CRGB c){
		for(int y=Y_RES/2-1; y>0; y--){
			for(int x=0; x<X_RES; x++){
				m_FB[x][y] = m_FB[x][y-1]; //shift each row up
			}
		}
		for(int y=Y_RES/2; y<Y_RES-1; y++){
			for(int x=0; x<X_RES; x++){
				m_FB[x][y] = m_FB[x][y+1]; //shift each row down
			}
		}
		for(int x=0; x<X_RES; x++){
			m_FB[x][0] = c; //sync first row
			m_FB[x][Y_RES-1] = c; //sync last row
		}
	}

	void render(long ms){
		if(++m_FrameCounter < m_Interval)
			return;
		m_FrameCounter = 0;

		CRGB c = getColor();
		c.nscale8(m_ArtnetHelper.getModulator());
		if(m_Orientation == V){
			switch(m_Direction){
				case R:
					rippleVD(c);
					break;
				case L:
					rippleVU(c);
					break;
				case OUT:
					rippleVOUT(c);
					break;
				case IN:
					rippleVIN(c);
					break;
			}
		}else{
			switch(m_Direction){
				case R:
					rippleHR(c);
					break;
				case L:
					rippleHL(c);
					break;
				case OUT:
					rippleHOUT(c);
					break;
				case IN:
					rippleHIN(c);
					break;
			}
		}
	}
} rippleSync;
