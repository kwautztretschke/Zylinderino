#include "Program.h"
#include <string.h>
#include <stdlib.h>

static class : public Program{
private:
	uint8_t m_HotButtons[16] = {0};
	uint8_t m_Strips = 1;
	enum Orientation{H, V} m_Orientation = H;
public:
	int init(){
		m_Name = "simpleHB";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if(!strcmp(key, "strips")){
			m_Strips = strtol(value, NULL, 10);
			if(m_Strips > 16)
				m_Strips = 16;
			if(m_Strips < 1)
				m_Strips = 1;
			return 0;
		}
		if(!strcmp(key, "orientation")){
			m_Orientation = value[0] == 'V' ? V : H;
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		if(size < 80)
			return;
		memcpy(m_HotButtons, data+64, 16);
	}
	void render(long ms){
		// first reset everything
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++)
				m_FB[x][y] = CRGB::Black;

		// illuminate each n/th of the strip depending if the button is pressed
		CRGB color = getColor();
		for (int b=0;b<m_Strips;b++){
			if (m_HotButtons[b]){
				if(m_Orientation == H){
					for(int x=0; x<X_RES/m_Strips; x++){
						for(int y=0; y<Y_RES; y++){
							m_FB[x + b*X_RES/m_Strips][y] = color;
						}
					}
				}else{
					for(int x=0; x<X_RES; x++){
						for(int y=0; y<Y_RES/m_Strips; y++){
							m_FB[x][y + b*Y_RES/m_Strips] = color;
						}
					}
				}
			}
		}
	}
} simpleHB;
