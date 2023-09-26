#include "Program.h"
#include <string.h>
#include <stdlib.h>

static class : public ArtnetProgram{
private:
	char m_ArtNetHistory[32] = {0};
public:
	using ArtnetProgram::ArtnetProgram;
	int init(){
		m_Name = "simpleSync";
		m_pArtNetHistory = m_ArtNetHistory;
		m_ArtNetHistorySize = 32;
		return 0;
	}
	void render(long ms){
		CRGB c = getColor();
		c.nscale8(getModulator());
		for (int i=0;i<FB_SIZE;i++){
			m_FB[i] = c;
		}
	}
} simpleSync;
