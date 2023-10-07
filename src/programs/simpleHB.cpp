#include "Program.h"
#include <string.h>
#include <stdlib.h>

static class : public Program{
private:
	uint8_t m_HotButtons[16] = {0};
	uint8_t m_Strips = 1;
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
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		if(size < 80)
			return;
		memcpy(m_HotButtons, data+64, 16);
	}
	void render(long ms){
		// first reset everything
		for (int i=0;i<FB_SIZE;i++){
			m_FB[i] = CRGB::Black;
		}
		// illuminate each n/th of the strip depending if the button is pressed
		CRGB color = getColor();
		for (int b=0;b<m_Strips;b++){
			if (m_HotButtons[b]){
				for(int i=0; i<FB_SIZE/m_Strips; i++){
					m_FB[i + b*FB_SIZE/m_Strips] = color;
				}
			}
		}
	}
} simpleHB;
