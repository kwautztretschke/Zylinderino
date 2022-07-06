/**
 * @file fire.cpp
 * @author Bernhard Stöffler
 * @brief 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "zylProg.h"
#include <FastLED.h>

static class : public zylProg{
private:
	int			m_Speed;
	int			m_XScale;
	int			m_YScale;
	int			m_ThresholdSlope;
	CRGB 		colormap(int y, int v){
		// distribution on the hot end is 2/5, 3/5, 4/5
		int t0 = 87 - y*255/(m_ThresholdSlope*Y_RES);
		int t1 = 144 - y*256/(m_ThresholdSlope*Y_RES);
		int t2 = 190 - y*256/(m_ThresholdSlope*Y_RES);
		if (v<t0)
			return CRGB::Purple;
		if (v<t1)
			return CRGB::Orange;
		if (v<t2)
			return CRGB::Red;
		return CRGB::Black;
	}
public:
	using zylProg::zylProg;
	int init(){
		m_Id = 130;
		m_Speed = 16;
		m_XScale = 64;
		m_YScale = 2; // should be around XScale/16, maybe combine
		m_ThresholdSlope = 2;
		return 0;
	}
	void render(){
		long t = millis()*m_Speed/32;
		for(int x=0; x<X_RES; x++)
			for(int y=0; y<Y_RES; y++){
				int dy = Y_RES-y + 1; // starting at 0 breaks things
				m_FB[x][y] = colormap(y, inoise8(
						x*m_XScale, 
						-dy*dy*dy*m_YScale - t,
						0));
			}

	}
} fire;