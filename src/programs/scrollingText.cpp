#include "Program.h"

#include "buchstabenyolo.h"

#define TEXT_MAX_LENGTH 1024

static class : public Program{
private:
	char			m_aText[TEXT_MAX_LENGTH];
  	int     		m_TextLength;
	uint8_t			m_aBytemap[TEXT_MAX_LENGTH * FONT_WIDTH];
  	int     		m_ByteLength;
  	int    			m_WrapOffset = 		10;
	int				m_Speed = 			20;
	int strToBytes(const char *pText){
		Serial.printf("Translating text '%s'\n", pText);
		memset(m_aBytemap, 0, sizeof(m_aBytemap));
		m_TextLength = strlen(pText);
		for(int c=0;c<m_TextLength;c++){ // basically strcpy but sanitized to our stuff
			int chr = pText[c];
			if     (chr == 0xE4) chr = FONT_ae; // We're Using ISO-8859-15 in the webpage
			else if(chr == 0xF6) chr = FONT_oe;
			else if(chr == 0xFC) chr = FONT_ue;
			else if(chr == 0xC4) chr = FONT_AE;
			else if(chr == 0xD6) chr = FONT_OE;
			else if(chr == 0xDC) chr = FONT_UE;
			else if(chr == 0xDF) chr = FONT_ssharp;
			else if(chr == 0xA4) chr = FONT_euro;
			else if(chr<FONT_FIRST_CHAR||chr>FONT_LAST_CHAR){
				//return chr;
				Serial.printf("Error Char %d (%c)\n", chr, chr); //todo return as error
				c++;
			}
			chr -= FONT_FIRST_CHAR;

			for(int i=0;i<FONT_WIDTH;i++){
				m_aBytemap[c*FONT_WIDTH +i] = g_aFont[chr*FONT_WIDTH +i];
			}
		}
		m_ByteLength = m_TextLength*FONT_WIDTH + m_WrapOffset;
		for(int i=m_TextLength*FONT_WIDTH; i<m_ByteLength; i++)
		m_aBytemap[i] = 0;
		return 0;
	}
public:
	using Program::Program;
	int init(){
		m_Name = "scrollingText";
		memset(m_aText, 0, sizeof(m_aText));
		strToBytes("Hello World!");
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (!strcmp(key, "speed")){
			m_Speed = strtol(value, NULL, 10);
			return 0;
		}
		if (!strcmp(key, "wrapoffset")){
			m_WrapOffset = strtol(value, NULL, 10);
			return 0;
		}
		if (!strcmp(key, "text")){
			return strToBytes(value);
		}
		return 1;
	}
	void render(long ms){
		for(int x=0;x<X_RES;x++){
		// int currentByteIndex = (x+(m_Speed*millis()/128/64)) % m_ByteLength;
		int currentByteIndex = (x+(m_Speed*ms/128)) % m_ByteLength;
			for(int y=0;y<Y_RES;y++){
				if(m_aBytemap[currentByteIndex] & 1<<(FONT_HEIGHT-y-1))
					m_FB[x][y] = getColor();
				else
					m_FB[x][y] = CRGB::Black;
			}
		}
	}
} scrollingText;